/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:31:50 by dbredykh          #+#    #+#             */
/*   Updated: 2023/11/22 13:40:37 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	ft_restore(t_cmd **cmd_lst, t_token **token_lst, char *prompt)
{
	free_token_lst(token_lst);
	free_cmd_lst(cmd_lst);
	free(prompt);
}

void	minishell_lounch(t_info *info)
{
	char	*prompt;

	prompt = NULL;
	while (info->exit != 1)
	{
		g_batch_flag = 0;
		ft_signals();
		prompt = readline("\x1b[1;33mminishell-1.0$ \x1b[0m");
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
		if (*prompt != '\0')
			add_history(prompt);
		ft_restore(&info->cmd_lst, &info->token_lst, prompt);
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
	free_all(info);
	exit(status);
}
