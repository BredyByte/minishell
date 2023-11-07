/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:37:51 by regea-go          #+#    #+#             */
/*   Updated: 2023/11/07 11:38:59 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_ctrl_c(int signal)
{
	(void)signal;
	if (g_batch_flag == 42)
	{
		write(1, "\033[K\n", 5);
		rl_replace_line("", 0);
		g_batch_flag = 1;
	}
	if (g_batch_flag == 0)
	{
		ioctl(STDIN, TIOCSTI, "\n");
		rl_replace_line("", 1);
		rl_on_new_line();
	}
	else if (g_batch_flag == 1)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
	}
}

void	ft_signals(void)
{
	signal(SIGINT, ft_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
