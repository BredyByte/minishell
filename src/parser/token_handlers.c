/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_handlers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:24:51 by dbredykh          #+#    #+#             */
/*   Updated: 2023/11/07 19:06:52 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_quotes(t_info *info, char **str)
{
	char	quote_char;
	char	*start;
	char	*tmp;

	quote_char = **str;
	start = ++(*str);
	tmp = NULL;
	while (**str && **str != quote_char)
		(*str)++;
	if (**str == quote_char)
	{
		tmp = ft_strndup(start, *str - start);
		if (quote_char == '"')
			fill_in_lex(info, TOKEN_EXP_FIELD, tmp);
		else if (quote_char == '\'')
			fill_in_lex(info, TOKEN_FIELD, tmp);
		free(tmp);
	}
	else
		return (printf("Davyd: Error Quotes.\n"), 1);
	return (0);
}

void	handle_redirections(t_info *info, char **str)
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

void	handle_words(t_info *info, char **str)
{
	char	*start;
	char	*tmp;

	tmp = NULL;
	if (!ft_is_special_char(**str)
		|| (*(*str + 1) && **str == '&' && *(*str + 1) != '&'))
	{
		start = *str;
		while (*(*str + 1) && (!ft_is_special_char(*(*str + 1)) || (**str == '&'
					&& *(*str + 1) != '&')) && !ft_isspace(*(*str + 1)))
			(*str)++;
		tmp = ft_strndup(start, *str + 1 - start);
		fill_in_lex(info, TOKEN_WORD, tmp);
		free(tmp);
	}
}

void	handle_space(t_info *info, char **str)
{
	char	*start;
	char	*tmp;

	tmp = NULL;
	start = *str;
	while (ft_isspace(*(*str + 1)))
		(*str)++;
	tmp = ft_strndup(start, *str + 1 - start);
	fill_in_lex(info, TOKEN_SEP, tmp);
	free(tmp);
}
