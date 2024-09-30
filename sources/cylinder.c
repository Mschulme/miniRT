/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 22:04:11 by mschulme          #+#    #+#             */
/*   Updated: 2023/10/14 19:09:31 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_rescyl	compute_disc_l(t_info *info, t_cylinder cyl, t_vector light)
{
	t_rescyl	rescyl;
	t_vector	dist;
	double		a;
	double		b;
	double		c;

	dist = v_sub(info->intpoint, cyl.cent);
	a = v_dot(light, light) - pow(v_dot(light, cyl.dir), 2);
	b = 2 * (v_dot(light, dist) - v_dot(light, cyl.dir) * v_dot(dist, cyl.dir));
	c = v_dot(dist, dist) - pow(v_dot(dist, cyl.dir), 2) - pow(cyl.radius, 2);
	rescyl.d = b * b - 4 * a * c;
	rescyl.t0 = (-b - sqrt(rescyl.d)) / (2 * a);
	rescyl.t1 = (-b + sqrt(rescyl.d)) / (2 * a);
	return (rescyl);
}

void	init_cyl_and_cam(double *array, t_cylinder *cyl, t_data *data,
			t_vector *cam_pos)
{
	cyl->cent.x = array[1];
	cyl->cent.y = array[2];
	cyl->cent.z = array[3];
	cyl->dir.x = array[4];
	cyl->dir.y = array[5];
	cyl->dir.z = array[6];
	cyl->radius = array[7] * 0.5;
	cyl->height = array[8] * 0.5;
	if (cam_pos)
	{
		cam_pos->x = data->cam[0];
		cam_pos->y = data->cam[1];
		cam_pos->z = data->cam[2];
	}
}

bool	int_cy(t_data *data, t_info *info, double *array, t_vector light)
{
	t_cylinder	cyl;
	t_vector	cam_pos;
	t_rescyl	rescyl;
	double		h0;

	init_cyl_and_cam(array, &cyl, data, &cam_pos);
	if (cap_intersection_check(info, cam_pos, light, &cyl))
		return (true);
	rescyl = compute_disc_l(info, cyl, light);
	h0 = v_dot(v_sub(v_add(info->intpoint, v_scale(light, rescyl.t0)),
				cyl.cent), cyl.dir);
	if (h0 >= -cyl.height && h0 <= cyl.height)
	{
		if (rescyl.t0 <= 1e-6)
			return (false);
		if (rescyl.t0 > 1e-6 && rescyl.t0 < v_dist(info->intpoint, cam_pos))
			return (true);
		if (rescyl.t1 > 1e-6 && rescyl.t1 < v_dist(info->intpoint, cam_pos))
			return (true);
	}
	return (false);
}

void	compute_disc(t_info *info, t_cylinder *cyl, t_rescyl *rescyl)
{
	t_vector	dist;
	double		a;
	double		b;
	double		c;

	dist = v_sub(info->ray.pos, cyl->cent);
	a = v_dot(info->ray.dir, info->ray.dir)
		- pow(v_dot(info->ray.dir, cyl->dir), 2);
	b = 2 * (v_dot(info->ray.dir, dist) - v_dot(info->ray.dir, cyl->dir)
			* v_dot(dist, cyl->dir));
	c = v_dot(dist, dist) - pow(v_dot(dist, cyl->dir), 2) - pow(cyl->radius, 2);
	rescyl->d = b * b - 4 * a * c;
	rescyl->t0 = (-b - sqrt(rescyl->d)) / (2 * a);
	rescyl->t1 = (-b + sqrt(rescyl->d)) / (2 * a);
}

void	dist_cylinder(t_data *data, t_info *info, double *array)
{
	t_rescyl	rescyl;
	t_cylinder	cyl;

	init_cyl_and_cam(array, &cyl, data, NULL);
	cap_intersection(info, &cyl, data);
	compute_disc(info, &cyl, &rescyl);
	if (rescyl.d <= 0 && rescyl.t0 < info->t0)
		return ;
	else
	{
		body_intersection(info, &cyl, &rescyl);
		return ;
	}
}
