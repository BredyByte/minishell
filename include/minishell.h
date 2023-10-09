/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 15:33:03 by dbredykh          #+#    #+#             */
/*   Updated: 2023/10/09 11:48:48 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../assets/libft/include/libft.h"
# include "tokens.h"

typedef struct s_info t_info;
typedef int			(*t_builtin_ptr)(t_list *, t_info *);

typedef struct s_info
{
	t_builtin_ptr	builtins[7];
	char			*reserved_words[7];
	char			**envp;
	t_list			*envp_lst;
	/*
		Односвязанный лист со всеми переменными окружения key = value.
		Eсли небыло произведено никаких опираций над листом то пересобирать envp не нужно,
		и так мы экономим ресурмы, как только добавляем новую перемнную,
		или изменяем стару, то меняем envp_f == 1 и envp пересобирается.
	 */
	int				envp_f;
	/*
		Флаг, в зависимости от которого мы будем пересобирать массив envp или нет
		execve имеет параметр переменной окруждения,
		и мы туда ее будем отправлять,
		если флаг envp_f == 1 то нужно пересобрать envp в противном случае отправляем указатель на массив
	*/
	char			exit_f;
	// Флаг для выхода из программы;
	int				status;
	/*
		для $?. Так как все команды будут исполняться в подпроцессах за иссключением билтинов.
		Сигналы этих команд обрабатываться будут иным способом, будем смотреть статус выхода процесса
		waitpid(pid, &status, 0);
		WIFSIGNALED(status) - макросс проверки (true / false) завершился ли процесс сигналом как например сигнал SIGSEGV;
		WTERMSIG(status) - позволяет узнать сигнал который завершил процесс;
		WIFEXITED(status) -	возвращает истинное значение, это означает, что дочерний процесс завершился нормально (вызвал  exit()) - можно вызвать WEXITSTATUS чтобы получить код выхода;
		WEXITSTATUS(status) - макрос возвращает код завершения процесса;
	*/
	/*
		int status;
		waitpid(pid, &status, 0);
		&status - статус выхода из дочернего процесса который мы ожидаем
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
			execve(команда и аргументы);
			exit(127);
		}
		} else {
			waitpid(child_pid, &status, 0);
			if (WIFEXITED(status)) {
				int exit_status = WEXITSTATUS(status);
			}
		}
	 */
	t_list			*token_lst;
	// лексер разбивает все на токены, и кладет их в лист, тього получается односвязанный лист с key = TOKEN_MACROS, value = token_value;
	// t_lgroup		groups;
	// в случае cat >file | cat <file && pwd: t_lgroup: t_list *tokens, &&, t_list * tokens
	// лист для логическиих групп, тоесть группы команд разделенные логическими операторами && || ;
}					t_info;

// buildins
int	buildin_echo(t_list *list, t_info *info);
int	buildin_cd(t_list *list, t_info *info);
int	buildin_pwd(t_list *list, t_info *info);
int	buildin_export(t_list *list, t_info *info);
int	buildin_unset(t_list *list, t_info *info);
int	buildin_env(t_list *list, t_info *info);
int	buildin_exit(t_list *list, t_info *info);

// minishell_lounch

void	minishell_lounch(t_info *info);

// ft_readline

char	*ft_readline(void);

// lexer

void	ft_lexer(t_info *info, char *str);

#endif
