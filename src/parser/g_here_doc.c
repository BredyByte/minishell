/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_here_doc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:08:37 by dbredykh          #+#    #+#             */
/*   Updated: 2023/11/04 11:33:07 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(t_cmd *new_node, char *here_doc_str)
{
	char	*line;
	int		fd[2];

	line = NULL;
	new_node->here_doc = ft_strdup(here_doc_str);
	if (!new_node->here_doc || pipe(fd) < 0)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (line == NULL
			|| (line != NULL && ft_strncmp(line, new_node->here_doc,
					ft_strlen(new_node->here_doc)) == 0))
			break ;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	free(line);
	close(fd[1]);
	new_node->fd_in = fd[0];
	return (0);
}
