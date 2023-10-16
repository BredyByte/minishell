/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:18:11 by regea-go          #+#    #+#             */
/*   Updated: 2023/10/16 12:09:42 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//We shall see if we receive a string or a num;
//Either we convert the string or we operate with the int
//If no int with exit call, just put a 0

void    ft_exit(int option)
{
    //See with Davyd who controls the errors here
    //Theoretically, we have to update a variable of the global struct like
    //We use the modulo 256 because bash does it like that
        // minishell->ret = option % 256;
    int value;

    value = option % 256;
    ft_printf("Original value: %i\n", option);
    ft_printf("Yes, its a %i\n", value);
}

int    exit1(t_list *node)
{
    if (ft_strncmp(node->key, "exit", 4) == 0)
    {
        ft_exit(ft_atoi(node->value));
        return (EXIT_SUCCESS);
    }
    else
    {
        ft_putendl_fd("Ruben: from ft_exit: this is not a exit!", 2);
        return (EXIT_ERROR);
    }
}