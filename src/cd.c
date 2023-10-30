/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:08:44 by regea-go          #+#    #+#             */
/*   Updated: 2023/10/30 14:43:02 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO
//We have to refactor all this 

static void ft_free_dirs(char *s1, char *s2, char *s3)
{
    if (s1)
        free(s1);
    if (s2)
        free(s2);
    if (s3)
        free(s3);
    s1 = NULL;
    s2 = NULL;
    s3 = NULL;
}

int     ft_cd_home(t_info *info)
{
    char    *new_dir;
    char    *current_dir;
    int     status;
    char    cwd[PATH_SIZE];
    char    *path;
    
    new_dir = ft_get_env_value(info, "HOME");
    if (!new_dir)
        return (ft_print_error("Ruben from cd_home: Variable HOME not set\n"));
    current_dir = ft_get_env_value(info, "PWD");
    status = chdir(new_dir);
    if (status == -1)
    {
        perror("Ruben: Can't change to home dir\n");
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

int ft_cd_lastdir(t_info *info)
{
    char    *new_dir;
    char    *current_dir;
    int     status;
    char    cwd[PATH_SIZE];
    char    *path;
    
    current_dir = ft_strdup(getcwd(cwd, PATH_SIZE));
    new_dir = ft_get_env_value(info, "OLDPWD");
    if (!new_dir)
        return (ft_print_error("Ruben from cd_lastdir:"));
    status = chdir(new_dir);
    if (status == -1)
    {
        free(current_dir);
        free(new_dir);
        perror("Ruben: Can't change to last dir\n");
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

int ft_cd_home_relat(t_info *info, char *string)    //<---Refactor this one
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
        return (ft_print_error("Ruben from cd_home_relat:"));
    current_dir = ft_get_env_value(info, "PWD");
    tmp = ft_strtrim(string, "~");
    new_dir = ft_strjoin(home_dir, tmp);
    status = chdir(new_dir);
    if (status == -1)
    {
        ft_free_dirs(current_dir, home_dir, new_dir);
        free(tmp);
        perror("Ruben: Can't change to ~/(path)\n");
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

int ft_cd_other(t_info *info, char *string)
{
    char    *current_dir;
    char    *new_dir;
    char    cwd[PATH_SIZE];
    int     status;
    char    *path;
    
    current_dir = ft_get_env_value(info, "PWD");
    status = chdir(string);
    if (status == -1)
    {
        free(current_dir);
        perror("Ruben: Can't change to (path)\n");
        return (EXIT_ERROR);
    }
    new_dir = ft_strdup(getcwd(cwd, PATH_SIZE));
    
    path = ft_strjoin("OLDPWD=",current_dir);
    ft_export(info, path);
    free(path);
    
    path = ft_strjoin("PWD=", new_dir);
    ft_export(info, path);
    free(path);
    
    printf("Current: %s\n", new_dir);
    ft_free_dirs(new_dir, current_dir, NULL);
    return (EXIT_SUCCESS);
}

int    ft_cd(t_info *info, char **cmd)
{
    if (cmd[1] == NULL)
        return (ft_cd_home(info));
    else if (ft_strncmp(cmd[1], "-", 1) == 0)
        return (ft_cd_lastdir(info));   
    else if (ft_strncmp(cmd[1], "~", 1) == 0)
    {
        if (ft_strlen(cmd[1]) == 1)
            return (ft_cd_home(info));
        else if (ft_strlen(cmd[1]) > 1)
            return (ft_cd_home_relat(info, cmd[1]));
    }
    else if (ft_strncmp(cmd[1], "..", 2) == 0)
        return (ft_cd_other(info, cmd[1]));
    else if (ft_strncmp(cmd[1], ".", 1) == 0)
        return (ft_cd_other(info, cmd[1]));
    else if (ft_strncmp(cmd[1], "/", 1) == 0)
        return (ft_cd_other(info, cmd[1]));
    else
        return (ft_cd_other(info, cmd[1]));
    return (EXIT_ERROR);
}

//It is gonna return int value, 1 bad 0 good
int    cd(t_info *info, char **cmd)
{
    if (ft_strncmp(cmd[0], "cd", 2) == 0 && cmd[0][2] == '\0')
        return (ft_cd(info, cmd));
    else
    {
        ft_putendl_fd("Ruben: from ft_cd: this is not a cd", 2);
        return (EXIT_ERROR);
    }
}