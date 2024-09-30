/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_rt_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 22:04:23 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/25 16:11:11 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	is_rt_file(const char *filename)
{
	const char	*dot;

	dot = ft_strrchr(filename, '.');
	if (!dot || dot == filename)
		return (false);
	if (ft_strcmp(dot, ".rt") == 0)
		return (true);
	return (false);
}
