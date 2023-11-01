/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:31:17 by dbredykh          #+#    #+#             */
/*   Updated: 2023/11/01 14:20:21 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_readline(char *prompt)
{
	char	*str;

	str = readline(prompt);
	if (!str || *str == '\0')
		return (NULL);
	return (str);
}
