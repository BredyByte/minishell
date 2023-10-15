/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:33:40 by dbredykh          #+#    #+#             */
/*   Updated: 2023/10/15 13:26:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*d;
	size_t	len;

	len = ft_strlen(s);
	if (len < n)
		n = len;
	d = (char *)malloc(n + 1);
	if (!d)
		return (NULL);
	ft_memcpy(d, s, n);
	d[n] = '\0';
	return (d);
}
