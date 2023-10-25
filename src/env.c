/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:01:24 by regea-go          #+#    #+#             */
/*   Updated: 2023/10/25 11:53:55 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//It is just a printf of a char * matrix 
//Should we leave error check with that message?
//Should we just print global var? It seems so
int ft_env(t_info *info)
{
    char    *value;
    int     idx;

    value = NULL;
    idx = 0;
    if (info->envp == NULL)
    {
        ft_putendl_fd("Ruben: Env variable list is empty", 2);
        return (EXIT_ERROR);
    }
    while (info->envp[idx])
    {
        value = ft_store_value(info->envp[idx]);
        if (value != NULL)
            printf("%s\n", info->envp[idx]);
        idx++;
        free(value);
        value = NULL;
    }
    if (value)
        free(value);
    return (EXIT_SUCCESS);
}

int    env(t_info *info, char **cmd)
{
    if (ft_strncmp(cmd[0], "env", 3) == 0)
        return (ft_env(info));
    else
    {
        ft_putendl_fd("Ruben: from env: this is not a env!", 2);
        return (EXIT_ERROR);
    }
}