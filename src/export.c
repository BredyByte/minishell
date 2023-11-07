/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:32:26 by regea-go          #+#    #+#             */
/*   Updated: 2023/11/06 15:16:00 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_info *info, char *tuple)
{
	if (!tuple)
	{
		ft_print_export(info);
		return (EXIT_SUCCESS);
	}
	if (ft_double_assign(tuple) == TRUE)
		return (EXIT_SUCCESS);
	if (ft_env_exists(tuple, info->envp) == TRUE)
	{
		ft_modify_variable(info->envp, tuple);
		refill_envp_lst(info, info->envp);
	}
	else
	{
		info->envp = ft_add_to_matrix(info->envp, tuple);
		refill_envp_lst(info, info->envp);
	}
	return (EXIT_SUCCESS);
}

int	export(t_info *info, char **cmd)
{
	if (ft_strncmp(cmd[0], "export", 6) == 0 && cmd[0][6] == '\0')
	{
		if (!cmd[1])
			return (ft_export(info, NULL));
		else
			return (ft_export(info, cmd[1]));
	}
	else
		return (ft_print_error("Bad command"));
}
