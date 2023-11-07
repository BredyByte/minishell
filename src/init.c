/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:31:50 by dbredykh          #+#    #+#             */
/*   Updated: 2023/11/07 12:01:52 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_batch_flag;

static void	data_init(t_info *info, char **envp)
{
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

	ft_signals();
	while (info->exit != 1)
	{
		g_batch_flag = 0;
		ft_signals();
		prompt = readline("minishell-1.0$ ");
		if (!prompt)
		{
			printf("exit\n");
			info->exit = 1;
			break ;
		}
		tokenizer(info, prompt);
		expansion(info);
		grouping(info);
		ft_pipex(info);
		cmd_free(&info->cmd_lst);
		info->token_lst = NULL;
		if (*prompt != '\0')
			add_history(prompt);
		free(prompt);
	}
	clear_history();
}

int	main(int arv, char **argv, char **envp)
{
	t_info	*info;
	int		status;

	(void)argv;
	if (arv == 2)
		return (printf("Execute without any arguments, please!!!\n"), 1);
	info = malloc(sizeof(t_info));
	data_init(info, envp);
	minishell_lounch(info);
	status = info->status;
	free(info);
	return (status);
}
