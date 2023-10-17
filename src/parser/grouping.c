/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grouping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:02:21 by dbredykh          #+#    #+#             */
/*   Updated: 2023/10/17 16:19:55 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static t_group	*ft_newgroup(t_cmd *cmd, int group_type)
{
	t_group	*new_group;

	new_group = malloc(sizeof(t_group));
	if (!new_group)
		return (NULL);
	new_group->cmd = cmd;
	new_group->grout_type = group_type;
	new_group->next = NULL;
	return (new_group);
}

static void	add_to_end(t_info *info, t_group *new_group)
{
	t_group	*last_group;

	last_group = info->group_lst;
	while (last_group->next)
		last_group = last_group->next;
	last_group->next = new_group;
	new_group->next = NULL;
}

void	group_init(t_info *info, t_token *token)
{
	t_token	*ptr;
	t_token	*tmp;
	t_group	*group;

	ptr = token;
	tmp = info->token_lst;
	group = ft_newgroup(cmd_lst, group_type);
	if (!info->envp_lst)
		group->next = info->group_lst;
		info->group_lst = group;
	else
		add_to_end(info, group);
} */

void	grouping(t_info *info)
{
	t_token	*ptr;
	int		cmd_len;

	ptr = info->token_lst;
	cmd_len = 0;
	while (ptr)
	{
		if (ptr->key == TOKEN_PIPE
			|| ptr->key == TOKEN_IF_AND
			|| ptr->key == TOKEN_IF_OR)
			group_init(info, ptr);
		cmd_len++;
		ptr = ptr->next;
	}
	if (!ptr)
		group_init(info, NULL_GROUP);
	return ;
}
