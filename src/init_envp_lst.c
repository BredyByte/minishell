/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:17:42 by dbredykh          #+#    #+#             */
/*   Updated: 2023/10/07 17:02:08 by dbredykh         ###   ########.fr       */
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
		delimiter = strchr(*envp, '=');
		if (!delimiter)
		{
			envp++;
			continue ;
		}
		key = strndup(*envp, delimiter - *envp); // Извлекаем ключ
		value = strdup(delimiter + 1); // Извлекаем значение
		if (!info->envp_list) // Если это первый элемент списка
		{
			info->envp_list = ft_lstnew(key, value);
			current = info->envp_list;
		}
		else
		{
			current->next = ft_lstnew(key, value);
			current = current->next;
		}

		free(key);
		free(value);
		envp++;
	}
}
