/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_cap_intersection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:46:05 by cmenke            #+#    #+#             */
/*   Updated: 2023/10/14 19:14:41 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	top_cap(t_info *info, const t_cylinder *cyl,
					bool *is_within_top_cap_radius);
static double	bot_cap(t_info *info, const t_cylinder *cyl,
					bool *is_within_bot_cap_radius);
static void		update_intersection_data(t_info *info,
					const double param_intersection, const t_cylinder *cyl);
static bool		is_within_cap_radius(const t_info *info, const t_cylinder *cyl,
					const double param_intersection, const t_vector *pos_plane);

void	cap_intersection(t_info *info, const t_cylinder *cyl,
			const t_data *data)
{
	t_vector	cam_dir;
	double		param_intersection_top;
	double		param_intersection_bot;
	bool		is_within_bot_cap_radius;
	bool		is_within_top_cap_radius;

	cam_dir.x = data->cam[3];
	cam_dir.y = data->cam[4];
	cam_dir.z = data->cam[5];
	param_intersection_top = top_cap(info, cyl, &is_within_top_cap_radius);
	param_intersection_bot = bot_cap(info, cyl, &is_within_bot_cap_radius);
	if (param_intersection_bot > 0
		&& ((param_intersection_bot < param_intersection_top)
			|| param_intersection_top < 0) && is_within_bot_cap_radius)
		update_intersection_data(info, param_intersection_bot, cyl);
	else if (param_intersection_top > 0
		&& ((param_intersection_top < param_intersection_bot)
			|| param_intersection_bot < 0) && is_within_top_cap_radius)
		update_intersection_data(info, param_intersection_top, cyl);
}

static double	top_cap(t_info *info, const t_cylinder *cyl,
					bool *is_within_top_cap_radius)
{
	double		param_intersection;
	t_vector	pos_plane;

	pos_plane = v_add(cyl->cent, v_scale(cyl->dir, cyl->height));
	param_intersection = (v_dot(pos_plane, cyl->dir)
			- v_dot(cyl->dir, info->ray.pos)) / v_dot(cyl->dir, info->ray.dir);
	*is_within_top_cap_radius = is_within_cap_radius(info, cyl,
			param_intersection, &pos_plane);
	return (param_intersection);
}

static double	bot_cap(t_info *info, const t_cylinder *cyl,
					bool *is_within_bot_cap_radius)
{
	double		param_intersection;
	t_vector	pos_plane;

	pos_plane = v_sub(cyl->cent, v_scale(cyl->dir, cyl->height));
	param_intersection = (v_dot(pos_plane, cyl->dir)
			- v_dot(cyl->dir, info->ray.pos)) / v_dot(cyl->dir, info->ray.dir);
	*is_within_bot_cap_radius = is_within_cap_radius(info, cyl,
			param_intersection, &pos_plane);
	return (param_intersection);
}

static void	update_intersection_data(t_info *info,
				const double param_intersection, const t_cylinder *cyl)
{
	info->t0 = param_intersection;
	info->intpoint = v_add(info->ray.pos, v_scale(info->ray.dir, info->t0));
	if (v_dot(info->ray.dir, cyl->dir) > 0)
		info->normal = v_scale(cyl->dir, -1);
	else
		info->normal = cyl->dir;
}

static bool	is_within_cap_radius(const t_info *info, const t_cylinder *cyl,
				const double param_intersection, const t_vector *pos_plane)
{
	return (v_dist(v_add(info->ray.pos,
				v_scale(info->ray.dir, param_intersection)), *pos_plane)
		< cyl->radius);
}
