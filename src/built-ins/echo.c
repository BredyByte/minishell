/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:00:55 by regea-go          #+#    #+#             */
/*   Updated: 2023/11/15 12:29:57 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_nl(char **str)
{
	if (!str[1])
		return (FALSE);
	if (ft_strncmp(str[1], "-n", 2) == 0 && str[1][2] == '\0')
		return (TRUE);
	return (FALSE);
}

int	ft_echo(char **cmd)
{
	int		idx;
	int		is_nl;

	is_nl = ft_is_nl(cmd);
	idx = 1;
	if (!cmd[1])
	{
		ft_putstr_fd("\n", STDOUT);
		return (EXIT_SUCCESS);
	}
	while (ft_strncmp(cmd[idx], "-n", 2) == 0 && cmd[idx][2] == '\0')
		idx++;
	while (cmd[idx])
	{
		ft_putstr_fd(cmd[idx], STDOUT);
		idx++;
	}
	if (ft_is_nl(cmd) == FALSE)
		write(STDOUT, "\n", 1);
	return (EXIT_SUCCESS);
}

int	echo(char **cmd)
{
	if (ft_strncmp(cmd[0], "echo", 4) == 0 && cmd[0][4] == '\0')
		return (ft_echo(cmd));
	else
		return (BAD_ARGS);
}
