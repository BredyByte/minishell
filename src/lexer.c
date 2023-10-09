/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 14:29:13 by dbredykh          #+#    #+#             */
/*   Updated: 2023/10/09 18:58:21 by dbredykh         ###   ########.fr       */
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

static void	handle_redirections(t_info *info, char **str)
{
	if (**str == '>')
	{
		if (ft_strncmp(*str, ">>", 2) == 0)
		{
			fill_in_lex(info, TOKEN_REDIR_APPEND, ">>");
			(*str)++;
		}
		else
			fill_in_lex(info, TOKEN_REDIR_OUT, ">");
	}
	else if (**str == '<')
	{
		if (ft_strncmp(*str, "<<", 2) == 0)
		{
			fill_in_lex(info, TOKEN_REDIR_INSOURCE, "<<");
			(*str)++;
		}
		else
			fill_in_lex(info, TOKEN_REDIR_IN, "<");
	}
}

static void	handle_words(t_info *info, char **str)
{
	char	*start;

	if (!ft_is_special_char(**str))
	{
		start = *str;
		while (*(*str + 1) && !ft_is_special_char(*(*str + 1))
			&& !ft_isspace(*(*str + 1)))
			(*str)++;
		fill_in_lex(info, TOKEN_WORD, ft_strndup(start, *str + 1 - start));
	}
}

static void	handle_logical(t_info *info, char **str)
{
	if (**str == '&' && *(*str + 1) == '&')
	{
		fill_in_lex(info, IF_AND, "&&");
		(*str)++;
	}
	else if (**str == '|' && *(*str + 1) == '|')
	{
		fill_in_lex(info, IF_OR, "||");
		(*str)++;
	}
	else if (**str == '(')
		fill_in_lex(info, PARN_L, "(");
	else if (**str == ')')
		fill_in_lex(info, PARN_R, ")");
	else if (**str == '|')
		fill_in_lex(info, TOKEN_PIPE, "|");
}

void	ft_lexer(t_info *info, char *str)
{
	while (*str)
	{
		if (!ft_is_special_char(*str))
			handle_words(info, &str);
		else if (ft_isspace(*str))
		{
			fill_in_lex(info, TOKEN_SEP, "s");
			while (ft_isspace(*str))
				str++;
			continue ;
		}
		else if (*str == '\'')
			fill_in_lex(info, TOKEN_FIELD, "\'");
		else if (*str == '"')
			fill_in_lex(info, TOKEN_EXP_FIELD, "\"");
		else if (*str == '>' || *str == '<')
			handle_redirections(info, &str);
		else if (*str == '&' || *str == '|' || *str == '(' || *str == ')')
			handle_logical(info, &str);
		str++;
	}
}
