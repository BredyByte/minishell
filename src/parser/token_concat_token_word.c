/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_concat_token_word.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:35:14 by dbredykh          #+#    #+#             */
/*   Updated: 2023/11/15 15:27:40 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	concat_token_word(t_info *info)
{
	t_token	*tmp;
	char	*new_str;
	t_token	*next;

	tmp = info->token_lst;
	new_str = NULL;
	next = NULL;
	while (tmp && tmp->next)
	{
		if (tmp->key == TOKEN_WORD
			&& (tmp->next && tmp->next->key == TOKEN_WORD))
		{
			new_str = ft_strjoin(tmp->value, tmp->next->value);
			free(tmp->value);
			tmp->value = ft_strndup(new_str, ft_strlen(new_str));
			tmp->len = ft_strlen(tmp->value);
			free(new_str);
			next = tmp->next;
			free(next->value);
			tmp->next = next->next;
			free(next);
		}
		else
			tmp = tmp->next;
	}
}
