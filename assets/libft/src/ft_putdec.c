/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:49:42 by dbredykh          #+#    #+#             */
/*   Updated: 2023/06/19 16:21:30 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putdec(int n)
{
	char	*new_str;
	size_t	len;

	new_str = ft_itoa(n);
	len = ft_putstr(new_str);
	free(new_str);
	return (len);
}
