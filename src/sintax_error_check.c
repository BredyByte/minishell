/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sintax_error_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:33:32 by dbredykh          #+#    #+#             */
/*   Updated: 2023/10/12 12:20:39 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static int	ft_pipe_end_check(t_list *token_lst)
{
	t_list	*tmp;

	tmp = token_lst;
	while (tmp != NULL)
	{
		if (get_int_key(tmp) == TOKEN_PIPE)
		{
			tmp = tmp->next;
			while (tmp != NULL && get_int_key(tmp) == TOKEN_SEP)
				tmp = tmp->next;
			if (tmp == NULL)
				return (0);
		}
		else
			tmp = tmp->next;
	}
	return (1);
}

static int	ft_pipe_start_check(t_list *token_lst)
{
	t_list	*tmp;

	tmp = token_lst;
	while (tmp != NULL && get_int_key(tmp) == TOKEN_SEP)
		tmp = tmp->next;
	if (get_int_key(tmp) == TOKEN_PIPE)
		return (0);
	return (1);
}

static int	ft_pipe_check(t_list *token_lst)
{
	t_list	*tmp;

	tmp = token_lst;
	if (!ft_pipe_start_check(token_lst)
		|| !ft_pipe_end_check(token_lst))
		return (0);
	while (tmp != NULL)
	{
		if (get_int_key(tmp) == TOKEN_PIPE
			|| get_int_key(tmp) == TOKEN_IF_OR
			|| get_int_key(tmp) == TOKEN_IF_AND)
		{
			tmp = tmp->next;
			while (tmp != NULL && get_int_key(tmp) == TOKEN_SEP)
				tmp = tmp->next;
			if (tmp == NULL || get_int_key(tmp) == TOKEN_PIPE
				|| get_int_key(tmp) == TOKEN_IF_OR
				|| get_int_key(tmp) == TOKEN_IF_AND)
				return (0);
		}
		else
			tmp = tmp->next;
	}
	return (1);
}

static int	ft_qot_paren_check(t_list *token_lst)
{
	int		double_q_count;
	int		single_q_count;
	int		parentesis_count;
	t_list	*tmp;

	tmp = token_lst;
	double_q_count = 0;
	single_q_count = 0;
	parentesis_count = 0;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->value, "\"", SIZE_MAX) == 0)
			double_q_count++;
		else if (ft_strncmp(tmp->value, "\'", SIZE_MAX) == 0)
			single_q_count++;
		else if (ft_strncmp(tmp->value, "(", SIZE_MAX) == 0
			|| ft_strncmp(tmp->value, ")", SIZE_MAX) == 0)
			parentesis_count++;
		tmp = tmp->next;
	}
	return (!(double_q_count % 2
			|| single_q_count % 2 || parentesis_count % 2));
}

int	sintax_error_check(t_info *info)
{
	return ((ft_qot_paren_check(info->token_lst)
			&& ft_pipe_check(info->token_lst)));
}
 */
