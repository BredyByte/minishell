/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_all.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:52:53 by dbredykh          #+#    #+#             */
/*   Updated: 2023/11/07 19:16:25 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_envp_lst(t_list **envp_lst)
{
	t_list	*ptr;
	t_list	*tmp;

	ptr = *envp_lst;
	tmp = NULL;
	while (ptr)
	{
		tmp = ptr->next;
		free(ptr->key);
		free(ptr->value);
		free(ptr);
		ptr = tmp;
	}
	*envp_lst = NULL;
}


void	free_all(t_info *info)
{
	int	i;

	i = 0;
	while (info->reserved_words[i])
		free(info->reserved_words[i++]);
	i = 0;
	while (info->envp[i])
		free(info->envp[i++]);
	free(info->envp);
	free_envp_lst(&info->envp_lst);
	if (info->token_lst)
		free_token_lst(&info->token_lst);
	if (info->cmd_lst)
		free_cmd_lst(&info->cmd_lst);
	free(info);
}
