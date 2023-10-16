/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:32:26 by regea-go          #+#    #+#             */
/*   Updated: 2023/10/16 11:59:57 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
//It prints empty lines;
//We have to print IN ORDER
void    ft_print_export()
{
    int idx;

    idx = 0;
    if (my_struct.envp == NULL)
    {
        ft_putendl_fd("Error: Env variable list is empty", 2);
        return ;
    }
    while (my_struct.envp[idx])
    {
        if (ft_empty_line(my_struct.envp[idx]) == TRUE)
            idx++;
        else
        {
            ft_printf("declare -x %s\n", my_struct.envp[idx]);
            idx++;
        }
    }
}

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
char    **ft_modify_variable(char *tuple, char **envp)
{
    int idx;

    idx = 0;
    while (envp[idx])
    {
        if (ft_contains(tuple, envp[idx]) == TRUE)
        {
            free(envp[idx]);
            envp[idx] = ft_substr(tuple, 0, ft_strlen(tuple));
            return (envp);
        }
        idx++;
    }
    return (envp);    
}

void    ft_add_to_matrix(char *tuple)
{   
    char    **new_envp;
    int     idx;

    new_envp = malloc((ft_matrix_size(my_struct.envp) + 1) * sizeof(char *));
    idx = 0;
    while (my_struct.envp[idx])
    {
        new_envp[idx] = ft_substr(my_struct.envp[idx], 0, ft_strlen(my_struct.envp[idx]));
        idx++;
    }
    new_envp[idx] = ft_substr(tuple, 0, ft_strlen(tuple));
    new_envp[++idx] = NULL;
    //ft_free_matrix(my_struct.envp);
    my_struct.envp = ft_copy_matrix(new_envp); // Somehow I cannot free new_envp, it gives "pointer freed was not allocated error"
}

void    ft_export(char *tuple)
{
    if (!tuple)
    {
        ft_print_export();
        return ;
    }
    if (ft_double_assign(tuple) == TRUE)
        return ;
    if (ft_env_exists(tuple, my_struct.envp) == TRUE)
        my_struct.envp = ft_copy_matrix(ft_modify_variable(tuple, my_struct.envp));
    else
        ft_add_to_matrix(tuple);
    return ;
}

int    export(t_list *node)
{
    int ret_val;

    ret_val = 0;
    if (ft_strncmp(node->key, "export", 6) == 0)
    {
        ft_export(node->value);
        return (ret_val);
    }
    else
    {
        ft_putendl_fd("Ruben: from ft_export: this is not an export!", 2);
        ret_val = 1;
        return (ret_val);
    }
}