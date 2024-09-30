/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_body_intersection.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 19:00:35 by cmenke            #+#    #+#             */
/*   Updated: 2023/10/14 18:54:04 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	body_intersection(t_info *info, const t_cylinder *cyl,
			t_rescyl *rescyl)
{
	t_vector	help1;
	t_vector	help2;
	t_vector	p0;
	double		h0;

	p0 = v_add(info->ray.pos, v_scale(info->ray.dir, rescyl->t0));
	h0 = v_dot(v_sub(p0, cyl->cent), cyl->dir);
	if (h0 >= -cyl->height && h0 <= cyl->height)
	{
		if (rescyl->t0 <= 0)
			rescyl->t0 = rescyl->t1;
		if (rescyl->t0 <= 0)
			return ;
		info->t0 = rescyl->t0;
		info->intpoint = p0;
		help1 = v_sub(info->intpoint, cyl->cent);
		help2 = v_scale(cyl->dir, v_dot(help1, cyl->dir));
		info->normal = v_normalize(v_sub(help1, help2));
		if (v_dot(info->ray.dir, info->normal) > 0)
			info->normal = v_scale(info->normal, -1);
		return ;
	}
	return ;
}
