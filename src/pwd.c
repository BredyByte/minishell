/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:21:49 by regea-go          #+#    #+#             */
/*   Updated: 2023/10/19 13:52:23 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Looks too easy, but it seems like we dont have to do anything else
// Any other number for that random 64?
int ft_pwd(void)
{
    char    cwd[64];

    if (getcwd(cwd, 64))
    {
        ft_putendl_fd(cwd, STDOUT);
        return (EXIT_SUCCESS);
    }
    else
    {
        perror("Error from pwd:");
        return (EXIT_ERROR);
    }
}

int    pwd(char **cmd)
{
    if (ft_strncmp(cmd[0], "pwd", 3) == 0)
        return (ft_pwd());
    else
    {
        ft_putendl_fd("Ruben: from ft_pwd: this is not a pwd!", 2);
        return (EXIT_ERROR);
    }
}