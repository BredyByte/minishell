/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 14:40:23 by dbredykh          #+#    #+#             */
/*   Updated: 2023/10/08 16:16:51 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# define SEP 1 // all == ft_isspace // ex: $echo    a    b; result: a b;
# define WORD 2 // all != specific sign and without ""
# define FIELD 3 // simple quotes
# define EXP_FIELD 4 // double quotes
# define REDIR_OUT 5 // >
# define REDIR_IN 6 // <
# define REDIR_APPEND 7 // >>
# define REDIR_INSOURCE 8 // heredoc <<
# define PIPE 9 // |

// bonus part

# define IF_AND 10 // &&
# define IF_OR 11 // ||
# define PARN_L 12 // (
# define PARN_R 13 // )



#endif
