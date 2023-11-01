/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:01:24 by regea-go          #+#    #+#             */
/*   Updated: 2023/11/01 14:59:26 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_info *info)
{
	char	*value;
	int		idx;

	value = NULL;
	idx = 0;
	if (info->envp == NULL)
		return (EXIT_SUCCESS);
	while (info->envp[idx])
	{
		value = ft_store_value(info->envp[idx]);
		if (value != NULL)
			printf("%s\n", info->envp[idx]);
		idx++;
		free(value);
		value = NULL;
	}
	if (value)
		free(value);
	return (EXIT_SUCCESS);
}

int	env(t_info *info, char **cmd)
{
	if (cmd[1])
	{
		ft_print_error("env");
		return (COMMAND_NOT_FOUND);
	}
	else if (ft_strncmp(cmd[0], "env", 3) == 0 && cmd[0][3] == '\0')
		return (ft_env(info));
	else
	{
		ft_putendl_fd("Bad command", 2);
		return (BAD_ARGS);
	}
}
