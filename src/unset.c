/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:23:14 by regea-go          #+#    #+#             */
/*   Updated: 2023/10/25 11:59:15 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_delete_variable(t_info *info, char *tuple)
{
    char    **new_envp;
    int     idx;
    int     idx2;

    new_envp = malloc((ft_matrix_size(info->envp) - 1) * sizeof(char *));
    idx = 0;
    idx2 = 0;
    while (info->envp[idx2])
    {
        if (ft_strncmp(info->envp[idx2], tuple, ft_strlen(info->envp[idx2])) != 0)
        {
            new_envp[idx] = ft_substr(info->envp[idx2], 0, ft_strlen(info->envp[idx2]));
            idx++;
        }
        idx2++;
    }
    new_envp[idx] = NULL;
    info->envp = ft_copy_matrix(new_envp);
    //ft_free_matrix(new_envp);
    return ;
}

int ft_unset(t_info *info, char *tuple)
{
    if (ft_env_exists(tuple, info->envp) == TRUE)
    {
        printf("Ruben: From unset: Ah yes it is there\n");
        ft_delete_variable(info, tuple);
        return (EXIT_SUCCESS);
    }
    else
    {
        printf("Ruben: From unset: Env variable doesnt exists\n");
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

int    unset(t_info *info, char **cmd)
{
    if (ft_strncmp(cmd[0], "unset", 5) == 0)
    {
        if (cmd[1])
            return(ft_unset(info, cmd[1]));
        else 
            return (ft_print_error("No args here"));
    }
    else
        return (ft_print_error("This is not an unset!"));
}