/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:28:05 by dbredykh          #+#    #+#             */
/*   Updated: 2023/11/02 18:05:47 by dbredykh         ###   ########.fr       */
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

# define TRUE 1
# define FALSE 0

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define EXIT_EXIT 3
# define EXIT_SUCCESS 0
# define EXIT_ERROR 1
# define BAD_ARGS 2
# define COMMAND_NOT_FOUND 127
# define CTRL_C 130

# define NO_FD -2

# define PATH_SIZE 4097

# define FORK_ERROR "Unable to fork"
# define REDIR_ERROR "Unable to redirect"
# define EXEC_ERROR "Unable to execute"

/*Colors*/
# define RESET "\033[0;m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"

typedef struct s_info	t_info;

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
	char			*reserved_words[8];
	char			**envp;
	t_list			*envp_lst;
	char			exit_f;
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
	t_cmd			*cmd_lst;
}					t_info;

// init_utils
void	init_envp_lst(t_info *info, char **envp);
void	init_envp(t_info *info, char **environ);

// ft_readline
char	*ft_readline(char *prompt);

// tokenizer_core
void	fill_in_lex(t_info *info, int token, char *content);

// tenizer_handlers
void	handle_redirections(t_info *info, char **str);
void	handle_words(t_info *info, char **str);
void	handle_space(t_info *info, char **str);
void	handle_quotes(t_info *info, char **str);

// tokenizer_core
void	tokenizer(t_info *info, char *str);

// exapansion_core
void	expansion(t_info *info);

// expantion_utils
int		is_valid_dollar_followup(char c);
void	append_to_buffer(char *buf, const char *append, int *current_len);
char	*get_envp_value(t_list *list, char *str);
char	*get_envp_key(char *str);

// delete_sep_token
void	delete_token_sep(t_info *info);

// here_doc
int		here_doc(t_cmd *new_node, char *here_doc_str);

// grouping_core
void	grouping(t_info *info);

// grouping_cmd_lst
t_cmd	*new_cmd(void);
void	add_back_cmd(t_cmd **cmd_ptr, t_cmd *new_node);
void	cmd_free(t_cmd **cmd);

// grouping_utils
int		check_sintax_unexpected_token(t_token *token);
int		e_index_check(int index);
char	**add_to_array(char **arr, char *new_str);
int		redir(t_cmd *new_node, int *fd_in, t_token **token_ptr);

// refill_envp_lst
void	ft_t_lstclear(t_list **envp_lst);
void	refill_envp_lst(t_info *info, char **new_envp);

/****Envp utils*******/
//For envp manipulation
int		ft_init_envp(t_info *info, char **envp);
void	ft_free_matrix(char **str);
char	**ft_copy_matrix(char **envp);
int		ft_matrix_size(char **envp);

//For export
void	ft_modify_variable(char **envp, char *tuple);
char	**ft_add_to_matrix(char **envp, char *tuple);
int		ft_empty_line(char *string);
char	**ft_init_matrix_nil(int size);
char	*ft_high_string(void);
int		ft_max_len(char *string1, char *string2);
int		ft_not_in_matrix(char *string, char **envp);
char	**ft_order_env(char **envp);
void	ft_print_export(t_info *info);
int		ft_double_assign(char *str);

//For unset
void	ft_delete_variable(t_info *info, char *tuple);

/*********cd utils*************/
void	ft_free_dirs(char *s1, char *s2, char *s3);
int		ft_cd_home(t_info *info);
int		ft_cd_lastdir(t_info *info);
int		ft_cd_home_relat(t_info *info, char *string);
int		ft_cd_other(t_info *info, char *string);

/****Tuple utils*******/
int		ft_var_size(char *tuple);
int		ft_contains(char *tuple, char *envp_tuple);
int		ft_env_exists(char *tuple, char **envp);
int		ft_var_exists(char *variable, char *envp_tuple);
char	*ft_get_env_value(t_info *info, char *tuple);
char	*ft_store_value(char *tuple);
int		ft_contains(char *envp_tuple, char *tuple);

/*******BUILTIN FUNCTIONS***********/

//Functions
int		pwd(char **cmd);
int		ft_pwd(void);

int		export(t_info *info, char **cmd);
int		ft_export(t_info *info, char *tuple);
void	ft_print_export(t_info *info);

int		unset(t_info *info, char **cmd);
int		ft_unset(t_info *info, char *tuple);

int		env(t_info *info, char **cmd);
int		ft_env(t_info *info);

int		cd(t_info *info, char **cmd);
int		ft_cd(t_info *info, char **cmd);

int		exit1(t_info *info, char **cmd);
int		ft_exit(t_info *info, int option);

int		echo(char **cmd);
int		ft_echo(char **cmd);

/****PIPEX*******/
//Aux functions
int		ft_print_error(char *error);
char	*abs_bin_path(char *cmd, char **envp);
char	**get_paths(char *envp[]);
t_cmd	*init_cmd_node(int fd_in1, int fd_out1, char **argv);
t_cmd	*create_list(char *str, int fdin, int fdout);
int		ft_is_builtin(t_info *info, char *str);

//Atomic functions
int		ft_exec_cmd(t_info *info, t_cmd *node);
int		ft_pipex(t_info *info);

#endif
