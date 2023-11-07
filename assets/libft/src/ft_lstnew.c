/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 15:55:39 by dbredykh          #+#    #+#             */
/*   Updated: 2023/11/07 19:12:36 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *key, void *value)
{
	t_list	*new_list;

	new_list = malloc(sizeof(t_list));
	if (!new_list)
		return (NULL);
	new_list->key = ft_strdup(key);
	new_list->value = ft_strdup(value);
	new_list->next = NULL;
	return (new_list);
}

t_token	*ft_tokennew(int key, char *value)
{
	t_token	*new_list;

	new_list = malloc(sizeof(t_token));
	if (!new_list)
		return (NULL);
	new_list->key = key;
	new_list->value = ft_strdup(value);
	new_list->len = ft_strlen(new_list->value);
	new_list->next = NULL;
	return (new_list);
}
