/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:31:50 by dbredykh          #+#    #+#             */
/*   Updated: 2023/11/07 19:17:23 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_batch_flag;

static void	data_init(t_info *info, char **envp)
{
	(void) envp;
	info->reserved_words[0] = ft_strdup("echo");
	info->reserved_words[1] = ft_strdup("cd");
	info->reserved_words[2] = ft_strdup("pwd");
	info->reserved_words[3] = ft_strdup("export");
	info->reserved_words[4] = ft_strdup("unset");
	info->reserved_words[5] = ft_strdup("env");
	info->reserved_words[6] = ft_strdup("exit");
	info->reserved_words[7] = NULL;
	info->envp_lst = NULL;
	info->envp = NULL;
	info->token_lst = NULL;
	info->cmd_lst = NULL;
	init_envp(info, envp);
	init_envp_lst(info, info->envp);
	info->status = 0;
	info->exit = 0;
}

void	minishell_lounch(t_info *info)
{
	char	*prompt;

	prompt = NULL;
	while (info->exit != 1)
	{
		g_batch_flag = 0;
		ft_signals();
		prompt = readline("minishell-1.0$ ");
		if (!prompt)
		{
			free(prompt);
			printf("exit\n");
			info->exit = 1;
			continue ;
		}
		if (tokenizer(info, prompt))
			continue ;
		expansion(info);
		grouping(info);
		ft_pipex(info);
		free_token_lst(&info->token_lst);
		free_cmd_lst(&info->cmd_lst);
		if (*prompt != '\0')
			add_history(prompt);
		free(prompt);
	}
	clear_history();
}

void test(void)
{
	system("leaks -q minishell");
}

int	main(int arv, char **argv, char **envp)
{
	t_info	*info;
	int		status;

	(void)argv;
	if (arv == 2)
		return (printf("Execute without any arguments, please!!!\n"), 1);
	atexit(test);
	info = malloc(sizeof(t_info));
	data_init(info, envp);
	minishell_lounch(info);
	status = info->status;
	free_all(info);
	return (status);
}
