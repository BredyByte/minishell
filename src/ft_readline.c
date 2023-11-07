/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:31:17 by dbredykh          #+#    #+#             */
/*   Updated: 2023/11/07 11:23:53 by regea-go         ###   ########.fr       */
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
