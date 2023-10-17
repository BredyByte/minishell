/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 15:33:03 by dbredykh          #+#    #+#             */
/*   Updated: 2023/10/17 15:29:50 by dbredykh         ###   ########.fr       */
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

typedef struct s_info	t_info;
typedef int				(*t_builtin_ptr)(t_list *, t_info *);

typedef struct s_cmd
{
	char			**command;
	int				fd_in;
	int				fd_out;
	char			*name_in;
	char			*name_out;
	int				*fd_here_doc;
	int				append_f;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_group
{
	t_cmd				*cmd_lst;
	int					grout_type;
	struct s_group		*next;
}				t_group;

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
	t_group			*group_lst;
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
void	tokenizer(t_info *info, char *str);

// tenizer_handlers

void	handle_redirections(t_info *info, char **str);
void	handle_words(t_info *info, char **str);
void	handle_space(t_info *info, char **str);
void	handle_logical(t_info *info, char **str);
void	handle_quotes(t_info *info, char **str);


void	tokenizer(t_info *info, char *str);

// casting

int		get_int_key(t_list *node);
char	*get_str_key(t_list *node);

// exapansion

void	expansion(t_info *info);

// expantion_utils

int		is_valid_dollar_followup(char c);
void	append_to_buffer(char *buf, const char *append, int *current_len);
char	*get_envp_value(t_list *list, char *str);
char	*get_envp_key(char *str);

// grouping

void	grouping(t_info *info);

#endif
