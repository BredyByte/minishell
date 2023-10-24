/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:32:26 by regea-go          #+#    #+#             */
/*   Updated: 2023/10/24 14:44:01 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function tells us if an line from env is empty, so its not printed 
 * @param string - line to be tested 
 * @return int - TRUE if empty, FALSE if not 
 */
int ft_empty_line(char *string)
{
    int idx;
    
    idx =  0;
    if (!string)
        return (TRUE);
    while (string[idx])
        idx++;
    if (idx == 0)
        return (TRUE);
    else 
        return (FALSE);
}

/**
 * @brief Prints env vars in "declare -x:" format if no params are passed 
 * 
 */
//**************We have to print IN ORDER***************
void    ft_print_export()
{
    int idx;

    idx = 0;
    if (info->envp == NULL)
    {
        ft_putendl_fd("Ruben from print_export: Error: Env variable list is empty", 2);
        return ;
    }
    while (info->envp[idx] != NULL)
    {
        if (ft_empty_line(info->envp[idx]) == TRUE)
            idx++;
        else
        {
            printf("declare -x %s\n", info->envp[idx]);
            idx++;
        }

    }
}

/**
 * @brief It tells us if a variable as been double assigned (VAR=SMTH=SMTH)
 * so we dont save it
 * 
 * @param str 
 * @return int 
 */
int     ft_double_assign(char *str)
{
    int idx;
    int cntr;

    idx = 0;
    cntr = 0;
    while (str[idx] != '\0')
    {
        if (str[idx] == '=')
            cntr++;
        idx++;
    }
    if (cntr > 1)
        return (TRUE);
    return (FALSE);
}

//Mbe change it so it just modifies global env
void    ft_modify_variable(char *tuple)
{
    int idx;

    idx = 0;
    while (info->envp[idx])
    {
        if (ft_contains(tuple, info->envp[idx]) == TRUE)
        {
            free(info->envp[idx]);
            info->envp[idx] = ft_substr(tuple, 0, ft_strlen(tuple));
            return ;
        }
        idx++;
    }
    return ;    
}

/**
 * @brief 
 * 
 * @param tuple 
 */
void    ft_add_to_matrix(char *tuple)
{   
    char    **new_envp;
    int     idx;

    new_envp = malloc((ft_matrix_size(info->envp) + 1) * sizeof(char *));
    idx = 0;
    while (info->envp[idx])
    {
        new_envp[idx] = ft_substr(info->envp[idx], 0, ft_strlen(info->envp[idx]));
        idx++;
    }
    new_envp[idx] = ft_substr(tuple, 0, ft_strlen(tuple));
    new_envp[++idx] = NULL;
    info->envp = ft_copy_matrix(new_envp);
}

int ft_export(char *tuple)
{
    if (!tuple)
    {
        ft_print_export();
        return (EXIT_SUCCESS);
    }
    if (ft_double_assign(tuple) == TRUE)
        return (EXIT_SUCCESS);
    if (ft_env_exists(tuple, info->envp) == TRUE)
    {
        ft_modify_variable(tuple);
        info->envp = ft_copy_matrix(info->envp);
    }
    else
    {
        //ft_free_matrix(info->envp);
        ft_add_to_matrix(tuple);
    }
    
    return (EXIT_SUCCESS);
}

int    export(char **cmd)
{
    if (ft_strncmp(cmd[0], "export", 6) == 0)
        if (!cmd[1])
            return (ft_export(NULL));
        else
            return (ft_export(cmd[1]));
    else
        return (ft_print_error("Ruben: from ft_export: this is not an export!"));
}