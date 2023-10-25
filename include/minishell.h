/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 15:33:03 by dbredykh          #+#    #+#             */
/*   Updated: 2023/10/25 12:20:26 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <dirent.h>
# include <stdint.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../assets/libft/include/libft.h"
# include "defines.h"
# include <fcntl.h>
# include <errno.h>

typedef struct s_info	t_info;
typedef int				(*t_builtin_ptr)(t_list *, t_info *);

typedef struct s_cmd
{
	char			**command;
	int				fd_in;
	int				fd_out;
	char			*here_doc;
	int				append_f;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_info
{
	t_builtin_ptr	builtins[7];
	char			*reserved_words[7];
	char			**envp;
	t_list			*envp_lst;
	/*
		A node list with all the environment variables in key:value format.
		If no operations were performed on the list, there's no need to rebuild envp,
		thus conserving resources. As soon as a new variable is added,
		or an old one is modified, we set envp_f to 1 and envp is rebuilt.
	 */
	char			exit_f;
	// A flag for exiting the program.
	int				status;
	/*
		"For $?. Since all commands will be executed in subprocesses except for built-ins.
		Signals of these commands will be processed in a different way; we will look at the process exit status using
		waitpid(pid, &status, 0);
		WIFSIGNALED(status) - a macro check (true / false) if the process was terminated by a signal, such as SIGSEGV signal;
		WTERMSIG(status) - allows you to find out the signal that terminated the process;
		WIFEXITED(status) - a macro check (true / false) if the child process terminated normally (called exit()) - you can call WEXITSTATUS to get the exit code;
		WEXITSTATUS(status) - the macro returns the process termination code."
	*/
	/*
		int status;
		waitpid(pid, &status, 0);
		&status - Exit status of the child process we are waiting for
		if (WIFEXITED(status)) {
			int exit_status = WEXITSTATUS(status);
			printf("Child exited with status %d\n", exit_status);
		} else if (WIFSIGNALED(status)) {
			int signal_number = WTERMSIG(status);
			printf("Child terminated by signal %d\n", signal_number);
		}
	 */
	/*
		int status;
		pid_t child_pid = fork();

		if (child_pid == 0) {
			execve(args...);
			exit(127);
		}
		} else {
			waitpid(child_pid, &status, 0);
			if (WIFEXITED(status)) {
				int exit_status = WEXITSTATUS(status);
			}
		}
	 */
	t_token			*token_lst;
	/*
		A list of tokens.
		key: TOKEN_INDX, value: "tokent value, ex: <" tokens.h -> there are all tokens
	 */
	t_cmd			*cmd_lst;
	/*
		In the case of "cat >file | cat <file && pwd" : t_lgroup: t_list *tokens, &&, t_list * tokens.
		List for logical groups, i.e., groups of commands separated by logical operators &&, ||, ;
	 */
}					t_info;

// buildins
int		buildin_echo(t_list *list, t_info *info);
int		buildin_cd(t_list *list, t_info *info);
int		buildin_pwd(t_list *list, t_info *info);
int		buildin_export(t_list *list, t_info *info);
int		buildin_unset(t_list *list, t_info *info);
int		buildin_env(t_list *list, t_info *info);
int		buildin_exit(t_list *list, t_info *info);

// minishell_lounch

void	minishell_lounch(t_info *info);

// ft_readline

char	*ft_readline(void);

// tokenizer_core

void	fill_in_lex(t_info *info, int token, char *content);

// tenizer_handlers

void	handle_redirections(t_info *info, char **str);
void	handle_words(t_info *info, char **str);
void	handle_space(t_info *info, char **str);
void	handle_quotes(t_info *info, char **str);

// tokenizer_core

void	tokenizer(t_info *info, char *str);

// exapansion

void	expansion(t_info *info);

// expantion_utils

int		is_valid_dollar_followup(char c);
void	append_to_buffer(char *buf, const char *append, int *current_len);
char	*get_envp_value(t_list *list, char *str);
char	*get_envp_key(char *str);

// delete_sep_token

void	delete_token_sep(t_info *info);

// grouping

void	grouping(t_info *info);



# define TRUE 1
# define FALSE 0

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define EXIT_SUCCESS 0
# define EXIT_ERROR -1

# define NO_FD -2

#define PATH_SIZE 4097

# define FORK_ERROR "Unable to fork" 
# define REDIR_ERROR "Unable to redirect" 
# define EXEC_ERROR "Unable to execute"

/*Colors*/
# define RESET "\033[0;m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"



/****Envp utils*******/
//For envp manipulation
void	ft_init_envp(t_info *info, char **envp);
void    ft_free_matrix(char **str);
char    **ft_copy_matrix(char **envp);
int     ft_matrix_size(char **envp);
char	**ft_malloc_matrix(char **envp);
//For export
void	ft_modify_variable(t_info *info, char *tuple);
void	ft_add_to_matrix(t_info *info, char *tuple);
//For unset
void    ft_delete_variable(t_info *info, char *tuple);

/****Tuple utils*******/
int     ft_var_size(char *tuple);
int     ft_contains(char *tuple, char *envp_tuple);
int     ft_env_exists(char *tuple, char **envp);
char    *ft_get_env_value(t_info *info, char *tuple);
char    *ft_store_value(char *tuple);
int     ft_contains(char *tuple, char *envp_tuple);

/*******BUILTIN FUNCTIONS***********/

//Functions for testing
void 	ft_test_cd();
void	ft_test_env();
void 	ft_test_exit();
void 	ft_test_export();
void 	ft_test_pwd();
void 	ft_test_unset();
void 	ft_test_echo();


//Functions 
int		echo();
int		ft_echo(char **str);

int    	pwd(char **cmd);
int     ft_pwd(void);

int		export(t_info *info, char **cmd);
int		ft_export(t_info *info, char *tuple);
void    ft_print_export(t_info *info);

int		unset(t_info *info, char **cmd);
int		ft_unset(t_info *info, char *tuple);

int		env(t_info *info, char **cmd);
int	    ft_env(t_info *info);

int    	cd(t_info *info, char **cmd);
int     ft_cd(t_info *info, char **cmd);

// error: conflicting types for 'exit' ---> we will call it "exit1"
int		exit1(t_info *info, char **cmd);
int		ft_exit(t_info *info, int option);

int		echo(char **cmd);
int		ft_echo(char **cmd);

void 	test_builtins();

/****PIPEX*******/
//Aux functions
int		ft_print_error(char *error);
char	*abs_bin_path(char *cmd, char **envp);
char	**get_paths(char *envp[]);
t_cmd   *init_cmd_node(int fd_in1, int fd_out1, char **argv);
t_cmd   *create_list(char *str, int fdin, int fdout);
int		ft_is_builtin(char *str);

//Atomic functions

int		ft_exec_cmd(t_info *info, t_cmd *node);
void	ft_pipex(t_info *info, t_cmd *list);



#endif
