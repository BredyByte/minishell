/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:54:44 by regea-go          #+#    #+#             */
/*   Updated: 2023/11/06 15:16:23 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_var_exists(char *variable, char *envp_tuple)
{
	int	size;

	size = ft_strlen(variable);
	if (ft_strncmp(envp_tuple, variable, size) == 0
		&& (envp_tuple[size] == '='))
		return (TRUE);
	else
		return (FALSE);
}

char	*ft_get_env_value(t_info *info, char *tuple)
{
	char	*env;
	int		idx;

	env = NULL;
	idx = 0;
	while (info->envp[idx])
	{
		if (ft_var_exists(tuple, info->envp[idx]) == TRUE)
		{
			env = ft_store_value(info->envp[idx]);
			return (env);
		}
		idx++;
	}
	return (env);
}

char	*ft_store_value(char *tuple)
{
	char	*value;
	int		idx;

	value = NULL;
	idx = 0;
	while (tuple[idx] != '=' && tuple[idx] != '\0')
		idx++;
	idx++;
	if (tuple[idx] == '\0')
		return (NULL);
	value = ft_substr(tuple, idx, ft_strlen(tuple) - idx);
	return (value);
}

int	ft_var_size(char *tuple)
{
	int	idx;

	idx = 0;
	while (tuple[idx] != '=' && tuple[idx] != '\0')
		idx++;
	return (idx);
}
