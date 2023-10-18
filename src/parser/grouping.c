/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grouping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:02:21 by dbredykh          #+#    #+#             */
/*   Updated: 2023/10/18 19:28:53 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static t_group	*ft_newgroup(t_cmd *cmd, int group_type)
{
	t_group	*new_group;

	new_group = malloc(sizeof(t_group));
	if (!new_group)
		return (NULL);
	new_group->cmd = cmd;
	new_group->grout_type = group_type;
	new_group->next = NULL;
	return (new_group);
}

static void	add_to_end(t_info *info, t_group *new_group)
{
	t_group	*last_group;

	last_group = info->group_lst;
	while (last_group->next)
		last_group = last_group->next;
	last_group->next = new_group;
	new_group->next = NULL;
}

void	group_init(t_info *info, t_token *token)
{
	t_token	*ptr;
	t_token	*tmp;
	t_group	*group;

	ptr = token;
	tmp = info->token_lst;
	group = ft_newgroup(cmd_lst, group_type);
	if (!info->envp_lst)
		group->next = info->group_lst;
		info->group_lst = group;
	else
		add_to_end(info, group);
} */

/* int	sintaxis_error_handler(t_info *info)
{
	t_token	*ptr;

	ptr = info->token_lst;
	while (ptr)
	{
		if (ptr->key == TOKEN_PIPE && ptr->next->key != TOKEN_WORD)
		{
			ft_printf("minishell: syntax error near unexpected token `|'\n");
			return (1);
		}
		ptr = ptr->next;
	}
} */

static t_cmd	*new_cmd(int fd_in)
{
	t_cmd	*new_node;

	new_node = malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->command = ft_calloc(1, sizeof(char *));
	new_node->fd_in = fd_in;
	new_node->fd_out = 1;
	new_node->fd_here_doc = 0;
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
	new_node->next = NULL;
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

static void	add_cmd(t_token *ptr, t_cmd *new_node)
{
	if (ptr->key == TOKEN_WORD)
		new_node->command = add_to_array(new_node->command, ptr->value);
	else if (ptr->key == TOKEN_SEP && ptr->next->key == TOKEN_WORD)
		new_node->command = add_to_array(new_node->command, " ");
}

static int	is_word(t_token *token)
{
	return (token != NULL
		&& (token->key == TOKEN_WORD
			|| (token->key == TOKEN_SEP
				&& token->next->key
				&& token->next->key == TOKEN_WORD)));
}

void redir(t_cmd *new_node, int *fd_in, t_token *token)
{
	int	fd[2];

	pipe(fd);
	if (*fd_in)
	{
		new_node->fd_in = *fd_in;
		*fd_in = 0;
	}
	else if (token->key == TOKEN_PIPE)
	{
		new_node->fd_out = fd[1];
		*fd_in = fd[0];
	}
	/* else if (token->key == TOKEN_REDIR_IN)
		new_node->fd_in = open(token->next->value, O_RDONLY);
	else if (token->key == TOKEN_REDIR_OUT)
	{
		new_node->fd_out = open(token->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		new_node->append_f = 0;
	}
	else if (token->key == TOKEN_REDIR_APPEND)
	{
		new_node->fd_out = open(token->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		new_node->append_f = 1;
	}
	else if (token->key == TOKEN_REDIR_INSOURCE)
	{
		new_node->here_doc = ft_strdup(token->next->value);
		new_node->fd_here_doc = fd[1];
		new_node->fd_out = fd[1];
	} */
}

void	grouping(t_info *info)
{
	t_cmd	*new_node;
	t_token	*token;
	int		fd_in;

	fd_in = 0;
	token = info->token_lst;
	while (token)
	{
		new_node = new_cmd(fd_in);
		add_back_cmd(&info->cmd_ptr, new_node);
		while (is_word(token))
		{
			add_cmd(token, new_node);
			if  (!token->next)
				redir(new_node, &fd_in, token);
			token = token->next;
		}
		if (token)
		{
			redir(new_node, &fd_in, token);
			token = token->next;
		}
	}
	t_cmd *ptr = info->cmd_ptr;
	while (ptr)
	{
		printf ("%s\n", *ptr->command);
		printf ("fd_in: %d\n", ptr->fd_in);
		printf ("fd_out: %d\n", ptr->fd_out);
		ptr = ptr->next;
	}
}
