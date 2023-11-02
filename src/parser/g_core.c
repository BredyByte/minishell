/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grouping_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:02:21 by dbredykh          #+#    #+#             */
/*   Updated: 2023/11/02 18:37:54 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	conditional_new_cmd(t_cmd **new, t_cmd **cmd_lst, int key)
{
	if (!*new
		|| (*new && (*new)->command[0]
			&& !(key == TOKEN_REDIR_APPEND || key == TOKEN_REDIR_OUT)))
	{
		*new = new_cmd();
		add_back_cmd(cmd_lst, *new);
	}
}

static void	conditional_token_word(t_cmd **new,
	t_token	**token, int *e_index, int *fd_in)
{
	while (*token && (*token)->key == TOKEN_WORD)
	{
		(*new)->command = add_to_array((*new)->command, (*token)->value);
		if (!(*token)->next
			&& redir(*new, fd_in, token))
		{
			*e_index = 1;
			break ;
		}
		*token = (*token)->next;
	}
}

void	grouping(t_info *info)
{
	t_cmd	*new;
	t_token	*token;
	int		fd_in;
	int		e_index;

	fd_in = 0;
	token = info->token_lst;
	e_index = check_sintax_unexpected_token(token);
	new = NULL;
	while (token && !e_index)
	{
		conditional_new_cmd(&new, &info->cmd_lst, token->key);
		conditional_token_word(&new, &token, &e_index, &fd_in);
		if (token && redir(new, &fd_in, &token))
		{
			e_index = 1;
			break ;
		}
		else if (token)
			token = token->next;
	}
	info->status = e_index_check(e_index);
}





