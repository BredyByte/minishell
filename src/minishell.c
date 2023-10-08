/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:21:05 by dbredykh          #+#    #+#             */
/*   Updated: 2023/10/08 16:21:43 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	minishell_lounch(t_info *info)
{
	char	*prompt;

	while (!info->exit_f)
	{
		prompt = ft_readline();
		if (!prompt)
		{
			info->exit_f = 1;
			continue ;
		}
		if (!ft_strncmp(prompt, "exit", SIZE_MAX))
			info->exit_f = 1;
		if (!ft_strncmp(prompt, "env", SIZE_MAX))
		{
			int i = 0;
			while (info->envp[i])
			{
				printf ("%s\n", info->envp[i]);
				i++;
			}
		}
		if (!ft_strncmp(prompt, "env_list", SIZE_MAX))
		{
			t_list *ptr = info->envp_list;
			while (ptr != NULL)
			{
				printf ("key: %s , value: %s\n", ptr->key, ptr->value);
				ptr = ptr->next;
			}
		}
		printf("%s\n", prompt);
		free(prompt);
	}
	clear_history();
}
