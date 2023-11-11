/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:54:38 by regea-go          #+#    #+#             */
/*   Updated: 2023/11/09 11:02:14 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_str_comparator(void)
{
	char	*string;

	string = malloc (2 * sizeof(char));
	if (!string)
		return (NULL);
	string[0] = 127;
	string[1] = '\0';
	return (string);
}

char	*ft_find_min_str(char **envp, char **new_envp)
{
	char	*tmp;
	int		idx;

	tmp = ft_str_comparator();
	idx = 0;
	while (envp[idx])
	{
		if (ft_strncmp(tmp, envp[idx], ft_max_len(tmp, envp[idx])) > 0
			&& ft_not_in_matrix(envp[idx], new_envp) == TRUE)
		{
			free (tmp);
			tmp = ft_strdup(envp[idx]);
		}
		idx++;
	}
	return (tmp);
}

/**
 * @brief 
 * 
 * @param envp 
 * @return char** 
 */
char	**ft_order_env(char **envp)
{
	char	**new_envp;
	int		size;
	int		idx;

	size = ft_matrix_size(envp);
	new_envp = ft_init_matrix_nil(size);
	if (!envp)
		return (NULL);
	idx = 0;
	while (idx < size)
	{
		new_envp[idx] = ft_find_min_str(envp, new_envp);
		idx++;
	}
	new_envp[idx] = NULL;
	return (new_envp);
}

//Mbe change it so it just modifies global env
void	ft_modify_variable(char **envp, char *tuple)
{
	int	idx;

	idx = 0;
	while (envp[idx])
	{
		if (ft_contains(tuple, envp[idx]) == TRUE)
		{
			free(envp[idx]);
			envp[idx] = ft_strdup(tuple);
			return ;
		}
		idx++;
	}
	return ;
}

/**
 * @brief
 *
 * @param tuple
 */
char	**ft_add_to_matrix(char **envp, char *tuple)
{
	char	**new_envp;
	int		idx;

	new_envp = malloc((ft_matrix_size(envp) + 2) * sizeof(char *));
	idx = 0;
	while (envp[idx])
	{
		new_envp[idx] = ft_strdup(envp[idx]);
		idx++;
	}
	new_envp[idx] = ft_strdup(tuple);
	new_envp[++idx] = NULL;
	ft_free_matrix(envp);
	return (new_envp);
}
