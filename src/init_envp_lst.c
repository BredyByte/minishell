/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:17:42 by dbredykh          #+#    #+#             */
/*   Updated: 2023/10/07 18:00:55 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_envp_lst(t_info *info, char **envp)
{
	t_list	*current;
	char	*delimiter;
	char	*key;
	char	*value;

	while (*envp)
	{
		delimiter = ft_strchr(*envp, '=');
		if (!delimiter)
		{
			envp++;
			continue ;
		}
		key = ft_strndup(*envp, delimiter - *envp);
		value = ft_strdup(delimiter + 1);
		current = ft_lstnew(key, value);
		if (!info->envp_list)
			ft_lstadd_front(&info->envp_list, current);
		else
			ft_lstadd_back(&info->envp_list, current);
		free(key);
		free(value);
		envp++;
	}
}
