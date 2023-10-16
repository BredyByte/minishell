/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:08:44 by regea-go          #+#    #+#             */
/*   Updated: 2023/10/16 11:28:13 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_cd_noarg()
{
    char    *new_dir;
    char    *current_dir;
    char    *old_dir;
    int     status;
    char    cwd[64];
    
    current_dir = ft_get_env_value("PWD");
    new_dir = ft_get_env_value("HOME");
    if (!new_dir)
        return (ft_print_error("Ruben from cd_noarg:"));
    status = chdir(new_dir);
    if (status == -1)
    {
        perror("Ruben: Can't change to home dir\n");
        return (EXIT_ERROR);
    }
    old_dir = ft_strdup(current_dir);
    ft_export(ft_strjoin("OLDPWD=", current_dir));
    current_dir = getcwd(cwd, 64);
    ft_export(ft_strjoin("PWD=",getcwd(cwd, 64)));
    ft_printf("Changed to: %s\n", ft_get_env_value("PWD"));
    return (EXIT_SUCCESS);
}

int ft_cd_lastdir()
{
    char    *new_dir;
    char    *current_dir;
    char    *old_dir;
    int     status;
    char    cwd[64];

    current_dir = getcwd(cwd, 64);
    old_dir = ft_get_env_value("OLDPWD");
    if (!old_dir)
        return (ft_print_error("Ruben from cd_lastdir:"));
    new_dir = ft_strdup(old_dir);
    status = chdir(old_dir);
    if (status == -1)
    {
        perror("Ruben: Can't change to last dir\n");
        return (EXIT_ERROR);
    }
    new_dir = ft_strdup(old_dir);
    old_dir = ft_strdup(current_dir);
    current_dir = ft_strdup(new_dir);
    ft_export(ft_strjoin("PWD=", getcwd(cwd, 64)));
    ft_export(ft_strjoin("OLDPWD=", old_dir));
    ft_printf("Changed to: %s\n", ft_get_env_value("PWD"));
    return (EXIT_SUCCESS);
}

int ft_cd_home()
{
    char    *new_dir;
    char    *current_dir;
    char    *old_dir;
    int     status;
    char    cwd[64];
    
    current_dir = ft_get_env_value("PWD");
    new_dir = ft_get_env_value("HOME");
    if (!new_dir)
        return (ft_print_error("Ruben from cd_home:"));
    status = chdir(new_dir);
    if (status == -1)
    {
        perror("Ruben: Can't change to home dir\n");
        return (EXIT_ERROR);
    }
    old_dir = ft_strdup(current_dir);
    ft_export(ft_strjoin("OLDPWD=", old_dir));
    current_dir = getcwd(cwd, 64);
    ft_export(ft_strjoin("PWD=", current_dir));
    ft_printf("Changed to: %s\n", current_dir);
    return (EXIT_SUCCESS);
}

int ft_cd_home_relat(char *string)
{
    char    *new_dir;
    char    *current_dir;
    char    *old_dir;
    char    *tmp;
    int     status;
    char    cwd[64];
    
    current_dir = ft_get_env_value("PWD");
    old_dir = ft_get_env_value("OLDPWD");
    tmp = ft_strtrim(string, "~");
    if (!ft_get_env_value("HOME"))
        return (ft_print_error("Ruben from cd_home_relat:"));
    new_dir = ft_strjoin(ft_get_env_value("HOME"), tmp);
    status = chdir(new_dir);
    if (status == -1)
    {
        perror("Ruben: Can't change to ~/(path)\n");
        return (EXIT_ERROR);
    }
    old_dir = ft_strdup(current_dir);
    current_dir = ft_strdup(new_dir);
    ft_export(ft_strjoin("OLDPWD=",old_dir));
    ft_export(ft_strjoin("PWD=", current_dir));
    ft_printf("Current: %s\n", getcwd(cwd, 64));
    free(tmp);
    return (EXIT_SUCCESS); 
}

int ft_cd_parent_dir(char *string)
{
    char    *current_dir;
    char    *old_dir;
    int     status;
    char    cwd[64];
    
    current_dir = ft_get_env_value("PWD");
    if (current_dir)
        old_dir = ft_strdup(current_dir); 
    status = chdir(string);
    if (status == -1)
    {
        perror("Ruben: Can't change to ../(path)\n");
        return (EXIT_ERROR);
    }
    current_dir = getcwd(cwd, 64);
    ft_export(ft_strjoin("OLDPWD=", old_dir));
    ft_export(ft_strjoin("PWD=", current_dir));
    ft_printf("Current dir: %s\n", current_dir);
    return (EXIT_SUCCESS);
}

int ft_cd_current_dir(char *string)
{
    char    *current_dir;
    char    *old_dir;
    int     status;
    char    cwd[64];
    current_dir = ft_get_env_value("PWD");
    if (current_dir)
        old_dir = ft_strdup(current_dir); 
    status = chdir(string);
    if (status == -1)
    {
        perror("Ruben: Can't change to ./(path)\n");
        return (EXIT_ERROR);
    }
    current_dir = getcwd(cwd, 64);
    ft_export(ft_strjoin("OLDPWD=", old_dir));
    ft_export(ft_strjoin("PWD=", current_dir));
    ft_printf("Current dir: %s\n", current_dir);
    return (EXIT_SUCCESS);
}

int ft_cd_abs_path(char *string)
{
    char    *current_dir;
    char    *old_dir;
    int     status;
    char    cwd[64];
    
    current_dir = ft_get_env_value("PWD");
    status = chdir(string);
    if (status == -1)
    {
        perror("Ruben: Can't change to /(path)\n");
        return (EXIT_ERROR);
    }
    if (current_dir)
        old_dir = ft_strdup(current_dir);
    current_dir = getcwd(cwd, 64);
    ft_export(ft_strjoin("OLDPWD=",old_dir));
    ft_export(ft_strjoin("PWD=", current_dir));
    ft_printf("Current: %s\n", ft_get_env_value("PWD"));
    return (EXIT_SUCCESS);
}

int ft_cd_from_current(char *string)
{
    char    *current_dir;
    char    *old_dir;
    char    cwd[64];
    int     status;
    
    current_dir = ft_get_env_value("PWD");
    status = chdir(string);
    if (status == -1)
    {
        perror("Ruben: Can't change to (path)\n");
        return (EXIT_ERROR);
    }
    if (current_dir)
        old_dir = ft_strdup(current_dir);
    current_dir = getcwd(cwd, 64);
    ft_export(ft_strjoin("OLDPWD=",old_dir));
    ft_export(ft_strjoin("PWD=", current_dir));
    ft_printf("Current: %s\n", current_dir);
    return (EXIT_SUCCESS);
}
//TODO
//
// WE SHOULD RETURN STATUS VALUE IF CHDIR FAILS, INSTEAD OF CONTINUING THE FUNCTION

//If chdir is not good, we shouldnt update the paths, and we should stay in the same
//directory as before

int    ft_cd(char *string)
{
    if (string == NULL)
        return (ft_cd_noarg());
    else if (ft_strncmp(string, "-", 1) == 0)
        return (ft_cd_lastdir());   
    else if (ft_strncmp(string, "~", 1) == 0)
    {
        if (ft_strlen(string) == 1)
            return (ft_cd_home());
        else if (ft_strlen(string) > 1)
            return (ft_cd_home_relat(string));
    }
    else if (ft_strncmp(string, "..", 2) == 0)
        return (ft_cd_parent_dir(string));
    else if (ft_strncmp(string, ".", 1) == 0)
        return (ft_cd_current_dir(string));
    else if (ft_strncmp(string, "/", 1) == 0)
        return (ft_cd_abs_path(string));
    else
        return (ft_cd_from_current(string));
    //If it gets to here, maybe there is a possibility we dont contemplate
    ft_putendl_fd("Ruben cd: what is this path!? I dont understand it :D", 2);
    return (EXIT_ERROR);
}

//It is gonna return int value, 1 bad 0 good
int    cd(t_list *node)
{
    if (ft_strncmp(node->key, "cd", 2) == 0)
        return (ft_cd(node->value));
    else
    {
        ft_putendl_fd("Ruben: from ft_cd: this is not a cd", 2);
        return (EXIT_ERROR);
    }
}