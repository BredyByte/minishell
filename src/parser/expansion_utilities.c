/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utilities.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:17:25 by dbredykh          #+#    #+#             */
/*   Updated: 2023/10/24 15:13:30 by regea-go         ###   ########.fr       */
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
	while (ptr[i] != ' ' && ptr[i] && ptr[i] != '$')
			i++;
	return (ft_strndup(ptr, i));
}

char	*get_envp_value(t_list *list, char *str)					//<--- Ruben to Davyd: When I do cd and stuff, it changes env vars in the char **, but you expand variables in list; so if I change dirs, then I print pwd, it is not the good one 
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
