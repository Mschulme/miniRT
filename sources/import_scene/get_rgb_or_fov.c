/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rgb_or_fov.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:53:08 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/29 19:57:21 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// For RGB and FOV values, the range of values is [0, 255] and [0, 180]
bool	get_rgb_or_fov(char *str, double *number, double max_value)
{
	*number = 0;
	if (*str == '-')
		return (print_error(ERR_NUM_NEG, NULL, NULL), false);
	if (*str == '+')
		str++;
	if (!ft_isdigit(*str))
		return (print_error(ERR_NUM_ONLY, NULL, NULL), false);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (print_error(ERR_NUM_ONLY, NULL, NULL), false);
		*number = *number * 10 + (*str++ - '0');
		if (*number > max_value)
			return (print_error(ERR_NUM_TOO_LARGE, NULL, NULL), false);
	}
	return (true);
}
