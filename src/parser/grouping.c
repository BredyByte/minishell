/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grouping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:02:21 by dbredykh          #+#    #+#             */
/*   Updated: 2023/10/27 13:41:36 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*new_cmd(void)
{
	t_cmd	*new_node;

	new_node = malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->command = ft_calloc(1, sizeof(char *));
	new_node->fd_in = 0;
	new_node->fd_out = 1;
	new_node->here_doc = NULL;
	new_node->append_f = 0;
	new_node->next = NULL;
	return (new_node);
}

static void	add_back_cmd(t_cmd **cmd_ptr, t_cmd *new_node)
{
	t_cmd	*ptr;

	ptr = *cmd_ptr;
	if (ptr == NULL)
	{
		new_node->next = *cmd_ptr;
		*cmd_ptr = new_node;
	}
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new_node;
	}
}

char	**add_to_array(char **arr, char *new_str)
{
	size_t	i = 0;
	size_t	j = 0;
	char	**new_arr;

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
		new_node->fd_in = open(token->next->value, O_RDONLY);
		if (new_node->fd_in == -1)
			return (1);
		*token_ptr = token->next;
	}
	else if (token->key == TOKEN_REDIR_OUT || token->key == TOKEN_REDIR_APPEND)
	{
		new_node->fd_out = open(token->next->value, O_WRONLY
				| O_CREAT | O_TRUNC, 0644);
		if (token->key == TOKEN_REDIR_APPEND)
			new_node->append_f = 1;
		else
			new_node->append_f = 0;
		if (new_node->fd_out == -1)
			return (1);
		*token_ptr = token->next;
	}
	else if (token->key == TOKEN_REDIR_INSOURCE)
	{
		new_node->here_doc = ft_strdup(token->next->value);
		new_node->fd_in = 0;
	}
	return (0);
}

static void cmd_free(t_cmd **cmd)
{
	t_cmd *ptr;
	t_cmd *tmp;
	int i;

	ptr = *cmd;
	i = 0;
	tmp = NULL;
	while (ptr)
	{
		tmp = ptr->next;
		while (ptr->command[i])
			free(ptr->command[i++]);
		if (ptr->fd_in != 0 && ptr->fd_in != 1)
			close(ptr->fd_in);
		if (ptr->fd_out != 0 && ptr->fd_out != 1)
			close(ptr->fd_out);
		free(ptr->command);
		free(ptr->here_doc);
		free(ptr);
		ptr = tmp;
	}
	*cmd = NULL;
}

static	int	check_sintax_unexpected_token(t_token *token)
{
	t_token	*ptr;

	ptr = token;
	if (ptr->key == TOKEN_PIPE)
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

static int	e_index_check(int index)
{
	if (index == 258)
	{
		printf("minishell: syntax error near unexpected token\n");
		return (index);
	}
	else if (index == 1)
	{
		printf("minishell: syntax error no such file or directory\n");
		return (index);
	}
	return (0);
}

void	grouping(t_info *info)
{
	t_cmd	*new;
	t_token	*token;
	int		fd_in;
	int		e_index;

	fd_in = 0;
	token = info->token_lst;
	e_index = check_sintax_unexpected_token(token);
	new = NULL;
	while (token)
	{
		if (e_index)
			break ;
		if (!new || (new && new->command[0]))
		{
			new = new_cmd();
			add_back_cmd(&info->cmd_lst, new);
		}
		while (token && token->key == TOKEN_WORD)
		{
			new->command = add_to_array(new->command, token->value);
			if (!token->next
				&& redir(new, &fd_in, &token))
			{
				e_index = 1;
				break ;
			}
			token = token->next;
		}
		if (token && redir(new, &fd_in, &token))
		{
			e_index = 1;
			break ;
		}
		else if (token)
			token = token->next;
	}
	info->status = e_index_check(e_index);
	/*
		ToDo:
		1 - Error handling:
			* - syntax error near unexpected token `some token' - code  258; e_index = 258; - ✅
			* - unexistfile: No such file or directory - 1 e_index = 1; - ✅
			* - first pipe error check - 258; e_index = 258; - ✅
		2 - <hello cat - does`t save cat in command; - ✅
		3 - close fd in case of >a>b>c - 
		4 - change status in case of error - ✅
		5 - minishell lounch error !prompt - sigment error - ✅
		6 - free cmd; ✅
		7 - <hello cat - after free cmd_lst && closing fds, gives a hello fd(past) + 4... - ✅ 
	 */
	t_cmd *ptr = info->cmd_lst;
	t_cmd *list = ptr;
	while (ptr)
	{
		printf(BLUE"\nDavid:\n\n"RESET);
		char **line = ptr->command;
		printf(BLUE"commands: "RESET);
		while (*line)
		{
			int i = 0;
			char *str = *line;
			while (str[i])
				i++;
			printf (BLUE"   %s"RESET, *line);
			//printf (BLUE"len: %d: "RESET, i);
			line++;
		}
		printf ("\n");
		printf (BLUE"fd_in: %d\nfd_out: %d\n"RESET, ptr->fd_in, ptr->fd_out);
		ptr = ptr->next;
	}
	ft_pipex(info, list);
	cmd_free(&info->cmd_lst);
}
