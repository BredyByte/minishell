/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:07:05 by dbredykh          #+#    #+#             */
/*   Updated: 2023/11/08 15:32:10 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_lst_change_out(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (!tmp->next)
		{
			if (tmp->fd_out > 2)
			{
				close(tmp->fd_out);
				tmp->fd_out = 1;
			}
		}
		tmp = tmp->next;
	}
}

int	is_redir_out_last(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (token)
	{
		if ((token->key == TOKEN_REDIR_OUT || token->key == TOKEN_REDIR_APPEND)
			&& (token->next && !token->next->next))
			return (1);
		token = token->next;
	}
	return (0);
}

char	**add_to_array(char **arr, char *new_str)
{
	size_t	i;
	size_t	j;
	char	**new_arr;

	i = 0;
	j = 0;
	while (arr && arr[i])
		i++;
	new_arr = ft_calloc(i + 2, sizeof(char *));
	if (!new_arr)
		return (NULL);
	while (j < i)
	{
		new_arr[j] = arr[j];
		j++;
	}
	new_arr[i] = new_str;
	new_arr[i + 1] = NULL;
	free(arr);
	return (new_arr);
}

int	check_sintax_unexpected_token(t_token *token)
{
	t_token	*ptr;

	ptr = token;
	if (ptr && ptr->key == TOKEN_PIPE)
		return (258);
	while (ptr)
	{
		if ((ptr->key == TOKEN_PIPE
				|| ptr->key == TOKEN_REDIR_IN
				|| ptr->key == TOKEN_REDIR_OUT
				|| ptr->key == TOKEN_REDIR_APPEND
				|| ptr->key == TOKEN_REDIR_INSOURCE)
			&& (!ptr->next || (ptr->next && ptr->next->key != TOKEN_WORD)))
			return (258);
		ptr = ptr->next;
	}
	return (0);
}

int	e_index_check(int index)
{
	if (index == 258)
		return (printf
			("minishell: syntax error near unexpected token\n"), index);
	else if (index == 1)
		return (printf
			("minishell: syntax error no such file or directory\n"), index);
	return (0);
}
