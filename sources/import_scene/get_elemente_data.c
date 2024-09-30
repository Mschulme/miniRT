/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elemente_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:29:01 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/29 20:17:07 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	get_sp_data(t_list *element, double *data_mat)
{
	if (!get_xyz_coordinates(&element, data_mat))
		return (ft_putendl_fd("sp xyz", 2), false);
	if (!get_atof((char *)element->content, &data_mat[4], INT_MAX, false))
		return (ft_putendl_fd("sp diameter", 2), false);
	if (!get_rgb_values(element, data_mat, sp_SIZE))
		return (ft_putendl_fd("sp rgb", 2), false);
	return (true);
}

bool	get_pl_data(t_list *element, double *data_mat)
{
	if (!get_xyz_coordinates(&element, data_mat))
		return (ft_putendl_fd("pl xyz", 2), false);
	if (!get_xyz_normalized_vector(&element, data_mat, 0.01))
		return (ft_putendl_fd("pl xyz vector", 2), false);
	if (!get_rgb_values(element, data_mat, pl_SIZE))
		return (ft_putendl_fd("pl rgb", 2), false);
	return (true);
}

bool	get_cy_data(t_list *element, double *data_mat)
{
	if (!get_xyz_coordinates(&element, data_mat))
		return (ft_putendl_fd("cy xyz", 2), false);
	if (!get_xyz_normalized_vector(&element, data_mat, 0.01))
		return (ft_putendl_fd("cy xyz vector", 2), false);
	if (!get_atof((char *)element->content, &data_mat[7], INT_MAX, false))
		return (ft_putendl_fd("cy diameter", 2), false);
	element = element->next;
	if (!get_atof((char *)element->content, &data_mat[8], INT_MAX, false))
		return (ft_putendl_fd("cy height", 2), false);
	if (!get_rgb_values(element, data_mat, cy_SIZE))
		return (ft_putendl_fd("cy rgb", 2), false);
	return (true);
}
