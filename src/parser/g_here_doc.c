/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grouping_here_doc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:08:37 by dbredykh          #+#    #+#             */
/*   Updated: 2023/11/02 17:08:43 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(t_cmd *new_node, char *here_doc_str)
{
	char	*line;
	int		fd_temp;

	line = NULL;
	fd_temp = open("/var/tmp/.temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	new_node->here_doc = ft_strdup(here_doc_str);
	if (!new_node->here_doc || fd_temp == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (line == NULL
			|| (line != NULL && ft_strncmp(line, new_node->here_doc,
					ft_strlen(new_node->here_doc)) == 0))
			break ;
		write(fd_temp, line, ft_strlen(line));
		write(fd_temp, "\n", 1);
		free(line);
	}
	free(line);
	close(fd_temp);
	fd_temp = open("/var/tmp/.temp.txt", O_RDONLY);
	new_node->fd_in = fd_temp;
	return (0);
}
