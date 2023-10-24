/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:34:21 by dbredykh          #+#    #+#             */
/*   Updated: 2023/10/24 13:01:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_in_lex(int token, char *content)
{
	t_token	*current;

	current = ft_tokennew(token, content);
	if (!info->token_lst)
		ft_tokadd_front(&info->token_lst, current);
	else
		ft_tokadd_back(&info->token_lst, current);
}

void	tokenizer(char *str)
{
	while (*str)
	{
		if (!ft_is_special_char(*str))
			handle_words(&str);
		else if (ft_isspace(*str))
			handle_space(&str);
		else if (*str == '\'' || *str == '"')
			handle_quotes(&str);
		else if (*str == '>' || *str == '<')
			handle_redirections(&str);
		else if (*str == '|')
			fill_in_lex(TOKEN_PIPE, "|");
		str++;
	}
}
