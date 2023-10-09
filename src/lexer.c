/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 14:29:13 by dbredykh          #+#    #+#             */
/*   Updated: 2023/10/09 12:44:01 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_in_lex(t_info *info, int token, char *content)
{
	t_list	*current;
	char	*value;

	value = ft_strdup(content);
	current = ft_lstnew(&token, value);
	if (!info->token_lst)
		ft_lstadd_front(&info->token_lst, current);
	else
		ft_lstadd_back(&info->token_lst, current);
	free(value);
}

void	ft_lexer(t_info *info, char *str)
{
	(void) info;
	(void) str;
	while (*str)
	{
		if (ft_isspace(*str))
		{
			fill_in_lex(info, TOKEN_SEP, " ");
			str++;
			while (ft_isspace(*str))
				str++;
		}
		if (*str == '"')
			fill_in_lex(info, TOKEN_EXP_FIELD, "\"");
		if (*str == '\'')
			fill_in_lex(info, TOKEN_FIELD, "\'");

		str++;
	}
	return ;
}
