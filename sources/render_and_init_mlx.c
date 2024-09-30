/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_and_init_mlx.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 20:39:06 by mschulme          #+#    #+#             */
/*   Updated: 2023/10/14 19:16:30 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	loop_closest(t_data *data, t_info *info, double t_old, int k)
{
	info->t0 = -1;
	if (data->data_mat[k][0] == SP)
		dist_sphere(info, data->data_mat[k]);
	else if (data->data_mat[k][0] == PL)
		dist_plane(info, data->data_mat[k]);
	else if (data->data_mat[k][0] == CY)
		dist_cylinder(data, info, data->data_mat[k]);
	if (info->t0 <= t_old && info->t0 >= 0)
	{
		info->t_old = info->t0;
		info->index_close = k;
		info->save_intpoint = info->intpoint;
		info->save_normal = info->normal;
	}
}

void	find_closest_object(t_data *data, t_info *info)
{
	int			k;

	info->t_old = INFINITY;
	info->index_close = -1;
	k = 0;
	while (data->data_mat[k] != NULL)
	{
		loop_closest(data, info, info->t_old, k);
		k++;
	}
	info->intpoint = info->save_intpoint;
	info->normal = info->save_normal;
	info->t0 = info->t_old;
}

int	render(t_data *data)
{
	t_info	info;
	int		i;
	int		j;

	i = 0;
	while (i < data->width)
	{
		j = 0;
		while (j < data->height)
		{
			info.ray = compute_camera_ray(data, i, j);
			find_closest_object(data, &info);
			if (info.index_close == -1)
				imgpixput(&data->img, i, j, rgbint(0, 0, 0));
			else
				shadows(data, &info, i, j);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.mlx_img, 0, 0);
	return (EXIT_SUCCESS);
}

void	render_and_init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->width, data->height, "miniRT");
	data->img.mlx_img = mlx_new_image(data->mlx, data->width, data->height);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	mlx_loop_hook(data->mlx, &render, data);
	mlx_hook(data->win, 3, 0, exit_function, data);
	mlx_hook(data->win, 17, 0, exitfunction, data);
	mlx_loop(data->mlx);
}
