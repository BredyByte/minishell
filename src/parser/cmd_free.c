/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:48:27 by dbredykh          #+#    #+#             */
/*   Updated: 2023/11/02 16:54:16 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_command(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->command[i])
		free(cmd->command[i++]);
	free(cmd->command);
}

static void	close_and_remove(t_cmd *cmd)
{
	if (cmd->fd_in != 0 && cmd->fd_in != 1)
		close(cmd->fd_in);
	if (cmd->fd_out != 0 && cmd->fd_out != 1)
		close(cmd->fd_out);
	if (cmd->here_doc)
	{
		free(cmd->here_doc);
		unlink("/var/tmp/.temp.txt");
	}
}

void	cmd_free(t_cmd **cmd)
{
	t_cmd	*ptr;
	t_cmd	*tmp;

	ptr = *cmd;
	tmp = NULL;
	while (ptr)
	{
		tmp = ptr->next;
		free_command(ptr);
		close_and_remove(ptr);
		free(ptr);
		ptr = tmp;
	}
	*cmd = NULL;
}
