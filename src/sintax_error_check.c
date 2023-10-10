/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sintax_error_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:33:32 by dbredykh          #+#    #+#             */
/*   Updated: 2023/10/10 16:25:08 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static int	ft_parenthesis_check(t_list *token_lst)
{
	(void) token_lst;
	return (1);
} */

static int	ft_qots_check(t_list *token_lst)
{
	int		double_q_count;
	int		single_q_count;
	t_list	*tmp;

	tmp = token_lst;
	double_q_count = 0;
	single_q_count = 0;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->value, "\"", SIZE_MAX) == 0)
			double_q_count++;
		else if (ft_strncmp(tmp->value, "\'", SIZE_MAX) == 0)
			single_q_count++;
		tmp = tmp->next;
	}
	if (double_q_count % 2 != 0 || single_q_count % 2 != 0)
		return (0);
	return (1);
}

int	sintax_error_check(t_info *info)
{
/* 	return ((ft_qots_check(info->token_lst)
			&& ft_parenthesis_check(info->token_lst))); */
	return (ft_qots_check(info->token_lst));
}
