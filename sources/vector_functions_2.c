/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_functions_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 22:50:45 by mschulme          #+#    #+#             */
/*   Updated: 2023/08/29 22:51:15 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector	v_normalize(t_vector v)
{
	return (v_scale(v, 1 / v_length(v)));
}

t_vector	v_cross(t_vector a, t_vector b)
{
	t_vector	vector;

	vector.x = a.y * b.z - a.z * b.y;
	vector.y = a.z * b.x - a.x * b.z;
	vector.z = a.x * b.y - a.y * b.x;
	return (vector);
}

double	v_dist(t_vector v1, t_vector v2)
{
	double	dx;
	double	dy;
	double	dz;

	dx = v1.x - v2.x;
	dy = v1.y - v2.y;
	dz = v1.z - v2.z;
	return (sqrt(dx * dx + dy * dy + dz * dz));
}

bool	v_equals(t_vector a, t_vector b)
{
	return (a.x == b.x && a.y == b.y && a.z == b.z);
}
