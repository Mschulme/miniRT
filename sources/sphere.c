/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 22:08:16 by mschulme          #+#    #+#             */
/*   Updated: 2023/10/14 15:34:58 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_sphere(t_info *info, double *array, t_vector light,
			t_sphere *sphere)
{
	sphere->center.x = array[1];
	sphere->center.y = array[2];
	sphere->center.z = array[3];
	sphere->radius = array[4] * 0.5;
	sphere->a = v_dot(light, light);
	sphere->mv = v_sub(info->intpoint, sphere->center);
	sphere->b = 2.0 * v_dot(light, sphere->mv);
	sphere->c = v_dot(sphere->mv, sphere->mv) - pow(sphere->radius, 2);
	sphere->d = sphere->b * sphere->b - 4.0 * sphere->a * sphere->c;
}

bool	int_sp(t_data *data, t_info *info, double *array, t_vector light)
{
	t_sphere	sphere;
	double		epsilon;
	t_vector	cam_pos;
	double		t0;

	cam_pos.x = data->cam[0];
	cam_pos.y = data->cam[1];
	cam_pos.z = data->cam[2];
	epsilon = 1e-6;
	init_sphere(info, array, light, &sphere);
	if (sphere.d < epsilon)
		return (false);
	t0 = (-sphere.b - sqrt(sphere.d)) / (2 * sphere.a);
	if (t0 > epsilon && t0 < v_dist(info->intpoint, cam_pos))
		return (true);
	t0 = (-sphere.b + sqrt(sphere.d)) / (2 * sphere.a);
	if (t0 > epsilon && t0 < v_dist(info->intpoint, cam_pos))
		return (true);
	return (false);
}

void	init_sphere_dist(t_info *info, double *array, t_sphere *sphere)
{
	sphere->center.x = array[1];
	sphere->center.y = array[2];
	sphere->center.z = array[3];
	sphere->radius = array[4] * 0.5;
	sphere->a = v_dot(info->ray.dir, info->ray.dir);
	sphere->mv = v_sub(info->ray.pos, sphere->center);
	sphere->b = 2.0 * v_dot(info->ray.dir, sphere->mv);
	sphere->c = v_dot(sphere->mv, sphere->mv) - pow(sphere->radius, 2);
	sphere->d = pow(sphere->b, 2) - 4.0 * sphere->a * sphere->c;
}

void	dist_sphere(t_info *info, double *array)
{
	t_sphere	sphere;

	init_sphere_dist(info, array, &sphere);
	if (sphere.d < 0)
		return ;
	info->t0 = (-sphere.b - sqrt(sphere.d)) / (2 * sphere.a);
	if (info->t0 > 0)
	{
		info->intpoint = v_add(info->ray.pos, v_scale(info->ray.dir, info->t0));
		info->normal = v_normalize(v_sub(info->intpoint, sphere.center));
		if (v_dot(info->ray.dir, info->normal) > 0)
			info->normal = v_scale(info->normal, -1);
		return ;
	}
	info->t0 = (-sphere.b + sqrt(sphere.d)) / (2 * sphere.a);
	if (info->t0 > 0)
	{
		info->intpoint = v_add(info->ray.pos, v_scale(info->ray.dir, info->t0));
		info->normal = v_normalize(v_sub(info->intpoint, sphere.center));
		if (v_dot(info->ray.dir, info->normal) > 0)
			info->normal = v_scale(info->normal, -1);
		return ;
	}
	return ;
}
