/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:21:45 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/29 19:58:48 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H

# include "miniRT.h"

# define ERR_NUM_ARGS "contains wrong number of arguments"
# define ERR_NUM_A_C_L "must have exactly one A, C, and L element" 

# define ERR_NUM_NEG "negative number not allowed"
# define ERR_NUM_ONLY "only numbers allowed"
# define ERR_NUM_TOO_LARGE "number too large"

# define ERR_POINTS "too many ."
# define ERR_COMMA "too many ,"
# define ERR_NUM_TOO_PRECISE "too many decimal places - max 6"

# define ERR_NORMAL "orientation vector is not normalized"

/* import_scene */
	/* messages.c*/
void	print_error(char *error_message, char *info1, char *info2);

#endif