/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:47:34 by dbredykh          #+#    #+#             */
/*   Updated: 2023/10/09 14:50:55 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_int_key(t_list *node)
{
	return (*((int *)node->key));
}

char	*get_str_key(t_list *node)
{
	return ((char *)node->key);
}
