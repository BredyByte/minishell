/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:00:41 by dbredykh          #+#    #+#             */
/*   Updated: 2023/11/01 19:35:25 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_exec_builtin(t_info *info, char **cmd)
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

int	ft_builtin(t_info *info, t_cmd *node)
{
	int	og_stdout;
	int	status;

	og_stdout = dup(STDOUT);
	status = 0;
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
	status = ft_exec_builtin(info, node->command);
	dup2(og_stdout, STDOUT);
	close(og_stdout);
	return (status);
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
		id = fork();
		if (id < 0)
			return (ft_print_error(FORK_ERROR));
		if (id == 0)
		{
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
			if (execve(abs_bin_path(node->command[0], get_paths(info->envp)),node->command, info->envp) < 0)
				return (ft_print_error(EXEC_ERROR));
		}
		else
		{
			waitpid(id, &status, 0);
			if (node->fd_in != NO_FD && node->fd_in != STDIN)
				close(node->fd_in);
			if (node->fd_out != NO_FD && node->fd_out != STDOUT)
				close(node->fd_out);
		}
		return (status);
	}
	return (EXIT_SUCCESS);
}

int	ft_pipex(t_info *info, t_cmd *list)
{
	int	status;

	status = 0;
	while (list)
	{
		status = ft_exec_cmd(info, list);
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
