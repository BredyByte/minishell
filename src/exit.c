/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:18:11 by regea-go          #+#    #+#             */
/*   Updated: 2023/10/31 15:33:58 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//We shall see if we receive a string or a num;
//Either we convert the string or we operate with the int
//If no int with exit call, just put a 0

static int  ft_isnum(char *str)
{
    size_t  size;

    size = 0;
    if (!str)
        return (FALSE);
    while (str[size] != '\0')
    {
        if (ft_isdigit(str[size]) == FALSE)
            return (FALSE);
        size++;
    }
    return (TRUE);
}

int ft_exit(t_info *info, int option)
{
    //See with Davyd who controls the errors here
    //Theoretically, we have to update a variable of the global struct like
    //We use the modulo 256 because bash does it like that
    // minishell->ret = option % 256;
    int value;

    value = option % 256;
    info->status = value;
    info->exit_f = 1;
    return (EXIT_SUCCESS);
}

int    exit1(t_info *info, char **cmd)
{
    ft_putendl_fd("exit", STDOUT);
    if (cmd[2] != NULL)
    {
        ft_print_error("Ruben: from exit: too many arguments\n");
        return (BAD_ARGS);
    }

    if (ft_strncmp(cmd[0], "exit", 4) == 0 && cmd[0][4] == '\0')
    {
        if (!cmd[1])
            return (ft_exit(info, 0));
        else if (ft_isnum(cmd[1]) == FALSE)
        {
            ft_exit(info, 255);
            ft_print_error("Ruben: from exit: Not a number ");
            return (BAD_ARGS);
        }
        else
            return (ft_exit(info, ft_atoi(cmd[1])));
    }
    else
    {
        ft_print_error("Ruben: from ft_exit: this is not a exit!");
        return (BAD_ARGS);
    }
}
