/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:51:27 by dbredykh          #+#    #+#             */
/*   Updated: 2023/10/31 09:43:10 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	last = *lst;
	if (last == NULL)
		ft_lstadd_front(lst, new);
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}

static t_token	*ft_toklast(t_token *lst)
{
	t_token	*temp;

	if (!lst)
		return (0);
	temp = (t_token *)lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	ft_tokadd_back(t_token **lst, t_token *new)
{
	t_token	*last;

	last = *lst;
	if (last == NULL)
		ft_tokadd_front(lst, new);
	else
	{
		last = ft_toklast(*lst);
		last->next = new;
	}
}
