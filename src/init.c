/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:31:50 by dbredykh          #+#    #+#             */
/*   Updated: 2023/11/04 20:13:05 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	info->exit_f = 0;
	info->status = 0;
}

void	minishell_lounch(t_info *info)
{
	char	*prompt;

	while (!info->exit_f)
	{
		prompt = ft_readline("minishell-1.0$ ");
		if (!prompt)
			continue ;
		tokenizer(info, prompt);
		expansion(info);
		grouping(info);
		ft_pipex(info);
		cmd_free(&info->cmd_lst);
		info->token_lst = NULL;
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
