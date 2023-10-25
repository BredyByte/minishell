/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:34:21 by dbredykh          #+#    #+#             */
/*   Updated: 2023/10/25 12:27:17 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_in_lex(t_info *info, int token, char *content)
{
	t_token	*current;

	current = ft_tokennew(token, content);
	if (!info->token_lst)
		ft_tokadd_front(&info->token_lst, current);
	else
		ft_tokadd_back(&info->token_lst, current);
}

void	tokenizer(t_info *info, char *str)
{
	while (*str)
	{
		if (!ft_is_special_char(*str))
			handle_words(info, &str);
		else if (ft_isspace(*str))
			handle_space(info, &str);
		else if (*str == '\'' || *str == '"')
			handle_quotes(info, &str);
		else if (*str == '>' || *str == '<')
			handle_redirections(info, &str);
		else if (*str == '|')
			fill_in_lex(info, TOKEN_PIPE, "|");
		str++;
	}
}
