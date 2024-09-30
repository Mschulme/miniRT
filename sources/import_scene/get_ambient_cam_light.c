/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ambient_cam_light.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:38:38 by cmenke            #+#    #+#             */
/*   Updated: 2023/09/03 19:04:17 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	get_a_data(t_list *element, double *data_mat, double **amb_reference)
{
	if (!get_atof((char *)element->next->content, &data_mat[1], 1, false))
		return (ft_putendl_fd("ambient lighting: [0.0,1.0]", 2), false);
	if (!get_rgb_values(element, data_mat, A_SIZE))
		return (ft_putendl_fd("a rgb", 2), false);
	*amb_reference = ++data_mat;
	return (true);
}

bool	get_c_data(t_list *element, double *data_mat, double **cam_reference)
{
	if (!get_xyz_coordinates(&element, data_mat))
		return (ft_putendl_fd("c xyz", 2), false);
	if (!get_xyz_normalized_vector(&element, data_mat, 0.01))
		return (ft_putendl_fd("c xyz vector", 2), false);
	if (!get_rgb_or_fov((char *)element->content, &data_mat[7], 180))
		return (ft_putendl_fd("FOV: [0,180]", 2), false);
	*cam_reference = ++data_mat;
	return (true);
}

bool	get_l_data(t_list *element, double *data_mat, double **light_reference)
{
	if (!get_xyz_coordinates(&element, data_mat))
		return (ft_putendl_fd("l xyz", 2), false);
	if (!get_atof((char *)element->content, &data_mat[4], 1, false))
		return (ft_putendl_fd("light brightness: [0.0,1.0]", 2), false);
	if (!get_rgb_values(element, data_mat, L_SIZE))
		return (ft_putendl_fd("l rgb", 2), false);
	*light_reference = ++data_mat;
	return (true);
}
