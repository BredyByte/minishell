/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:24:40 by regea-go          #+#    #+#             */
/*   Updated: 2023/11/11 15:18:47 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_contains(char *envp_tuple, char *tuple)
{
	int	size;

	size = ft_var_size(tuple);
	if (ft_strncmp(envp_tuple, tuple, size) == 0
		&& ((envp_tuple[size] == '=') || (envp_tuple[size] == '\0')))
		return (TRUE);
	else
		return (FALSE);
}

int	ft_env_exists(char *tuple, char **envp)
{
	int	idx;

	idx = 0;
	while (envp[idx])
	{
		if (ft_contains(envp[idx], tuple) == TRUE)
			return (TRUE);
		idx++;
	}
	return (FALSE);
}
