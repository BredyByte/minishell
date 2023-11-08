/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_core.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:34:21 by dbredykh          #+#    #+#             */
/*   Updated: 2023/11/08 15:32:20 by dbredykh         ###   ########.fr       */
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

int	tokenizer(t_info *info, char *str)
{
	char	*tmp;
	int		res_quotes;

	tmp = str;
	res_quotes = 0;
	while (*tmp)
	{
		if (!ft_is_special_char(*tmp))
			handle_words(info, &tmp);
		else if (ft_isspace(*tmp))
			handle_space(info, &tmp);
		else if (*tmp == '\'' || *tmp == '"')
			res_quotes = handle_quotes(info, &tmp);
		else if (*tmp == '>' || *tmp == '<')
			handle_redirections(info, &tmp);
		else if (*tmp == '|')
			fill_in_lex(info, TOKEN_PIPE, "|");
		tmp++;
	}
	if (res_quotes)
		return (free_token_lst(&info->token_lst), free(str), 1);
	return (0);
}
