/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:00:55 by regea-go          #+#    #+#             */
/*   Updated: 2023/10/16 11:46:43 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **ft_split_echo(char *str)
{
    char **echo;

    echo = ft_split(str, ' ');
    return (echo);
}

static int  ft_is_nl(char **str)
{
    if (ft_strncmp(str[0], "-n", 2) == 0)
            return (TRUE);
    return (FALSE);
}

//It gets the args already
void    ft_echo(char **str)
{
    int     idx;
    int     is_nl;
    char    *trim;

    is_nl = ft_is_nl(str);
    idx = 0;
    while (ft_strncmp(str[idx], "-n", 2) == 0)
        idx++;
    while (str[idx])
    {
        trim = ft_strtrim(str[idx], "\"");
        ft_putstr_fd(trim, STDOUT);
        free(trim);
        idx++;
        if (str[idx] != NULL)
            ft_putchar_fd(' ', STDOUT);
    }
    if (ft_is_nl(str) == FALSE)
        write(STDOUT, "\n", 1);
}

int    echo(t_list *node)
{
    char    **cmd;

    if (ft_strncmp(node->key, "echo", 4) == 0)
    {
        cmd = ft_split_echo(node->value);
        ft_echo(cmd);
        ft_free_matrix(cmd);
        return (EXIT_SUCCESS);
    }
    else
    {
        ft_putendl_fd("Ruben: from ft_echo: this is not a echo!", 2);
        return (EXIT_ERROR);
    }
}