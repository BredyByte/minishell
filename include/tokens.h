/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 14:40:23 by dbredykh          #+#    #+#             */
/*   Updated: 2023/10/09 15:08:25 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# define TOKEN_SEP 1 // all == ft_isspace // ex: $echo    a    b; result: a b;
# define TOKEN_WORD 2 // all != specific sign
# define TOKEN_FIELD 3 // simple quotes
# define TOKEN_EXP_FIELD 4 // double quotes
# define TOKEN_REDIR_OUT 5 // >
# define TOKEN_REDIR_IN 6 // <
# define TOKEN_REDIR_APPEND 7 // >>
# define TOKEN_REDIR_INSOURCE 8 // heredoc <<
# define TOKEN_PIPE 9 // |

// bonus part

# define IF_AND 10 // &&
# define IF_OR 11 // ||
# define PARN_L 12 // (
# define PARN_R 13 // )



#endif
