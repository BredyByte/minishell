/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:57:23 by dbredykh          #+#    #+#             */
/*   Updated: 2023/10/06 19:39:33 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	buildin_env(t_list *list, t_info *info)
{
	(void)list;
	(void)info;
	return (0);
}

int	buildin_exit(t_list *list, t_info *info)
{
	(void)list;
	(void)info;
	return (0);
}
