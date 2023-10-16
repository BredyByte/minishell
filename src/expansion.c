/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:45:59 by dbredykh          #+#    #+#             */
/*   Updated: 2023/10/16 11:12:20 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_envp_key(char *str)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = str;
	while (ptr[i] != ' ' && ptr[i] && ptr[i] != '$')
			i++;
	return (ft_strndup(ptr, i));
}

static char	*get_envp_value(t_info *info, char *str)
{
	char	*key;
	t_list	*ptr;

	key = get_envp_key(str);
	ptr = info->envp_lst;
	while (ptr)
	{
		if (ptr->key && !ft_strncmp(ptr->key, key, SIZE_MAX))
			break ;
		ptr = ptr->next;
	}
	free(key);
	return (ft_strndup(ptr->value, ft_strlen(ptr->value)));
}

static char	*handle_dollar_expansion(char **ptmp, t_info *info)
{
	char	*res;
	char	*key;
	char	*tmp;

	res = NULL;
	key = NULL;
	tmp = *ptmp;
	tmp++;
	if (*tmp == '?')
	{
		res = ft_itoa(info->status);
		tmp++;
	}
	else if (ft_isalpha(*tmp) || *tmp == '_')
	{
		key = get_envp_key(tmp);
		res = get_envp_value(info, key);
		tmp += ft_strlen(key);
		free(key);
	}
	*ptmp = tmp;
	return (res);
}

static int	pre_opening_get_new_len(char *str, t_info *info)
{
	char	*tmp;
	int		len;
	char	*res;

	res = NULL;
	tmp = str;
	len = 0;
	while (*tmp)
	{
		if (*tmp == '$' && *(tmp + 1) != ' '
			&& *(tmp + 1) != '$' && *(tmp + 1) != '\0')
		{
			res = handle_dollar_expansion(&tmp, info);
			len += ft_strlen(res);
			free(res);
		}
		else
		{
			len++;
			tmp++;
		}
	}
	return (len);
}

static void	append_to_buffer(char *buf, const char *append, int *current_len)
{
	int	len;

	len = ft_strlen(append);
	ft_memcpy(buf + (*current_len), append, len);
	(*current_len) += len;
	free((void *)append);
}

static char	*process_string_value(t_token *token,
			t_info *info, char *tmp, int *current_len)
{
	char	*new_str;
	char	*res;

	new_str = (char *)malloc(token->len + 1);
	if (!new_str)
		return (NULL);
	new_str[token->len] = '\0';
	while (*tmp)
	{
		if (*tmp == '$' && *(tmp + 1) != ' '
			&& *(tmp + 1) != '$' && *(tmp + 1) != '\0')
		{
			res = handle_dollar_expansion(&tmp, info);
			if (res)
				append_to_buffer(new_str, res, current_len);
		}
		else
		{
			new_str[*current_len] = *tmp;
			(*current_len)++;
			tmp++;
		}
	}
	return (new_str);
}

static char *change_dollar_value(t_token *token, t_info *info)
{
	char	*new_str;
	char	*tmp;
	int		current_len;

	current_len = 0;
	tmp = token->value;
	new_str = process_string_value(token, info, tmp, &current_len);
	free(token->value);
	return (new_str);
}

void opening_dollar(t_token *token, t_info *info)
{
	token->len = pre_opening_get_new_len(token->value, info);
	token->value = change_dollar_value(token, info);
}

void	expansion(t_info *info)
{
	t_token	*tmp;

	tmp = info->token_lst;
	while (tmp != NULL)
	{
		if (tmp->key == TOKEN_WORD || tmp->key == TOKEN_EXP_FIELD)
			opening_dollar(tmp, info);
		tmp = tmp->next;
	}
}
