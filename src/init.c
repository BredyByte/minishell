/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 15:32:59 by dbredykh          #+#    #+#             */
/*   Updated: 2023/10/07 17:12:38 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

void	chec_unclosed_quotes(t_info *info, char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '"')
			count++;
		i++;
	}
	if (count % 2 == 0)
		return ;
	info->exit_f = 1;
}

void	minishell_lounch(t_info *info)
{
	char	*prompt;

	while (!info->exit_f)
	{
		prompt = readline("minishell-1.0$ ");
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
		chec_unclosed_quotes(info, prompt);
		printf("%s\n", prompt);
		add_history(prompt);
		free(prompt);
	}
	clear_history();
}

void	init_envp(t_info *info)
{
	int count = 0;
	char **ptr = environ;
	int i = 0;
	while (*ptr)
	{
		count++;
		ptr++;
	}
	info->envp = malloc((count + 1) * sizeof(char *));
	while (i < count)
	{
		info->envp[i] = strdup(environ[i]);
        if (!info->envp[i])
        {
            perror("Failed to copy environment variable");
            exit(1);
        }
		i++;
	}
}

void	data_init(t_info *info)
{
	info->builtins[0] = &buildin_echo;
	info->builtins[1] = &buildin_cd;
	info->builtins[2] = &buildin_pwd;
	info->builtins[3] = &buildin_export;
	info->builtins[4] = &buildin_unset;
	info->builtins[5] = &buildin_env;
	info->builtins[6] = &buildin_exit;
	info->reserved_words[0] = ft_strdup("echo");
	info->reserved_words[1] = ft_strdup("cd");
	info->reserved_words[2] = ft_strdup("pwd");
	info->reserved_words[3] = ft_strdup("export");
	info->reserved_words[4] = ft_strdup("unset");
	info->reserved_words[5] = ft_strdup("env");
	info->reserved_words[6] = ft_strdup("exit");
	init_envp(info);
	init_envp_lst(info, info->envp);
	info->envp_f = 0;
	info->exit_f = 0;
	info->status = 0;
}

int	main(int arv, char **argv)
{
	t_info	*info;
	(void)argv;
	if (arv == 2)
	{
		printf("Execute without any arguments, please!!!");
		return (1);
	}
	info = malloc(sizeof(t_info));
	data_init(info);
	minishell_lounch(info);
	return (0);
}
