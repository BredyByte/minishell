/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refill_envp_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:22:24 by dbredykh          #+#    #+#             */
/*   Updated: 2023/11/02 16:49:35 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_t_lstclear(t_list **envp_lst)
{
	t_list	*current;
	t_list	*next;

	current = *envp_lst;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
	*envp_lst = NULL;
}

void	refill_envp_lst(t_info *info, char **new_envp)
{
	if (info->envp_lst)
		ft_t_lstclear(&info->envp_lst);
	init_envp_lst(info, new_envp);
}
