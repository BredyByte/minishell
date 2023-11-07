/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_cmd_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:47:45 by dbredykh          #+#    #+#             */
/*   Updated: 2023/11/07 19:20:17 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_and_remove(t_cmd *cmd)
{
	if (cmd->fd_in != 0 && cmd->fd_in != 1)
		close(cmd->fd_in);
	if (cmd->fd_out != 0 && cmd->fd_out != 1)
		close(cmd->fd_out);
	if (cmd->here_doc)
		free(cmd->here_doc);
}

void	free_cmd_lst(t_cmd **cmd)
{
	t_cmd	*ptr;
	t_cmd	*tmp;

	if (*cmd == NULL)
		return ;
	ptr = *cmd;
	tmp = NULL;
	while (ptr)
	{
		tmp = ptr->next;
		free(ptr->command);
		close_and_remove(ptr);
		free(ptr);
		ptr = tmp;
	}
	*cmd = NULL;
}
