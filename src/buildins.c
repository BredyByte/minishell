/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:54:52 by dbredykh          #+#    #+#             */
/*   Updated: 2023/10/07 12:33:32 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	buildin_echo(t_list *list, t_info *info)
{
	(void) list;
	(void) info;
	return (0);
}

int	buildin_cd(t_list *list, t_info *info)
{
	(void) list;
	(void) info;
	return (0);
}

int	buildin_pwd(t_list *list, t_info *info)
{
	(void) list;
	(void) info;
	return (0);
}

int	buildin_export(t_list *list, t_info *info)
{
	(void) list;
	(void) info;
	return (0);
}

int	buildin_unset(t_list *list, t_info *info)
{
	(void) list;
	(void) info;
	return (0);
}
