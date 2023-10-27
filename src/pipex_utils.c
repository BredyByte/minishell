/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:55:10 by regea-go          #+#    #+#             */
/*   Updated: 2023/10/26 18:42:40 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_print_error(char *error)
{
	perror(error);
	return (EXIT_ERROR);
}

//We r gonna init a list here, but we will use the one from global var
int	ft_is_builtin(char *str)
{
	char *table[] = {	"cd", 
						"env",
						"pwd",
						"echo",
						"exit",
						"unset",
						"export",
						NULL,
					};
	int	cntr;
	
	cntr = 0;
	while (table[cntr])
	{
		if (ft_strncmp(str, table[cntr], ft_strlen(table[cntr])) == 0)
			return (TRUE);
		cntr++;
	}
	return (FALSE);
}


char	*abs_bin_path(char *cmd, char **envp)	
{
	int		i;
	char	*slash_cmd;
	char	*possible_bin;

	i = 0;
	slash_cmd = NULL;
	possible_bin = NULL;
	if (cmd[0] == '/')
	{
		//do things
		if (access(cmd, F_OK) == 0)
		{
			if (access(cmd, X_OK) < 0)
			{
				perror("Permission denied\n");
				return (NULL);
			}
			else
				return (cmd);
		}
	}
	else
	{
		slash_cmd = ft_strjoin("/", cmd);
		while (envp[i])
		{
			possible_bin = ft_strjoin(envp[i], slash_cmd);
			if (access(possible_bin, F_OK) == 0)
			{
				if (access(possible_bin, X_OK) < 0)
				{
					perror("Permission denied\n");
					//free(possible_bin);
					return (NULL);
				}
				else
					return (possible_bin);
			}
			//free(possible_bin);
			i++;
		}
		//free(slash_cmd);
	}
	return (possible_bin);
}

char	**get_paths(char *envp[])
{
	int		i;
	int		flag;
	char	**path_env_var;
	char	**paths;

	i = 0;
	flag = 0;
	while (envp[i] && flag == 0)
	{
		if (ft_strnstr(envp[i], "PATH", 4))
			flag = 1;
		if (flag == 0)
			i++;
	}
	path_env_var = ft_split(envp[i], '=');
	paths = ft_split(path_env_var[1], ':');
	ft_free_matrix(path_env_var);
	return (paths);
}