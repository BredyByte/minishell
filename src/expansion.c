/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:45:59 by dbredykh          #+#    #+#             */
/*   Updated: 2023/10/15 15:18:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *get_envp_key(t_info *info, char *str)
{
	(void) info;
	int i = 0;
	char *ptr = str;
	while (ptr[i] != ' ' && ptr[i] && ptr[i] != '$')
			i++;
	return (ft_strndup(ptr, i));
}

static char *get_envp_value(t_info *info, char *str)
{
	char *key = get_envp_key(info, str);
	t_list *ptr = info->envp_lst;
	while (ptr)
	{
		if (ptr->key && !ft_strncmp(ptr->key, key, SIZE_MAX))
			break ;
		ptr = ptr->next;	
	}
	free(key);
	return (ft_strndup(ptr->value, ft_strlen(ptr->value)));
}

static char *get_dollar_value(char *str, t_info *info)
{
	char *tmp = str;
	while (*(++tmp))
	{
		if (*tmp == '?')
			return (ft_itoa(info->status));
		if (ft_isalpha(*tmp) || *tmp == '_')
			return (get_envp_value(info, tmp));
	}
	return (NULL);
}

static int pre_opening_get_new_len(char *str, t_info *info)
{
	char *tmp = str;
	char *res = NULL;
	int len = 0;
	while (*tmp)
	{
		if (*tmp == '$' && *(tmp + 1) != ' ' &&  *(tmp + 1) != '$' && *(tmp + 1) != '\0')
		{
			res = get_dollar_value(tmp, info);
			printf ("*res: %s\n", res);
			len += ft_strlen(res);
			free(res);
			printf ("*tmp before: %c\n", *tmp);
			while (*tmp && (ft_isalpha(*tmp) || *tmp == '_' || ft_isdigit(*tmp)))
    			tmp++;
			printf ("*tmp after: %c\n", *tmp);
		}
		else
		{
			len++;
			printf ("*tmp: %c\n", *tmp);
			tmp++;
		}
	}
	return (len);
}

/* static char *append_to_buffer(char *buf, const char *append, int *current_len)
{
    int len = ft_strlen(append);
    memcpy(buf + (*current_len), append, len);
    (*current_len) += len;
    return buf;
}

static char *change_dollar_value(t_token *token, t_info *info)
{
    char *new_str = (char *)malloc(token->len + 1);
    char *tmp = token->value;
    char *res;
    int current_len = 0;

    if (!new_str)
        return NULL;

    new_str[token->len] = '\0'; // Предварительно устанавливаем последний символ в '\0'

    while (*tmp)
    {
        if (*tmp == '$' && *(tmp + 1) != ' ' &&  *(tmp + 1) != '$' && *(tmp + 1) != '\0')
        {
            res = get_dollar_value(tmp, info);
            if (res)
            {
                append_to_buffer(new_str, res, &current_len);
                free(res);
            }
            while (*tmp && *tmp != ' ')
                tmp++;
        }
        else
        {
            new_str[current_len] = *tmp;
            current_len++;
            tmp++;
        }
    }
    free(token->value); // Освобождаем память старого значения
    return (new_str); // Обновляем указатель на новое значение
} */

void opening_dollar(t_token *token, t_info *info)
{
	token->len = pre_opening_get_new_len(token->value, info);
/* 	token->value = change_dollar_value(token, info); */
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
