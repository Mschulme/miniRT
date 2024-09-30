/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_cap_intersection2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:46:05 by cmenke            #+#    #+#             */
/*   Updated: 2023/10/14 19:15:36 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	cap_intersection_check(t_info *info, t_vector cam_pos,
			t_vector light, t_cylinder *cyl)
{
	t_vector	pos_plane;
	double		param_int;

	pos_plane = v_add(cyl->cent, v_scale(cyl->dir, cyl->height));
	param_int = (v_dot(pos_plane, cyl->dir)
			- v_dot(cyl->dir, info->intpoint)) / v_dot(cyl->dir, light);
	if (param_int > 1e-6 && param_int < v_dist(info->intpoint, cam_pos))
		if (v_dist(v_add(info->intpoint, v_scale(light, param_int)),
				pos_plane) < cyl->radius)
			return (true);
	pos_plane = v_sub(cyl->cent, v_scale(cyl->dir, cyl->height));
	param_int = (v_dot(pos_plane, cyl->dir)
			- v_dot(cyl->dir, info->intpoint)) / v_dot(cyl->dir, light);
	if (param_int > 1e-6 && param_int < v_dist(info->intpoint, cam_pos))
		if (v_dist(v_add(info->intpoint, v_scale(light, param_int)),
				pos_plane) < cyl->radius)
			return (true);
	return (false);
}
