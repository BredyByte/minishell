/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:31:17 by dbredykh          #+#    #+#             */
/*   Updated: 2023/10/31 09:36:04 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_readline(void)
{
	char	*str;

	str = readline("minishell-1.0$ ");
	if (!str || *str == '\0')
		return (NULL);
	add_history(str);
	return (str);
}
