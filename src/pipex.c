/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:37:09 by regea-go          #+#    #+#             */
/*   Updated: 2023/11/08 15:21:26 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redir_fds(int og_stdin, int og_stdout)
{
	dup2(og_stdin, STDIN);
	dup2(og_stdout, STDOUT);
	perror(EXEC_ERROR);
}

int	ft_child_process(t_info *info, t_cmd *node)
{
	int		og_stdin;
	int		og_stdout;
	char	*tmp;
	char	**paths;

	tmp = NULL;
	paths = NULL;
	og_stdin = dup(STDIN);
	og_stdout = dup(STDOUT);
	if (node->fd_in != NO_FD && node->fd_in != STDIN)
	{
		if (dup2(node->fd_in, STDIN) < 0)
			return (ft_print_error(REDIR_ERROR));
		close(node->fd_in);
	}
	if (node->fd_out != NO_FD && node->fd_out != STDOUT)
	{
		if (dup2(node->fd_out, STDOUT) < 0)
			return (ft_print_error(REDIR_ERROR));
		close(node->fd_out);
	}
	paths = get_paths(info->envp);
	tmp = abs_bin_path(node->command[0], paths);
	if (execve(tmp, node->command, info->envp) < 0)
	{
		g_batch_flag = 0;
		return (free(tmp), ft_free_matrix(paths),
			ft_redir_fds(og_stdin, og_stdout), EXIT_ERROR);
	}
	return (EXIT_SUCCESS);
}

void	ft_close_fds(t_cmd *node)
{
	if (node->fd_in != NO_FD && node->fd_in != STDIN)
		close(node->fd_in);
	if (node->fd_out != NO_FD && node->fd_out != STDOUT)
		close(node->fd_out);
}

int	ft_exec_cmd(t_info *info, t_cmd *node)
{
	pid_t	id;
	int		status;

	status = 0;
	if (!node->command[0])
		return (EXIT_SUCCESS);
	else if (ft_is_builtin(info, node->command[0]) == TRUE)
		return (ft_builtin(info, node));
	else
	{
		g_batch_flag = 1;
		id = fork();
		if (id < 0)
			return (ft_print_error(FORK_ERROR));
		if (id == 0)
		{
			if (ft_child_process(info, node) == EXIT_ERROR)
				exit(EXIT_ERROR);
		}
		else
		{
			waitpid(id, &status, 0);
			ft_close_fds(node);
			g_batch_flag = 0;
		}
		return (status);
	}
}

int	ft_pipex(t_info *info)
{
	int		status;
	t_cmd	*list;

	list = info->cmd_lst;
	status = 0;
	while (list)
	{
		status = ft_exec_cmd(info, list);
		g_batch_flag = 0;
		if (status == EXIT_EXIT)
			return (status);
		else if (status != EXIT_SUCCESS)
		{
			info->status = status;
			return (status);
		}
		list = list->next;
	}
	return (EXIT_SUCCESS);
}
