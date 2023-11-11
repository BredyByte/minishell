/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:04:58 by dbredykh          #+#    #+#             */
/*   Updated: 2023/11/13 10:39:40 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_pipe(t_cmd *new_node, int *fd_in)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (perror("Error: pipe failure"), 1);
	if (new_node->fd_out > 2)
		close(fd[1]);
	else
		new_node->fd_out = fd[1];
	*fd_in = fd[0];
	return (0);
}

static int	handle_redir_in(t_cmd *new_node, t_token *token,
		t_token **token_ptr)
{
	if (new_node->fd_in > 2)
		close(new_node->fd_in);
	new_node->fd_in = open(token->next->value, O_RDONLY);
	if (new_node->fd_in == -1)
		return (1);
	*token_ptr = token->next;
	if ((*token_ptr)->next && (*token_ptr)->next->key == TOKEN_PIPE
		&& !new_node->command[0] && new_node->fd_in > 2)
	{
		close(new_node->fd_in);
		new_node->fd_in = 0;
	}
	return (0);
}

static int	handle_redir_out(t_cmd *new_node, t_token *token,
		t_token **token_ptr)
{
	if (new_node->fd_out > 2)
		close(new_node->fd_out);
	if (token->key == TOKEN_REDIR_APPEND)
		new_node->fd_out = open(token->next->value,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		new_node->fd_out = open(token->next->value,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (new_node->fd_out == -1)
		return (1);
	*token_ptr = token->next;
	return (0);
}

static int	handle_here_doc(t_cmd *new_node, t_token *token,
		t_token **token_ptr)
{
	if (here_doc(new_node, token->next->value) == -1)
		return (1);
	*token_ptr = token->next;
	return (0);
}

int	redir(t_cmd *new_node, int *fd_in, t_token **token_ptr)
{
	t_token	*token;

	token = *token_ptr;
	if (*fd_in != 0)
	{
		new_node->fd_in = *fd_in;
		*fd_in = 0;
	}
	if (token->key == TOKEN_PIPE)
		return (handle_pipe(new_node, fd_in));
	else if (token->key == TOKEN_REDIR_IN)
		return (handle_redir_in(new_node, token, token_ptr));
	else if (token->key == TOKEN_REDIR_OUT || token->key == TOKEN_REDIR_APPEND)
		return (handle_redir_out(new_node, token, token_ptr));
	else if (token->key == TOKEN_REDIR_INSOURCE)
		return (handle_here_doc(new_node, token, token_ptr));
	return (0);
}
