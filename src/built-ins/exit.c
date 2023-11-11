/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:18:11 by regea-go          #+#    #+#             */
/*   Updated: 2023/11/10 13:06:43 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//We shall see if we receive a string or a num;
//Either we convert the string or we operate with the int
//If no int with exit call, just put a 0

static int	ft_isnum(char *str)
{
	size_t	size;

	size = 0;
	if (!str)
		return (FALSE);
	while (str[size] != '\0')
	{
		if (ft_isdigit(str[size]) == FALSE)
			return (FALSE);
		size++;
	}
	return (TRUE);
}

int	ft_exit(t_info *info, int option)
{
	int	value;

	value = option % 256;
	info->status = value;
	info->exit = 1;
	return (value);
}

int	exit1(t_info *info, char **cmd)
{
	ft_putendl_fd("exit", STDOUT);
	if (ft_strncmp(cmd[0], "exit", 4) == 0 && cmd[0][4] == '\0')
	{
		if (!cmd[1])
			return (ft_exit(info, 0));
		else if (ft_isnum(cmd[1]) == FALSE)
		{
			ft_putendl_fd("Bash: exit: numeric argument required", 2);
			return (ft_exit(info, 255));
		}
		else if (cmd[1] && cmd[2] != NULL)
		{
			ft_putendl_fd("Bash: exit: too many arguments", 2);
			return (EXIT_ERROR);
		}
		else
			return (ft_exit(info, ft_atoi(cmd[1])));
	}
	else
	{
		ft_print_error("Bad command");
		return (BAD_ARGS);
	}
}
