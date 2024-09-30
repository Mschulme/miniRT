/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_camera_ray.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:10:35 by mschulme          #+#    #+#             */
/*   Updated: 2023/09/24 17:16:09 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	initialize_camera_data(const t_data *data, t_camera *cam);

t_ray	compute_camera_ray(t_data *data, int i, int j)
{
	t_camera	cam;

	initialize_camera_data(data, &cam);
	cam.aspect_ratio = data->width / (double)data->height;
	cam.scale = tan((data->cam[6] * (M_PI / 180)) * 0.5);
	cam.norm_i = (2 * (i / (double)data->width) - 1)
		* cam.aspect_ratio * cam.scale;
	cam.norm_j = (1 - 2 * (j / (double)data->height)) * cam.scale;
	if (v_dot(cam.up, cam.dir) == 1 || v_dot(cam.up, cam.dir) == -1)
		cam.right = v_normalize(v_cross((t_vector){0, 1, 0}, cam.dir));
	else
		cam.right = v_normalize(v_cross(cam.up, cam.dir));
	if (v_dot(cam.up, cam.dir) == 1 || v_dot(cam.up, cam.dir) == -1)
		cam.right = v_normalize(v_cross((t_vector){0, 1, 0}, cam.dir));
	else
		cam.right = v_normalize(v_cross(cam.up, cam.dir));
	cam.up = v_normalize(v_cross(cam.right, cam.dir));
	cam.help = v_add(v_add(v_add(cam.pos, cam.dir),
				v_scale(cam.right, cam.norm_i)), v_scale(cam.up, cam.norm_j));
	cam.result = v_normalize(v_sub(cam.help, cam.pos));
	return ((t_ray){cam.pos, cam.result});
}

static void	initialize_camera_data(const t_data *data, t_camera *cam)
{
	cam->up.x = 0;
	cam->up.y = 0;
	cam->up.z = -1;
	cam->up.z = -1;
	cam->pos.x = data->cam[0];
	cam->pos.y = data->cam[1];
	cam->pos.z = data->cam[2];
	cam->dir.x = data->cam[3];
	cam->dir.y = data->cam[4];
	cam->dir.z = data->cam[5];
}
