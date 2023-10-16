/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:23:14 by regea-go          #+#    #+#             */
/*   Updated: 2023/10/13 12:30:14 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_delete_variable(char *tuple)
{
    char    **new_envp;
    int     idx;
    int     idx2;

    new_envp = malloc((ft_matrix_size(my_struct.envp) - 1) * sizeof(char *));
    idx = 0;
    idx2 = 0;
    while (my_struct.envp[idx2])
    {
        if (ft_strncmp(my_struct.envp[idx2], tuple, ft_strlen(my_struct.envp[idx2])) != 0)
        {
            new_envp[idx] = ft_substr(my_struct.envp[idx2], 0, ft_strlen(my_struct.envp[idx2]));
            idx++;
        }
        idx2++;
    }
    new_envp[idx] = NULL;
    my_struct.envp = ft_copy_matrix(new_envp);
    //ft_free_matrix(new_envp);
    return ;
}

void    ft_unset(char *tuple)
{
    if (ft_env_exists(tuple, my_struct.envp) == TRUE)
    {
        ft_printf("From unset: Ah yes it is there\n");
        ft_delete_variable(tuple);
    }
    else
    {
        ft_printf("Env variable doesnt exists\n");
        return ;
    }
    return ;
}

int    unset(t_list *node)
{
    int ret_val;

    ret_val = 0;
    if (ft_strncmp(node->key, "unset", 5) == 0)
    {
        ft_unset(node->value);
        return (ret_val);
    }
    else
    {
        ft_putendl_fd("Ruben: from ft_unset: this is not an unset!", 2);
        ret_val = 1;
        return (ret_val);
    }
}