/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:01:24 by regea-go          #+#    #+#             */
/*   Updated: 2023/10/14 20:44:58 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//It is just a printf of a char * matrix 
//Should we leave error check with that message?
//Should we just print global var? It seems so
void    ft_env()
{
    int idx;

    idx = 0;
    if (my_struct.envp == NULL)
    {
        ft_putendl_fd("Ruben: Env variable list is empty", 2);
        return ;
    }
    while (my_struct.envp[idx])
    {
        if (ft_store_value(my_struct.envp[idx]) != NULL)
            ft_printf("%s\n", my_struct.envp[idx]);
        idx++;
    }
}

int    env(t_list *node)
{
    if (ft_strncmp(node->key, "env", 3) == 0)
    {
        ft_env();
        return (EXIT_SUCCESS);
    }
    else
    {
        ft_putendl_fd("Ruben: from env: this is not a env!", 2);
        return (EXIT_ERROR);
    }
}