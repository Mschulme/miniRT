/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_objects_intersecting.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:44:09 by cmenke            #+#    #+#             */
/*   Updated: 2023/09/24 19:16:12 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	calculate(double ambient_coefficient,
					double ambient_light_color, double material_color,
					double max_value);

void	set_colors_intersecting(t_info *info, const t_data *data)
{
	info->c_p.r = calculate(data->amb[0], data->amb[1], info->color.r, 255);
	info->c_p.g = calculate(data->amb[0], data->amb[2], info->color.g, 255);
	info->c_p.b = calculate(data->amb[0], data->amb[3], info->color.b, 255);
}

static double	calculate(double ambient_coefficient,
					double ambient_light_color, double material_color,
					double max_value)
{
	return (fmin(ambient_coefficient * (ambient_light_color + material_color),
			max_value));
}
