/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:32:26 by regea-go          #+#    #+#             */
/*   Updated: 2023/11/09 11:01:42 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints env vars in "declare -x:" format if no params are passed
 *
 */
void	ft_print_export(t_info *info)
{
	int		idx;
	char	**ordered_list;

	idx = 0;
	if (info->envp == NULL)
		return ;
	ordered_list = ft_order_env(info->envp);
	while (ordered_list[idx] != NULL)
	{
		if (ft_empty_line(ordered_list[idx]) == TRUE)
			idx++;
		else
		{
			printf("declare -x %s\n", ordered_list[idx]);
			idx++;
		}
	}
	ft_free_matrix(ordered_list);
}

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
