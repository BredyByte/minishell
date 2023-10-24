/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:00:55 by regea-go          #+#    #+#             */
/*   Updated: 2023/10/23 15:03:07 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  ft_is_nl(char **str)
{
    if (!str[1])
        return (FALSE);
    if (ft_strncmp(str[1], "-n", 2) == 0)
            return (TRUE);
    return (FALSE);
}

int    ft_echo(char **cmd)
{
    int     idx;
    int     is_nl;
    char    *trim;

    is_nl = ft_is_nl(cmd);
    idx = 1;
    if (!cmd[1])
    {
        ft_putstr_fd("\n", STDOUT);
        return (EXIT_SUCCESS);
    }
    while (ft_strncmp(cmd[idx], "-n", 2) == 0)
        idx++;
    while (cmd[idx])
    {
        trim = ft_strtrim(cmd[idx], "\"");
        ft_putstr_fd(trim, STDOUT);
        free(trim);
        idx++;
        if (cmd[idx] != NULL)
            ft_putchar_fd(' ', STDOUT);
    }
    if (ft_is_nl(cmd) == FALSE)
        write(STDOUT, "\n", 1);
    return (EXIT_SUCCESS);
}

int    echo(char **cmd)
{
    if (ft_strncmp(cmd[0], "echo", 4) == 0)
        return (ft_echo(cmd));
    else
    {
        ft_putendl_fd("Ruben: from ft_echo: this is not a echo!", 2);
        return (EXIT_ERROR);
    }
}
