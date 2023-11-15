/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expan_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:17:25 by dbredykh          #+#    #+#             */
/*   Updated: 2023/11/15 13:35:10 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_envp_key(char *str)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = str;
	if (ft_isdigit(*ptr))
		return (ft_strndup(ptr, 1));
	while (ptr[i] != ' ' && ptr[i] && ptr[i] != '$' && ptr[i] != '\'')
		i++;
	return (ft_strndup(ptr, i));
}

char	*get_envp_value(t_list *list, char *str)
{
	char	*key;
	t_list	*ptr;

	key = get_envp_key(str);
	ptr = list;
	while (ptr)
	{
		if (ptr->key && !ft_strncmp(ptr->key, key, SIZE_MAX))
			break ;
		ptr = ptr->next;
	}
	if (!ptr)
		return (NULL);
	free(key);
	return (ft_strndup(ptr->value, ft_strlen(ptr->value)));
}

void	append_to_buffer(char *buf, const char *append, int *current_len)
{
	int	len;

	len = ft_strlen(append);
	ft_memcpy(buf + (*current_len), append, len);
	(*current_len) += len;
	free((void *)append);
}

int	is_valid_dollar_followup(char c)
{
	return (ft_isalpha(c) || c == '?' || ft_isdigit(c) || c == '_');
}
