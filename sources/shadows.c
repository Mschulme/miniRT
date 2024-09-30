/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:13:20 by mschulme          #+#    #+#             */
/*   Updated: 2023/10/14 15:39:26 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// https://www.inf.ed.ac.uk/teaching/courses/cg/lectures/cg4_2016.pdf

void	color_object(t_data *data, t_info *info, int i, int j)
{
	t_vector	light;
	t_vector	light_vector;
	bool		intersect;
	int			k;

	light.x = data->light[0];
	light.y = data->light[1];
	light.z = data->light[2];
	light_vector = v_normalize(v_sub(light, info->intpoint));
	intersect = false;
	k = 0;
	while (data->data_mat[k] != NULL)
	{
		if (data->data_mat[k][0] == SP)
			intersect = int_sp(data, info, data->data_mat[k], light_vector);
		else if (data->data_mat[k][0] == PL)
			intersect = int_pl(data, info, data->data_mat[k], light_vector);
		else if (data->data_mat[k][0] == CY)
			intersect = int_cy(data, info, data->data_mat[k], light_vector);
		if (intersect == true)
			break ;
		k++;
	}
	color_function(data, intersect, light_vector, info);
	imgpixput(&data->img, i, j, rgbint(info->c_p.r, info->c_p.g, info->c_p.b));
}

void	get_color(t_data *data, t_info *info, int rgb)
{
	info->color.r = data->data_mat[info->index_close][rgb];
	info->color.g = data->data_mat[info->index_close][rgb + 1];
	info->color.b = data->data_mat[info->index_close][rgb + 2];
}

void	shadows(t_data *data, t_info *info, int i, int j)
{
	if (data->data_mat[info->index_close][0] == SP)
		get_color(data, info, 5);
	else if (data->data_mat[info->index_close][0] == CY)
		get_color(data, info, 9);
	else if (data->data_mat[info->index_close][0] == PL)
		get_color(data, info, 7);
	color_object(data, info, i, j);
}
