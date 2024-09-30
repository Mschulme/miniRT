/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:34:28 by cmenke            #+#    #+#             */
/*   Updated: 2023/10/14 18:50:58 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void		init_cam_and_light(t_data *data, t_vector *cam,
					t_vector *light);
static double	calculate_specular_reflection(const t_info *info,
					const t_data *data, const t_vector light_vector);
static double	calculate_diffuse_sum(double amb, double in, double ld,
					double rd);
static void		calculate_rgb(t_data *data, double amb,
					double diffuse_sum, t_info *info);

void	color_function(t_data *data, bool intersect,
					t_vector light_vector, t_info *info)
{
	double		rd;
	double		ld;
	double		diffuse_sum;
	t_vector	cam;
	t_vector	light;

	init_cam_and_light(data, &cam, &light);
	if (!intersect)
	{
		rd = calculate_specular_reflection(info, data, light_vector);
		ld = v_dot(info->normal, light_vector);
		if (ld < 0 && v_dist(cam, info->intpoint)
			< v_dist(light, info->intpoint))
			set_colors_intersecting(info, data);
		else
		{
			if (ld < 0)
				ld = ld * -1;
			diffuse_sum = calculate_diffuse_sum(data->amb[0],
					data->light[3], ld, rd);
			calculate_rgb(data, data->amb[0], diffuse_sum, info);
		}
	}
	else
		set_colors_intersecting(info, data);
}

static void	init_cam_and_light(t_data *data, t_vector *cam, t_vector *light)
{
	cam->x = data->cam[0];
	cam->y = data->cam[1];
	cam->z = data->cam[2];
	light->x = data->light[0];
	light->y = data->light[1];
	light->z = data->light[2];
}

static double	calculate_specular_reflection(const t_info *info,
	const t_data *data, const t_vector light_vector)
{
	t_vector	cam;
	t_vector	r;
	t_vector	r_cam;
	double		rd;

	cam.x = data->cam[0];
	cam.y = data->cam[1];
	cam.z = data->cam[2];
	r = v_sub(v_scale(info->normal, 2 * v_dot(info->normal, light_vector)),
			light_vector);
	r_cam = v_normalize(v_sub(cam, info->intpoint));
	rd = pow(fmax(0, v_dot(r_cam, r)), 64);
	return (rd);
}

static double	calculate_diffuse_sum(double amb, double in, double ld,
					double rd)
{
	return (amb + in * (ld + rd));
}

static void	calculate_rgb(t_data *data, double amb,
				double diffuse_sum, t_info *info)
{
	info->c_p.r = fmin(amb * data->amb[1] + diffuse_sum * info->color.r, 255);
	info->c_p.g = fmin(amb * data->amb[2] + diffuse_sum * info->color.g, 255);
	info->c_p.b = fmin(amb * data->amb[3] + diffuse_sum * info->color.b, 255);
}
