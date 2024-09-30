/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 22:04:11 by mschulme          #+#    #+#             */
/*   Updated: 2023/10/14 19:16:12 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	int_pl(t_data *data, t_info *info, double *array, t_vector light)
{
	t_vector	cam_pos;
	t_vector	position;
	t_vector	normal;
	double		t;

	position.x = array[1];
	position.y = array[2];
	position.z = array[3];
	normal.x = array[4];
	normal.y = array[5];
	normal.z = array[6];
	cam_pos.x = data->cam[3];
	cam_pos.y = data->cam[4];
	cam_pos.z = data->cam[5];
	if (fabs(v_dot(normal, light)) > 1e-6)
	{
		t = v_dot(v_sub(position, info->intpoint), normal)
			/ (v_dot(normal, light));
		if (t >= 1e-6 && t <= v_length(v_sub(info->intpoint, cam_pos)))
			return (true);
	}
	return (false);
}

void	dist_plane(t_info *info, double *array)
{
	double		help;
	t_vector	pos;
	t_vector	nor;

	pos.x = array[1];
	pos.y = array[2];
	pos.z = array[3];
	nor.x = array[4];
	nor.y = array[5];
	nor.z = array[6];
	help = (v_dot(pos, nor) - v_dot(nor, info->ray.pos))
		/ v_dot(nor, info->ray.dir);
	if (help > 0)
	{
		info->t0 = help;
		info->intpoint = v_add(info->ray.pos, v_scale(info->ray.dir, info->t0));
		if (v_dot(info->ray.dir, nor) > 0)
			info->normal = v_scale(nor, -1);
		else
			info->normal = nor;
	}
}
