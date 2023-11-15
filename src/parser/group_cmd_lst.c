/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_cmd_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:42:00 by dbredykh          #+#    #+#             */
/*   Updated: 2023/11/15 12:31:01 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*new_node;

	new_node = malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->command = ft_calloc(1, sizeof(char *));
	new_node->command[0] = NULL;
	new_node->fd_in = 0;
	new_node->fd_out = 1;
	new_node->next = NULL;
	return (new_node);
}

void	add_back_cmd(t_cmd **cmd_ptr, t_cmd *new_node)
{
	t_cmd	*ptr;

	ptr = *cmd_ptr;
	if (ptr == NULL)
	{
		new_node->next = *cmd_ptr;
		*cmd_ptr = new_node;
	}
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new_node;
	}
}
