/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:08:44 by regea-go          #+#    #+#             */
/*   Updated: 2023/10/27 13:33:11 by regea-go         ###   ########.fr       */
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

int     ft_cd_noarg(t_info *info)
{
    char    *new_dir;
    char    *current_dir;
    char    *old_dir;
    int     status;
    char    cwd[PATH_SIZE];
    
    new_dir = ft_get_env_value(info, "HOME");
    if (!new_dir)
        return (ft_print_error("Ruben from cd_noarg: variable HOME doesnt exist"));
    current_dir = ft_get_env_value(info, "PWD");
    status = chdir(new_dir);
    if (status == -1)
    {
        perror("Ruben: Can't change to home dir\n");
        return (EXIT_ERROR);
    }
    old_dir = ft_strdup(current_dir);
    free(current_dir);
    char    *old_path = ft_strjoin("OLDPWD=", old_dir);
    ft_export(info, old_path);
    free(old_path);
    current_dir = ft_strdup(getcwd(cwd, PATH_SIZE));
    char    *new_path = ft_strjoin("PWD=", current_dir);
    ft_export(info, new_path);
    free(new_path);
    printf("Changed to: %s\n", current_dir);
    ft_free_dirs(old_dir, current_dir, new_dir);
    return (EXIT_SUCCESS);
}

int ft_cd_lastdir(t_info *info)
{
    char    *new_dir;
    char    *current_dir;
    char    *old_dir;
    int     status;
    char    cwd[PATH_SIZE];

    current_dir = ft_strdup(getcwd(cwd, PATH_SIZE));
    old_dir = ft_get_env_value(info, "OLDPWD");
    if (!old_dir)
        return (ft_print_error("Ruben from cd_lastdir:"));
    status = chdir(old_dir);
    if (status == -1)
    {
        perror("Ruben: Can't change to last dir\n");
        return (EXIT_ERROR);
    }
    new_dir = ft_strdup(old_dir);
    free(old_dir);
    old_dir = ft_strdup(current_dir);
    free(current_dir);
    current_dir = ft_strdup(getcwd(cwd, PATH_SIZE));
    char *new_path = ft_strjoin("PWD=", current_dir);
    ft_export(info, new_path);
    free(new_path);
    char *old_path = ft_strjoin("OLDPWD=", old_dir);
    ft_export(info, old_path);
    free(old_path);
    printf("Changed to: %s\n", current_dir);
    ft_free_dirs(old_dir, current_dir, new_dir);
    return (EXIT_SUCCESS);
}

int ft_cd_home(t_info *info)
{
    char    *new_dir;
    char    *current_dir;
    char    *old_dir;
    int     status;
    char    cwd[PATH_SIZE];
    
    current_dir = ft_get_env_value(info, "PWD");
    new_dir = ft_get_env_value(info, "HOME");
    if (!new_dir)
        return (ft_print_error("Ruben from cd_home:"));
    status = chdir(new_dir);
    if (status == -1)
    {
        perror("Ruben: Can't change to home dir\n");
        return (EXIT_ERROR);
    }
    old_dir = ft_strdup(current_dir);
    free(current_dir);
    char *old_path = ft_strjoin("OLDPWD=", old_dir);
    ft_export(info, old_path);
    free(old_path);
    current_dir = ft_strdup(getcwd(cwd, PATH_SIZE));
    char *new_path = ft_strjoin("PWD=", current_dir);
    ft_export(info, new_path);
    free(new_path);
    printf("Changed to: %s\n", current_dir);
    ft_free_dirs(old_dir, current_dir, new_dir);
    return (EXIT_SUCCESS);
}

int ft_cd_home_relat(t_info *info, char *string)
{
    char    *new_dir;
    char    *current_dir;
    char    *old_dir;
    char    *tmp;
    int     status;
    char    cwd[PATH_SIZE];
    char    *home_dir = ft_get_env_value(info, "HOME");
    if (!home_dir)
        return (ft_print_error("Ruben from cd_home_relat:"));
    current_dir = ft_get_env_value(info, "PWD");
    tmp = ft_strtrim(string, "~");
    new_dir = ft_strjoin(home_dir, tmp);
    status = chdir(new_dir);
    if (status == -1)
    {
        perror("Ruben: Can't change to ~/(path)\n");
        return (EXIT_ERROR);
    }
    old_dir = ft_strdup(current_dir);
    free(current_dir);
    current_dir = ft_strdup(new_dir);
    
    char *old_path = ft_strjoin("OLDPWD=",old_dir);
    ft_export(info, old_path);
    free(old_path);
    
    char *new_path = ft_strjoin("PWD=", current_dir);
    ft_export(info, new_path);
    free(new_path);
    
    printf("Current: %s\n", getcwd(cwd, PATH_SIZE));
    free(tmp);
    ft_free_dirs(old_dir, current_dir, new_dir);
    free(home_dir);
    return (EXIT_SUCCESS); 
}

int ft_cd_parent_dir(t_info *info, char *string)
{
    char    *current_dir;
    char    *old_dir;
    int     status;
    char    cwd[PATH_SIZE];
    
    current_dir = ft_get_env_value(info, "PWD");
    if (current_dir)
        old_dir = ft_strdup(current_dir); 
    status = chdir(string);
    if (status == -1)
    {
        perror("Ruben: Can't change to ../(path)\n");
        return (EXIT_ERROR);
    }
    free(current_dir);
    current_dir = ft_strdup(getcwd(cwd, PATH_SIZE));
    char *old_path = ft_strjoin("OLDPWD=", old_dir);
    ft_export(info, old_path);
    free(old_path);
    char *new_path = ft_strjoin("PWD=", current_dir);
    ft_export(info, new_path);
    free(new_path);
    printf("Current dir: %s\n", current_dir);
    ft_free_dirs(old_dir, current_dir, NULL);
    return (EXIT_SUCCESS);
}

int ft_cd_current_dir(t_info *info, char *string)
{
    char    *current_dir;
    char    *old_dir;
    int     status;
    char    cwd[PATH_SIZE];
    
    current_dir = ft_get_env_value(info, "PWD");
    if (current_dir)
        old_dir = ft_strdup(current_dir); 
    status = chdir(string);
    if (status == -1)
    {
        perror("Ruben: Can't change to ./(path)\n");
        return (EXIT_ERROR);
    }
    free(current_dir);
    current_dir = ft_strdup(getcwd(cwd, PATH_SIZE));
    char *old_path = ft_strjoin("OLDPWD=", old_dir);
    ft_export(info, old_path);
    free(old_path);
    char *new_path = ft_strjoin("PWD=", current_dir);
    ft_export(info, new_path);
    free(new_path);
    printf("Current dir: %s\n", current_dir);
    ft_free_dirs(old_dir, current_dir, NULL);
    return (EXIT_SUCCESS);
}

int ft_cd_abs_path(t_info *info, char *string)
{
    char    *current_dir;
    char    *old_dir;
    int     status;
    char    cwd[PATH_SIZE];
    
    old_dir = NULL;
    current_dir = ft_get_env_value(info, "PWD");
    status = chdir(string);
    if (status == -1)
    {
        perror("Ruben: Can't change to /(path)\n");
        return (EXIT_ERROR);
    }
    old_dir = ft_strdup(current_dir);
    free(current_dir);
    current_dir = ft_strdup(getcwd(cwd, PATH_SIZE));
    char *old_path = ft_strjoin("OLDPWD=",old_dir);
    ft_export(info, old_path);
    free(old_path);
    char *new_path = ft_strjoin("PWD=", current_dir);
    ft_export(info, new_path);
    free(new_path);
    printf("Current: %s\n", current_dir);
    ft_free_dirs(old_dir, current_dir, NULL);
    return (EXIT_SUCCESS);
}

int ft_cd_from_current(t_info *info, char *string)
{
    char    *current_dir;
    char    *old_dir;
    char    cwd[PATH_SIZE];
    int     status;
    
    old_dir = NULL;
    current_dir = ft_get_env_value(info, "PWD");
    status = chdir(string);
    if (status == -1)
    {
        perror("Ruben: Can't change to (path)\n");
        return (EXIT_ERROR);
    }
    if (current_dir)
        old_dir = ft_strdup(current_dir);
    free(current_dir);
    current_dir = ft_strdup(getcwd(cwd, PATH_SIZE));
    char *old_path = ft_strjoin("OLDPWD=",old_dir);
    ft_export(info, old_path);
    free(old_path);
    char *new_path = ft_strjoin("PWD=", current_dir);
    ft_export(info, new_path);
    free(new_path);
    printf("Current: %s\n", current_dir);
    ft_free_dirs(old_dir, current_dir, NULL);
    return (EXIT_SUCCESS);
}

int    ft_cd(t_info *info, char **cmd)
{
    if (cmd[1] == NULL)
        return (ft_cd_noarg(info));
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
        return (ft_cd_parent_dir(info, cmd[1]));
    else if (ft_strncmp(cmd[1], ".", 1) == 0)
        return (ft_cd_current_dir(info, cmd[1]));
    else if (ft_strncmp(cmd[1], "/", 1) == 0)
        return (ft_cd_abs_path(info, cmd[1]));
    else
        return (ft_cd_from_current(info, cmd[1]));
    //If it gets to here, maybe there is a possibility we dont contemplate
    ft_putendl_fd("Ruben cd: what is this path!? I dont understand it :D", 2);
    return (EXIT_ERROR);
}

//It is gonna return int value, 1 bad 0 good
int    cd(t_info *info, char **cmd)
{
    if (ft_strncmp(cmd[0], "cd", 2) == 0)
        return (ft_cd(info, cmd));
    else
    {
        ft_putendl_fd("Ruben: from ft_cd: this is not a cd", 2);
        return (EXIT_ERROR);
    }
}