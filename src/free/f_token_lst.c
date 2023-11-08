/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_token_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:49:11 by dbredykh          #+#    #+#             */
/*   Updated: 2023/11/07 19:16:38 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_lst(t_token **token_lst)
{
	t_token	*ptr;
	t_token	*tmp;

	if (*token_lst == NULL)
		return ;
	ptr = *token_lst;
	tmp = NULL;
	while (ptr)
	{
		tmp = ptr->next;
		free(ptr->value);
		free(ptr);
		ptr = tmp;
	}
	*token_lst = NULL;
}
