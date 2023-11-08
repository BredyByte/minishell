/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:20:06 by dbredykh          #+#    #+#             */
/*   Updated: 2023/11/08 15:19:18 by dbredykh         ###   ########.fr       */
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
		if (!info->envp_lst)
			ft_lstadd_front(&info->envp_lst, current);
		else
			ft_lstadd_back(&info->envp_lst, current);
		free(key);
		free(value);
		envp++;
	}
}

void	init_envp(t_info *info, char **environ)
{
	int		count;
	char	**ptr;
	int		i;

	i = 0;
	ptr = environ;
	count = 0;
	while (*ptr++)
		count++;
	info->envp = malloc((count + 1) * sizeof(char *));
	while (i < count)
	{
		info->envp[i] = ft_strdup(environ[i]);
		i++;
	}
	info->envp[i] = NULL;
}
