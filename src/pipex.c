/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:37:09 by regea-go          #+#    #+#             */
/*   Updated: 2023/10/31 15:37:57 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	ft_exec_builtin(t_info *info, char **cmd)
{
	if (ft_strncmp("cd", cmd[0], 2) == 0 && cmd[0][2] == '\0')
		return (cd(info, cmd));
	else if (ft_strncmp("echo", cmd[0], 4) == 0  & cmd[0][4] == '\0')
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

//Dont forget error check for every dup2 and stuff
//We have to check if the fds are -2 (which are not initialized) or -1 (it means that the file doesnt exists)
int	ft_exec_cmd(t_info *info, t_cmd *node)
{
	pid_t	id;
	int		status;
	int		og_stdout;

	//Remove this 
	printf(GREEN"cmd     fd_in   fd_out\n"RESET);
	if (node && node->command[0])
    	printf(GREEN"%s      %i      %i     \n\n"RESET, node->command[0], node->fd_in, node->fd_out);
	status = 0;
	if (!node->command[0])
		return (EXIT_SUCCESS);
	else if (ft_is_builtin(info, node->command[0]) == TRUE)
	{
		og_stdout = dup(STDOUT);
		if (node->fd_in != NO_FD && node->fd_in != STDIN)
		{
			if (dup2(node->fd_in, STDIN) < 0)
				return (ft_print_error("Ruben: "REDIR_ERROR));
			close(node->fd_in);
		}
		if (node->fd_out != NO_FD && node->fd_out != STDOUT)
		{
			if (dup2(node->fd_out, STDOUT) < 0)
				return (ft_print_error("Ruben: "REDIR_ERROR));
			close(node->fd_out);
		}
		status = ft_exec_builtin(info, node->command);
		/***********I THINK THIS IS REDUNDANT**********************/
		//if (status == EXIT_ERROR)
		//{
		//	dup2(og_stdout, STDOUT);
		//	return (ft_print_error("Ruben: "EXEC_ERROR));
		//}
		dup2(og_stdout, STDOUT);
		close(og_stdout);
		return (status);
	}	
	else
	{	
		id = fork();
		if (id < 0)
			return (ft_print_error("Ruben: "FORK_ERROR));
		if (id == 0)
		{
			if (node->fd_in != NO_FD && node->fd_in != STDIN)
			{
				if (dup2(node->fd_in, STDIN) < 0)
					return (ft_print_error("Ruben: "REDIR_ERROR));
				close(node->fd_in);
			}
			if (node->fd_out != NO_FD && node->fd_out != STDOUT)
			{
				if (dup2(node->fd_out, STDOUT) < 0)
					return (ft_print_error("Ruben: "REDIR_ERROR));
				close(node->fd_out);
			}
			if (execve(abs_bin_path(node->command[0], get_paths(info->envp)),node->command, info->envp) < 0)
				return (ft_print_error("Ruben: "EXEC_ERROR));
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
	int i = 0;
	int status;
	
	status = 0;
	while (list)
	{
		printf(GREEN"\nRuben:\n\n"RESET);
		status = ft_exec_cmd(info, list);
		if (status != EXIT_SUCCESS)				// I need to check the behaviour of chained failures
		{										// See how to implement exit here, RN we have EXIT_EXIT 3 to check exit cmd 
			info->status = status;
			return (status);
		}
		list = list->next;
		i++;
		printf("\n");
	}
	printf("\n");
	return (EXIT_SUCCESS);
}