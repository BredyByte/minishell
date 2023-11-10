/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:08:44 by regea-go          #+#    #+#             */
/*   Updated: 2023/11/09 17:57:08 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_dirs(char *s1, char *s2, char *s3)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
	s1 = NULL;
	s2 = NULL;
	s3 = NULL;
}

int	ft_cd(t_info *info, char **cmd)
{
	if (cmd[1] == NULL)
		return (ft_cd_home(info));
	else if (ft_strncmp(cmd[1], "-", 1) == 0)
	{
		if (cmd[1][1] == '\0')
			return (ft_cd_lastdir(info));
		else
			return (EXIT_SUCCESS);
	}
	else if (ft_strncmp(cmd[1], "~", 1) == 0)
	{
		if (ft_strlen(cmd[1]) == 1)
			return (ft_cd_home(info));
		else if (ft_strlen(cmd[1]) > 1)
			return (ft_cd_home_relat(info, cmd[1]));
	}
	else if (ft_strncmp(cmd[1], "..", 2) == 0)
		return (ft_cd_other(info, cmd[1]));
	else if (ft_strncmp(cmd[1], ".", 1) == 0)
		return (ft_cd_other(info, cmd[1]));
	else if (ft_strncmp(cmd[1], "/", 1) == 0)
		return (ft_cd_other(info, cmd[1]));
	else
		return (ft_cd_other(info, cmd[1]));
	return (EXIT_ERROR);
}

int	cd(t_info *info, char **cmd)
{
	int	status;

	status = 0;
	if (ft_strncmp(cmd[0], "cd", 2) == 0 && cmd[0][2] == '\0')
	{
		status = ft_cd(info, cmd);
		refill_envp_lst(info, info->envp);
		return (status);
	}
	else
	{
		ft_putendl_fd("Bad command", 2);
		return (EXIT_ERROR);
	}
}
