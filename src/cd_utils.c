/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:06:36 by regea-go          #+#    #+#             */
/*   Updated: 2023/11/01 23:40:57 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_update_pwds(t_info *info, char *current_dir, char *new_dir)
{
	char	*path;
	path = ft_strjoin("OLDPWD=",current_dir);
    ft_export(info, path);
    free(path);
    path = ft_strjoin("PWD=", new_dir);
    ft_export(info, path);
    free(path);
	return ;
}

int	ft_cd_home(t_info *info)
{
	char	*new_dir;
	char	*current_dir;
	int		status;
	char	cwd[PATH_SIZE];

	new_dir = ft_get_env_value(info, "HOME");
	if (!new_dir)
	{
		ft_print_error("cd: HOME not set\n");
		return (EXIT_ERROR);
	}
	current_dir = ft_get_env_value(info, "PWD");
	status = chdir(new_dir);
	if (status == -1)
	{
		free(current_dir);
		free(new_dir);
		return (EXIT_ERROR);
	}
	free(new_dir);
	new_dir = ft_strdup(getcwd(cwd, PATH_SIZE));
	ft_update_pwds(info, current_dir, new_dir);
	ft_free_dirs(current_dir, new_dir, NULL);
	return (EXIT_SUCCESS);
}

int	ft_cd_lastdir(t_info *info)
{
	char	*new_dir;
	char	*current_dir;
	int		status;
	char	cwd[PATH_SIZE];

	current_dir = ft_strdup(getcwd(cwd, PATH_SIZE));
	new_dir = ft_get_env_value(info, "OLDPWD");
	if (!new_dir)
		return (ft_print_error("cd_lastdir:"));					//<----If OLDPWD doesnt exist, we have to go to ~(and print it)
	status = chdir(new_dir);
	if (status == -1)
	{
		free(current_dir);
		free(new_dir);
		return (EXIT_ERROR);
	}
	free(new_dir);
	new_dir = ft_strdup(getcwd(cwd, PATH_SIZE));
	ft_update_pwds(info, current_dir, new_dir);
	printf("%s\n", new_dir);
	ft_free_dirs(current_dir, new_dir, NULL);
	return (EXIT_SUCCESS);
}



int	ft_cd_home_relat(t_info *info, char *string)    //<---Refactor this one
{
	char    *new_dir;
	char    *current_dir;
	char    *tmp;
	int     status;
	char    cwd[PATH_SIZE];
	char    *home_dir;
    
    home_dir = ft_get_env_value(info, "HOME");
    if (!home_dir)
        return (ft_print_error("home_relat:"));
    current_dir = ft_get_env_value(info, "PWD");
    tmp = ft_strtrim(string, "~");
    new_dir = ft_strjoin(home_dir, tmp);
    status = chdir(new_dir);
    if (status == -1)
    {
        ft_free_dirs(current_dir, home_dir, new_dir);
        free(tmp);
        return (EXIT_ERROR);
    }
	free(new_dir);
	new_dir = ft_strdup(getcwd(cwd, PATH_SIZE));
	ft_update_pwds(info, current_dir, new_dir);
    ft_free_dirs(current_dir, new_dir, NULL);
    ft_free_dirs(tmp, home_dir, NULL);
    return (EXIT_SUCCESS); 
}

int	ft_cd_other(t_info *info, char *string)
{
	char	*current_dir;
	char	*new_dir;
	char	cwd[PATH_SIZE];
	int		status;

	current_dir = ft_get_env_value(info, "PWD");
	status = chdir(string);
	if (status == -1)
	{
		free(current_dir);
		return (EXIT_ERROR);
	}
	new_dir = ft_strdup(getcwd(cwd, PATH_SIZE));
	ft_update_pwds(info, current_dir, new_dir);
	ft_free_dirs(new_dir, current_dir, NULL);
	return (EXIT_SUCCESS);
}
