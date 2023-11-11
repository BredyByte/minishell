/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:00:19 by regea-go          #+#    #+#             */
/*   Updated: 2023/11/08 18:50:19 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lst_size(t_cmd *lst)
{
	int		size;
	t_cmd	*itr;

	size = 0;
	itr = lst;
	if (lst == 0)
		return (0);
	while (itr != 0)
	{
		itr = itr->next;
		size++;
	}
	return (size);
}

void	ft_redir_fds(int og_stdin, int og_stdout)
{
	dup2(og_stdin, STDIN);
	dup2(og_stdout, STDOUT);
	perror(EXEC_ERROR);
}

int	ft_exec_builtin(t_info *info, char **cmd)
{
	if (ft_strncmp("cd", cmd[0], 2) == 0 && cmd[0][2] == '\0')
		return (cd(info, cmd));
	else if (ft_strncmp("echo", cmd[0], 4) == 0 && cmd[0][4] == '\0')
		return (echo(cmd));
	else if (ft_strncmp("env", cmd[0], 3) == 0 && cmd[0][3] == '\0')
		return (env(info, cmd));
	else if (ft_strncmp("exit", cmd[0], 4) == 0 && cmd[0][4] == '\0')
		return (exit1(info, cmd));
	else if (ft_strncmp("export", cmd[0], 6) == 0 && cmd[0][6] == '\0')
		return (export(info, cmd));
	else if (ft_strncmp("pwd", cmd[0], 3) == 0 && cmd[0][3] == '\0')
		return (pwd(cmd));
	else if (ft_strncmp("unset", cmd[0], 5) == 0 && cmd[0][5] == '\0')
		return (unset(info, cmd));
	return (COMMAND_NOT_FOUND);
}

void	ft_redir_fd_std(int fd, int std, int fd2)
{
	if (fd != NO_FD && fd != std)
	{
		if (dup2(fd2, std) < 0)
			ft_print_error(REDIR_ERROR);
		close(fd);
	}
}

int	ft_builtin(t_info *info, t_cmd *node)
{
	int	status;
	int	og_stdout;
	int	og_stdin;

	og_stdout = dup(STDOUT);
	og_stdin = dup(STDIN);
	status = 0;
	ft_redir_fd_std(node->fd_in, STDIN, node->fd_in);
	ft_redir_fd_std(node->fd_out, STDOUT, node->fd_out);
	status = ft_exec_builtin(info, node->command);
	ft_redir_fd_std(node->fd_in, STDIN, og_stdin);
	ft_redir_fd_std(node->fd_out, STDOUT, og_stdout);
	return (status);
}
