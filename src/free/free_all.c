/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:52:53 by dbredykh          #+#    #+#             */
/*   Updated: 2023/11/15 12:37:10 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_lst(t_cmd **cmd)
{
	t_cmd	*ptr;
	t_cmd	*tmp;

	if (*cmd == NULL)
		return ;
	ptr = *cmd;
	tmp = NULL;
	while (ptr)
	{
		tmp = ptr->next;
		free(ptr->command);
		if (ptr->fd_in > 2)
			close(ptr->fd_in);
		if (ptr->fd_out > 2)
			close(ptr->fd_out);
		free(ptr);
		ptr = tmp;
	}
	*cmd = NULL;
}

void	free_token_lst(t_token **token_lst)
{
	t_token	*ptr;
	t_token	*tmp;

	if (*token_lst == NULL)
		return ;
	ptr = *token_lst;
	tmp = NULL;
	while (ptr)
	{
		tmp = ptr->next;
		free(ptr->value);
		free(ptr);
		ptr = tmp;
	}
	*token_lst = NULL;
}

static void	free_envp_lst(t_list **envp_lst)
{
	t_list	*ptr;
	t_list	*tmp;

	ptr = *envp_lst;
	tmp = NULL;
	while (ptr)
	{
		tmp = ptr->next;
		free(ptr->key);
		free(ptr->value);
		free(ptr);
		ptr = tmp;
	}
	*envp_lst = NULL;
}

void	free_all(t_info *info)
{
	int	i;

	i = 0;
	while (info->reserved_words[i])
		free(info->reserved_words[i++]);
	i = 0;
	while (info->envp[i])
		free(info->envp[i++]);
	free(info->envp);
	free_envp_lst(&info->envp_lst);
	if (info->token_lst)
		free_token_lst(&info->token_lst);
	if (info->cmd_lst)
		free_cmd_lst(&info->cmd_lst);
	free(info);
}
