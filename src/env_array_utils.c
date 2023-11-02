/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:39:08 by regea-go          #+#    #+#             */
/*   Updated: 2023/11/01 15:00:56 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief It frees a whole matrix of chars. Sets everything to null
 * 
 * @param str 
 */
void	ft_free_matrix(char **envp)
{
	int	idx;

	idx = 0;
	while (envp[idx])
	{
		if (envp[idx])
		{
			free(envp[idx]);
			envp[idx] = NULL;
		}
		idx++;
	}
	free(envp);
	envp = NULL;
}

/**
 * @brief It returns the number of strings that a matrix has
 * 
 * @param envp 
 * @return int 
 */
int	ft_matrix_size(char **envp)
{
	int	size;

	size = 0;
	while (envp[size])
		size++;
	return (size);
}

/**
 * @brief It gets a matrix of char, copies it to another one, then frees it
 * 
 * @param envp The matrix to copy
 * @return char** The new copied matrix
 */
char	**ft_copy_matrix(char **envp)
{
	int		idx;
	char	**new_envp;

	idx = 0;
	new_envp = malloc((ft_matrix_size(envp) + 1) * sizeof(char *));
	if (!new_envp)
		return (NULL);
	while (envp[idx])
	{
		new_envp[idx] = ft_strdup(envp[idx]);
		idx++;
	}
	new_envp[idx] = NULL;
	ft_free_matrix(envp);
	return (new_envp);
}

/**
 * @brief It initializes the envp matrix of global variable
 * 
 * @param envp Env matrix from main 
 */
int	ft_init_envp(t_info *info, char **envp)
{
	int	idx;

	idx = 0;
	info->envp = (char **)malloc((ft_matrix_size(envp) + 1) * sizeof(char *));
	if (!info)
		return (EXIT_ERROR);
	while (envp[idx])
	{
		info->envp[idx] = ft_strdup(envp[idx]);
		idx++;
	}
	info->envp[idx] = NULL;
	return (EXIT_SUCCESS);
}
