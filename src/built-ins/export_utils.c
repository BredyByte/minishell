/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:52:16 by regea-go          #+#    #+#             */
/*   Updated: 2023/11/09 11:01:21 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function tells us if an line from env is empty, 
 * 			so its not printed 
 * @param string - line to be tested 
 * @return int - TRUE if empty, FALSE if not 
 */
int	ft_empty_line(char *string)
{
	int	idx;

	idx = 0;
	if (!string)
		return (TRUE);
	while (string[idx])
		idx++;
	if (idx == 0)
		return (TRUE);
	else
		return (FALSE);
}

/**
 * @brief It tells us if a variable as been double assigned (VAR=SMTH=SMTH)
 * so we dont save it
 *
 * @param str
 * @return int
 */
int	ft_double_assign(char *str)
{
	int	idx;
	int	cntr;

	idx = 0;
	cntr = 0;
	while (str[idx] != '\0')
	{
		if (str[idx] == '=')
			cntr++;
		idx++;
	}
	if (cntr > 1)
		return (TRUE);
	return (FALSE);
}

char	**ft_init_matrix_nil(int size)
{
	char	**matrix;
	int		i;

	matrix = malloc((size + 1) * sizeof(char *));
	if (!matrix)
		return (NULL);
	i = 0;
	while (i <= size)
	{
		matrix[i] = NULL;
		i++;
	}
	return (matrix);
}

int	ft_max_len(char *string1, char *string2)
{
	int	size1;
	int	size2;

	size1 = ft_strlen(string1);
	size2 = ft_strlen(string2);
	if (size1 > size2)
		return (size1);
	else
		return (size2);
}

int	ft_not_in_matrix(char *string, char **envp)
{
	int	idx;

	idx = 0;
	while (envp[idx])
	{
		if (ft_strncmp(envp[idx], string, ft_max_len(envp[idx], string)) == 0)
			return (FALSE);
		idx++;
	}
	return (TRUE);
}
