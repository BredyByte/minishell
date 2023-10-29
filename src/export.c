/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:32:26 by regea-go          #+#    #+#             */
/*   Updated: 2023/10/29 16:02:06 by regea-go         ###   ########.fr       */
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
void    ft_print_export(t_info *info)
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
void    ft_modify_variable(char **envp, char *tuple)
{
    int idx;

    idx = 0;
    while (envp[idx])
    {
        if (ft_contains(tuple, envp[idx]) == TRUE)
        {
            free(envp[idx]);
            envp[idx] = ft_strdup(tuple);
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
char    **ft_add_to_matrix(char **envp, char *tuple)
{   
    char    **new_envp;
    int     idx;

    new_envp = malloc((ft_matrix_size(envp) + 2) * sizeof(char *));
    idx = 0;
    while (envp[idx])
    {
        new_envp[idx] = ft_strdup(envp[idx]);
        idx++;
    }
    new_envp[idx] = ft_strdup(tuple);
    new_envp[++idx] = NULL;
    ft_free_matrix(envp);
    return (new_envp);
}

int ft_export(t_info *info, char *tuple)
{
    if (!tuple)
    {
        ft_print_export(info);
        return (EXIT_SUCCESS);
    }
    if (ft_double_assign(tuple) == TRUE)
        return (EXIT_SUCCESS);
    if (ft_env_exists(tuple, info->envp) == TRUE)
        ft_modify_variable(info->envp, tuple);
    else
        info->envp = ft_add_to_matrix(info->envp, tuple);
    
    return (EXIT_SUCCESS);
}

int    export(t_info *info, char **cmd)
{
    if (ft_strncmp(cmd[0], "export", 6) == 0 && cmd[0][6] == '\0')
        if (!cmd[1])
            return (ft_export(info, NULL));
        else
            return (ft_export(info, cmd[1]));
    else
        return (ft_print_error("Ruben: from ft_export: this is not an export!"));
}