/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 15:32:59 by dbredykh          #+#    #+#             */
/*   Updated: 2023/10/23 16:01:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_envp_lst(t_info *info, char **envp)
{
	t_list	*current;
	char	*delimiter;
	char	*key;
	char	*value;

	while (*envp)
	{
		delimiter = ft_strchr(*envp, '=');
		if (!delimiter)
		{
			envp++;
			continue ;
		}
		key = ft_strndup(*envp, delimiter - *envp);
		value = ft_strdup(delimiter + 1);
		current = ft_lstnew(key, value);
		if (!info->envp_lst)
			ft_lstadd_front(&info->envp_lst, current);
		else
			ft_lstadd_back(&info->envp_lst, current);
		free(key);
		free(value);
		envp++;
	}
}

static void	init_envp(t_info *info, char **environ)
{
	int		count;
	char	**ptr;
	int		i;

	i = 0;
	ptr = environ;
	count = 0;
	while (*ptr++)
		count++;
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

static void	data_init(t_info *info, char **envp)
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
	init_envp(info, envp);
	init_envp_lst(info, info->envp);
	info->token_lst = NULL;
	info->cmd_lst = NULL;
	info->exit_f = 0;
	info->status = 0;
}

int	main(int arv, char **argv, char **envp)
{
	t_info	*info;

	(void)argv;
	if (arv == 2)
	{
		printf("Execute without any arguments, please!!!\n");
		return (1);
	}
	info = malloc(sizeof(t_info));
	data_init(info, envp);
	minishell_lounch(info);
	free(info);
	return (0);
}
