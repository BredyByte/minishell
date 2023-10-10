/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:21:05 by dbredykh          #+#    #+#             */
/*   Updated: 2023/10/10 16:24:54 by dbredykh         ###   ########.fr       */
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
		lexer(info, prompt);
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
			t_list *ptr = info->envp_lst;
			while (ptr != NULL)
			{
				printf ("key: %s , value: %s\n", ptr->key, ptr->value);
				ptr = ptr->next;
			}
		}
		t_list *ptr = info->token_lst;
		while (ptr != NULL)
		{
			printf ("token: %d , value: %s\n", get_int_key(ptr), ptr->value);
			ptr = ptr->next;
		}
		printf("resp: %d\n", sintax_error_check(info));
		info->token_lst = NULL;
		/* printf("%s\n", prompt); */
		free(prompt);
	}
	clear_history();
}
