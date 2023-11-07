/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:23:14 by regea-go          #+#    #+#             */
/*   Updated: 2023/11/06 15:15:46 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delete_variable(t_info *info, char *tuple)
{
	char	**new_envp;
	int		idx;
	int		idx2;

	new_envp = malloc(ft_matrix_size(info->envp) * sizeof(char *));
	idx = 0;
	idx2 = 0;
	while (info->envp[idx2])
	{
		if (ft_contains(info->envp[idx2], tuple) == FALSE)
		{
			new_envp[idx] = ft_strdup(info->envp[idx2]);
			idx++;
		}
		idx2++;
	}
	new_envp[idx] = NULL;
	ft_free_matrix(info->envp);
	info->envp = ft_copy_matrix(new_envp);
	return ;
}

int	ft_unset(t_info *info, char *tuple)
{
	if (ft_env_exists(tuple, info->envp) == TRUE)
	{
		ft_delete_variable(info, tuple);
		refill_envp_lst(info, info->envp);
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_SUCCESS);
}

int	unset(t_info *info, char **cmd)
{
	if (ft_strncmp(cmd[0], "unset", 5) == 0 && cmd[0][5] == '\0')
	{
		if (cmd[1])
			return (ft_unset(info, cmd[1]));
		else
			return (EXIT_SUCCESS);
	}
	else
		return (ft_print_error("Bad command"));
}
