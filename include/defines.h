/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regea-go <regea-go@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 14:40:23 by dbredykh          #+#    #+#             */
/*   Updated: 2023/11/08 18:09:59 by regea-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define TOKEN_SEP 1 // all == ft_isspace // ex: $echo    a    b; result: a b;
# define TOKEN_WORD 2 // all != specific sign
# define TOKEN_FIELD 3 // simple quotes
# define TOKEN_EXP_FIELD 4 // double quotes
# define TOKEN_REDIR_OUT 5 // >
# define TOKEN_REDIR_IN 6 // <
# define TOKEN_REDIR_APPEND 7 // >>
# define TOKEN_REDIR_INSOURCE 8 // heredoc <<
# define TOKEN_PIPE 9 // |

# define TRUE 1
# define FALSE 0

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define EXIT_EXIT 3
# define EXIT_SUCCESS 0
# define EXIT_ERROR 1
# define BAD_ARGS 2
# define COMMAND_NOT_FOUND 127
# define CTRL_C 130

# define NO_FD -2
# define NO_STAT -100

# define PATH_SIZE 4097

# define FORK_ERROR "Unable to fork"
# define REDIR_ERROR "Unable to redirect"
# define EXEC_ERROR "Unable to execute"

/*Colors*/
# define RESET "\033[0;m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"

#endif
