/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:28:05 by dbredykh          #+#    #+#             */
/*   Updated: 2023/11/11 12:29:38 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <dirent.h>
# include <stdint.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../assets/libft/include/libft.h"
# include "defines.h"
# include <fcntl.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <readline/history.h>
# include <readline/readline.h>

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
	int				status;
	int				exit;
	t_token			*token_lst;
	t_cmd			*cmd_lst;
}					t_info;

int	g_batch_flag;

// free_fn
void	free_all(t_info *info);
void	free_token_lst(t_token **token_lst);
void	free_cmd_lst(t_cmd **cmd);

// init_utils
void	init_envp_lst(t_info *info, char **envp);
void	init_envp(t_info *info, char **environ);

// ft_readline
char	*ft_readline(char *prompt);

// refill_envp_lst
void	ft_t_lstclear(t_list **envp_lst);
void	refill_envp_lst(t_info *info, char **new_envp);

/****Tokenizer*******/
// tenizer_handlers
void	handle_redirections(t_info *info, char **str);
void	handle_words(t_info *info, char **str);
void	handle_space(t_info *info, char **str);
int		handle_quotes(t_info *info, char **str);

// tokenizer_core
int		tokenizer(t_info *info, char *str);
void	fill_in_lex(t_info *info, int token, char *content);
void	delete_token_sep(t_info *info);

/****Expansion*******/
// exapansion_core
void	expansion(t_info *info);

// expantion_utils
int		is_valid_dollar_followup(char c);
void	append_to_buffer(char *buf, const char *append, int *current_len);
char	*get_envp_value(t_list *list, char *str);
char	*get_envp_key(char *str);

/****Grouping*******/
// grouping_core
void	grouping(t_info *info);
int		here_doc(t_cmd *new_node, char *here_doc_str);
int		redir(t_cmd *new_node, int *fd_in, t_token **token_ptr);

// grouping_cmd_lst
t_cmd	*new_cmd(void);
void	add_back_cmd(t_cmd **cmd_ptr, t_cmd *new_node);

// grouping_utils
int		check_sintax_unexpected_token(t_token *token);
int		e_index_check(int index);
char	**add_to_array(char **arr, char *new_str);
void	cmd_lst_change_out(t_cmd *cmd);
int		is_redir_out_last(t_token *token);

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
char	*ft_str_comparator(void);
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
int		ft_is_builtin(t_info *info, char *str);
int		ft_exec_builtin(t_info *info, char **cmd);
int		ft_builtin(t_info *info, t_cmd *node);
void	ft_redir_fd_std(int fd, int std, int fd2);
void	ft_redir_fds(int og_stdin, int og_stdout);
int		ft_lst_size(t_cmd *lst);

//Atomic functions
int		ft_exec_cmd(t_info *info, t_cmd *node, int cmd_number);
int		ft_pipex(t_info *info);

/******SIGNALS*********/
void	ft_signals(void);

#endif
