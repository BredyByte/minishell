/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:21:05 by dbredykh          #+#    #+#             */
/*   Updated: 2023/11/01 14:20:40 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	minishell_lounch(t_info *info)
{
	char	*prompt;

	while (!info->exit_f)
	{
		prompt = ft_readline("minishell-1.0$ ");
		if (!prompt)
			continue ;
		tokenizer(info, prompt);
		expansion(info);
		grouping(info);
		info->token_lst = NULL;
		add_history(prompt);
		free(prompt);
	}
	clear_history();
}
