/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:06:36 by regea-go          #+#    #+#             */
/*   Updated: 2023/11/01 15:06:50 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd_home(t_info *info)
{
	char	*new_dir;
	char	*current_dir;
	int		status;
	char	cwd[PATH_SIZE];
	char	*path;

	new_dir = ft_get_env_value(info, "HOME");
	if (!new_dir)
	{
		ft_print_error("cd_home: Variable HOME not set\n");
		return (EXIT_ERROR);
	}
	current_dir = ft_get_env_value(info, "PWD");
	status = chdir(new_dir);
	if (status == -1)
	{
		perror("Can't change to home dir\n");
		free(current_dir);
		free(new_dir);
		return (EXIT_ERROR);
	}
	path = ft_strjoin("OLDPWD=", current_dir);
	ft_export(info, path);
	free(path);
	free(new_dir);
	new_dir = ft_strdup(getcwd(cwd, PATH_SIZE));
	path = ft_strjoin("PWD=", new_dir);
	ft_export(info, path);
	free(path);
	printf("Current: %s\n", new_dir);
	ft_free_dirs(current_dir, new_dir, NULL);
	return (EXIT_SUCCESS);
}

int	ft_cd_lastdir(t_info *info)
{
	char	*new_dir;
	char	*current_dir;
	int		status;
	char	cwd[PATH_SIZE];
	char	*path;

	current_dir = ft_strdup(getcwd(cwd, PATH_SIZE));
	new_dir = ft_get_env_value(info, "OLDPWD");
	if (!new_dir)
		return (ft_print_error("cd_lastdir:"));
	status = chdir(new_dir);
	if (status == -1)
	{
		free(current_dir);
		free(new_dir);
		perror("Can't change to last dir\n");
		return (EXIT_ERROR);
	}
	free(new_dir);
	new_dir = ft_strdup(getcwd(cwd, PATH_SIZE));
	path = ft_strjoin("PWD=", new_dir);
	ft_export(info, path);
	free(path);
	path = ft_strjoin("OLDPWD=", current_dir);
	ft_export(info, path);
	free(path);
	printf("Current: %s\n", new_dir);
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
	char    *path;
    
    home_dir = ft_get_env_value(info, "HOME");
    if (!home_dir)
        return (ft_print_error("Rcd_home_relat:"));
    current_dir = ft_get_env_value(info, "PWD");
    tmp = ft_strtrim(string, "~");
    new_dir = ft_strjoin(home_dir, tmp);
    status = chdir(new_dir);
    if (status == -1)
    {
        ft_free_dirs(current_dir, home_dir, new_dir);
        free(tmp);
        perror("Can't change to ~/(path)\n");
        return (EXIT_ERROR);
    }    
    path = ft_strjoin("OLDPWD=",current_dir);
    ft_export(info, path);
    free(path);
    
    path = ft_strjoin("PWD=", new_dir);
    ft_export(info, path);
    free(path);
    
    printf("Current: %s\n", getcwd(cwd, PATH_SIZE));
    ft_free_dirs(current_dir, new_dir, NULL);
    free(tmp);
    free(home_dir);
    return (EXIT_SUCCESS); 
}

int	ft_cd_other(t_info *info, char *string)
{
	char	*current_dir;
	char	*new_dir;
	char	cwd[PATH_SIZE];
	int		status;
	char	*path;

	current_dir = ft_get_env_value(info, "PWD");
	status = chdir(string);
	if (status == -1)
	{
		free(current_dir);
		perror("Can't change to (path)\n");
		return (EXIT_ERROR);
	}
	new_dir = ft_strdup(getcwd(cwd, PATH_SIZE));
	path = ft_strjoin("OLDPWD=", current_dir);
	ft_export(info, path);
	free(path);
	path = ft_strjoin("PWD=", new_dir);
	ft_export(info, path);
	free(path);
	printf("Current: %s\n", new_dir);
	ft_free_dirs(new_dir, current_dir, NULL);
	return (EXIT_SUCCESS);
}
