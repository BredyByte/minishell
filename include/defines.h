/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 14:40:23 by dbredykh          #+#    #+#             */
/*   Updated: 2023/10/17 13:09:02 by dbredykh         ###   ########.fr       */
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

// bonus part

# define TOKEN_IF_AND 10 // &&
# define TOKEN_IF_OR 11 // ||
# define TOKEN_PARN_L 12 // (
# define TOKEN_PARN_R 13 // )

// group types

# define NULL_GROUP 1 //
# define OR_GROUP 2 // ||
# define AND_GROUP 3 // &&

#endif
