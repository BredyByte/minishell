/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:32:26 by regea-go          #+#    #+#             */
/*   Updated: 2023/11/01 13:08:07 by regea-go         ###   ########.fr       */
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

char    **ft_init_matrix_nil(int size)
{
    char    **matrix;
    int     i;

    matrix = malloc ((size + 1) * sizeof(char *));
    if (!matrix)
        return (NULL);
    i = 0;
    while (i <= size)
    {
        matrix[i] = NULL;
        i++;
    }
    return (matrix);
}

char    *ft_high_string()
{
    char    *string;
    
    string = malloc (2 * sizeof(char));
    if (!string)
        return (NULL);
    string[0] = 127;
    string[1] = '\0';
    return (string);
}

int     ft_max_len(char *string1, char *string2)
{
    int size1;
    int size2;

    size1 = ft_strlen(string1);
    size2 = ft_strlen(string2);
    if (size1 > size2)
        return (size1);
    else 
        return (size2);
}

int     ft_not_in_matrix(char *string, char **envp)
{
    int idx;

    idx = 0;
    while (envp[idx])
    {
        if (ft_strncmp(envp[idx], string, ft_max_len(envp[idx], string)) == 0)
            return (FALSE);
        idx++;
    }
    return (TRUE);
}

char    **ft_order_env(char **envp)
{
    char    **new_envp;
    char    *tmp;
    int     size;
    int     idx;
    int     idx2;
    
    size = ft_matrix_size(envp);
    new_envp = ft_init_matrix_nil(size);
    if (!envp)
        return (NULL);
    idx = 0;
    idx2 = 0;
    
    while (idx < size)
    {
        tmp = ft_high_string();
        idx2 = 0;
        while (envp[idx2])
        {
            if (ft_strncmp(tmp, envp[idx2], ft_max_len(tmp, envp[idx2])) > 0 
                && ft_not_in_matrix(envp[idx2], new_envp) == TRUE)
            {
                free (tmp);
                tmp = ft_strdup(envp[idx2]);
            }
            idx2++;
        }
        new_envp[idx] = ft_strdup(tmp);
        free(tmp);
        idx++;
    }
    new_envp[idx] = NULL;
    return (new_envp);
}

/**
 * @brief Prints env vars in "declare -x:" format if no params are passed 
 * 
 */
void    ft_print_export(t_info *info)
{
    int     idx;
    char    **ordered_list;
    idx = 0;
    if (info->envp == NULL)
        return ;
    ordered_list = ft_order_env(info->envp);
    while (ordered_list[idx] != NULL)
    {
        if (ft_empty_line(ordered_list[idx]) == TRUE)
            idx++;
        else
        {
            printf("declare -x %s\n", ordered_list[idx]);
            idx++;
        }
    }
    ft_free_matrix(ordered_list);
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
        return (ft_print_error("Bad command"));
}