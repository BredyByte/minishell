/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_token_sep.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:35:54 by dbredykh          #+#    #+#             */
/*   Updated: 2023/10/31 10:00:14 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	del_isspace(t_token **token, t_token *prev, t_token **token_lst)
{
	t_token	*next_token;

	next_token = (*token)->next;
	free((*token)->value);
	free((*token));
	if (prev)
		prev->next = next_token;
	*token = next_token;
	if (!prev)
		*token_lst = next_token;
}

void	delete_token_sep(t_info *info)
{
	t_token	*token;
	t_token	*prev;

	prev = NULL;
	token = info->token_lst;
	while (token)
	{
		if (token->key == TOKEN_SEP)
			del_isspace(&token, prev, &info->token_lst);
		else
		{
			prev = token;
			token = token->next;
		}
	}
}
