/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:45:59 by dbredykh          #+#    #+#             */
/*   Updated: 2023/10/13 18:03:28 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_dollar(t_token *token)
{
	char	*str;

	str = token->value;
	while (*str)
	{
		if (*str == '$')
			return (1);
		str++;
	}
	return (0);
}

void	expansion(t_info *info)
{
	t_token	*tmp;

	tmp = info->token_lst;
	int count = 0;
	while (tmp != NULL)
	{
		if ((tmp->key == TOKEN_WORD || tmp->key == TOKEN_EXP_FIELD) && is_dollar(tmp))
			count++;
		tmp = tmp->next;
	}
	printf("count: %d\n", count);
}
