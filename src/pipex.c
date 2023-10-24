/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:37:09 by regea-go          #+#    #+#             */
/*   Updated: 2023/10/24 14:57:42 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	ft_exec_builtin(char **cmd)
{
	printf("%s\n", cmd[0]);
	if (ft_strncmp("cd", cmd[0], 2) == 0)
		return (cd(cmd));
	else if (ft_strncmp("echo", cmd[0], 4) == 0)
		return (echo(cmd));
	else if (ft_strncmp("env", cmd[0], 3) == 0)
		return (env(cmd));
	else if (ft_strncmp("exit", cmd[0], 4) == 0)
		return (exit1(cmd));
	else if (ft_strncmp("export", cmd[0], 6) == 0)
		return (export(cmd));
	else if (ft_strncmp("pwd", cmd[0], 3) == 0)
		return (pwd(cmd));
	else if (ft_strncmp("unset", cmd[0], 5) == 0)
		return (unset(cmd));
	return (EXIT_ERROR);
}

//Dont forget error check for every dup2 and stuff
//We have to check if the fds are -2 (which are not initialized) or -1 (it means that the file doesnt exists)
int	ft_exec_cmd(t_cmd *node)
{
	pid_t	id;
	//Remove this 
	printf("                    cmd     fd_in   fd_out\n");
    printf("Value of the node:  %s      %i      %i     \n", node->command[0], node->fd_in, node->fd_out);
		/****We need to change this funct to take global var******/
	if (ft_is_builtin(node->command[0]) == TRUE)
	{
		printf("Yep, its a builtin\n");	//<----- Remove this 
		if (node->fd_out != NO_FD)
			dup2(node->fd_out, STDOUT);
		if (ft_exec_builtin(node->command) == EXIT_ERROR)
			return (ft_print_error("Ruben: "EXEC_ERROR));
		return (EXIT_SUCCESS);
	}	
	else
	{	
		printf("Nope, its not a builtin\n");		//<------- Remove this 
		id = fork();
		if (id < 0)
			return (ft_print_error("Ruben: "FORK_ERROR));
		if (id == 0)
		{
			if (node->fd_in != NO_FD)
			{
				if (dup2(node->fd_in, STDIN) < 0)
					return (ft_print_error("Ruben: "REDIR_ERROR));	
				
			}
			if (node->fd_out != NO_FD)
			{
				if (dup2(node->fd_out, STDOUT) < 0)
					return (ft_print_error("Ruben: "REDIR_ERROR));
				
			}
			if (execve(abs_bin_path(node->command[0], get_paths(info->envp)),node->command, info->envp) < 0)
				return (ft_print_error("Ruben: "EXEC_ERROR));
		}
		else
		{
			waitpid(id, NULL, WNOHANG);
			if (node->fd_in != 0)
				close(node->fd_in);
			if (node->fd_out != 1)
				close(node->fd_out);
		}
		return (EXIT_SUCCESS);
	}
}

void	ft_pipex(t_cmd *list)
{
	int i = 0;
	while (list)
	{
		ft_exec_cmd(list);
		printf("Ejecucion nº: %i\n", i);
		list = list->next;
		i++;
	}
}