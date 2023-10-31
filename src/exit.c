/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:18:11 by regea-go          #+#    #+#             */
/*   Updated: 2023/10/31 12:46:10 by dbredykh         ###   ########.fr       */
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
    printf("Original value: %i\n", option);
    printf("Value %i saved in status\n", value);
    return (EXIT_SUCCESS);
}

int    exit1(t_info *info, char **cmd)
{
    ft_putendl_fd("exit", STDOUT);
    if (cmd[2] != NULL)
        return (ft_print_error("Ruben: from exit: too many arguments\n"));

    if (ft_strncmp(cmd[0], "exit", 4) == 0 && cmd[0][4] == '\0')
    {
        if (!cmd[1])
            return (ft_exit(info, 0));
        else if (ft_isnum(cmd[1]) == FALSE)
        {
            ft_exit(info, 255);
            return (ft_print_error("Ruben: from exit: Not a number "));
        }
        else
            return (ft_exit(info, ft_atoi(cmd[1])));
    }
    else
        return (ft_print_error("Ruben: from ft_exit: this is not a exit!"));
}
