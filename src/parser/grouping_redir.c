/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grouping_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:04:58 by dbredykh          #+#    #+#             */
/*   Updated: 2023/11/02 18:05:04 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir(t_cmd *new_node, int *fd_in, t_token **token_ptr)
{
	int		fd[2];
	t_token	*token;

	token = *token_ptr;
	if (*fd_in)
	{
		new_node->fd_in = *fd_in;
		*fd_in = 0;
	}
	if (token->key == TOKEN_PIPE)
	{
		if (pipe(fd) == -1)
			perror("Error: pipe failure");
		new_node->fd_out = fd[1];
		*fd_in = fd[0];
	}
	else if (token->key == TOKEN_REDIR_IN)
	{
		if (new_node->fd_in > 2)
			close(new_node->fd_in);
		new_node->fd_in = open(token->next->value, O_RDONLY);
		if (new_node->fd_in == -1)
			return (1);
		*token_ptr = token->next;
	}
	else if (token->key == TOKEN_REDIR_OUT || token->key == TOKEN_REDIR_APPEND)
	{
		if (new_node->fd_out > 2)
			close(new_node->fd_out);
		if (token->key == TOKEN_REDIR_APPEND)
			new_node->fd_out = open(token->next->value, O_WRONLY
					| O_CREAT | O_APPEND, 0644);
		else
			new_node->fd_out = open(token->next->value, O_WRONLY
					| O_CREAT | O_TRUNC, 0644);
		if (new_node->fd_out == -1)
			return (1);
		*token_ptr = token->next;
	}
	else if (token->key == TOKEN_REDIR_INSOURCE)
	{
		if (here_doc(new_node, token->next->value) == -1)
			return (1);
		*token_ptr = token->next;
	}
	return (0);
}
