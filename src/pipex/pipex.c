/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:37:09 by regea-go          #+#    #+#             */
/*   Updated: 2023/11/11 20:05:26 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_child_process(t_info *info, t_cmd *node)
{
	int		og_stdin;
	int		og_stdout;
	char	*tmp;
	int		status;
	char	**paths;

	tmp = NULL;
	paths = NULL;
	og_stdin = dup(STDIN);
	og_stdout = dup(STDOUT);
	status = 0;
	ft_redir_fd_std(node->fd_in, STDIN, node->fd_in);
	ft_redir_fd_std(node->fd_out, STDOUT, node->fd_out);
	paths = get_paths(info->envp);
	tmp = abs_bin_path(node->command[0], paths);
	if (!tmp)
		exit(COMMAND_NOT_FOUND);
	if (execve(tmp, node->command, info->envp) < 0)
	{
		free(tmp);
		ft_free_matrix(paths);
		ft_redir_fds(og_stdin, og_stdout);
		exit(EXIT_ERROR);
	}
	return (status);
}

void	ft_close_fds(t_cmd *node)
{
	if (node->fd_in != NO_FD && node->fd_in != STDIN)
		close(node->fd_in);
	if (node->fd_out != NO_FD && node->fd_out != STDOUT)
		close(node->fd_out);
}

int	ft_fork_funct(t_info *info, t_cmd *node, int cmd_number)
{
	int		status;
	pid_t	id;

	status = NO_STAT;
	id = fork();
	if (id == 0)
	{
		if (ft_is_builtin(info, node->command[0]) == TRUE
			&& cmd_number != 0)
		{
			status = ft_builtin(info, node);
			exit (status);
		}
		else
			ft_child_process(info, node);
	}
	else
	{
		waitpid(id, &status, 0);
		ft_close_fds(node);
	}
	return (WEXITSTATUS(status));
}

int	ft_exec_cmd(t_info *info, t_cmd *node, int cmd_number)
{
	int	status;

	status = 0;
	if (!node->command[0])
		return (EXIT_SUCCESS);
	else if (ft_is_builtin(info, node->command[0]) == TRUE && cmd_number == 0)
	{
		status = ft_builtin(info, node);
		ft_close_fds(node);
		return (status);
	}
	else
	{
		g_batch_flag = 1;
		return (ft_fork_funct(info, node, cmd_number));
	}
}

int	ft_pipex(t_info *info)
{
	t_cmd	*list;
	int		status;
	int		cmd_number;

	list = info->cmd_lst;
	status = 0;
	cmd_number = 0;
	if (ft_lst_size(list) > 1)
		cmd_number = 1;
	while (list)
	{
		status = ft_exec_cmd(info, list, cmd_number);
		g_batch_flag = 0;
		info->status = status;
		list = list->next;
		cmd_number++;
	}
	return (EXIT_SUCCESS);
}
