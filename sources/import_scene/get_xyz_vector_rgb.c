/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_xyz_vector_rgb.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 23:42:11 by mschulme          #+#    #+#             */
/*   Updated: 2023/08/30 14:14:43 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	get_xyz_coordinates(t_list **element, double *data_mat)
{
	*element = (*element)->next;
	if (!get_atof((char *)(*element)->content, &data_mat[1], INT_MAX, true))
		return (false);
	*element = (*element)->next;
	if (!get_atof((char *)(*element)->content, &data_mat[2], INT_MAX, true))
		return (false);
	*element = (*element)->next;
	if (!get_atof((char *)(*element)->content, &data_mat[3], INT_MAX, true))
		return (false);
	*element = (*element)->next;
	return (true);
}

bool	get_xyz_normalized_vector(t_list **element, double *data_mat,
			double tolerance)
{
	double	vector_sum;

	if (!get_atof((char *)(*element)->content, &data_mat[4], 1, true))
		return (false);
	*element = (*element)->next;
	if (!get_atof((char *)(*element)->content, &data_mat[5], 1, true))
		return (false);
	*element = (*element)->next;
	if (!get_atof((char *)(*element)->content, &data_mat[6], 1, true))
		return (false);
	*element = (*element)->next;
	vector_sum = pow(data_mat[4], 2) + pow(data_mat[5], 2)
		+ pow(data_mat[6], 2);
	if (vector_sum < 1 - tolerance || vector_sum > 1 + tolerance)
		return (print_error(ERR_NORMAL, NULL, NULL), false);
	return (true);
}

bool	get_rgb_values(t_list *element, double *data_mat, int max_element_size)
{
	while (element->next->next->next)
		element = element->next;
	if (!get_rgb_or_fov((char *)element->content,
			&data_mat[max_element_size - 3], 255))
	{
		return (false);
	}
	element = element->next;
	if (!get_rgb_or_fov((char *)element->content,
			&data_mat[max_element_size - 2], 255))
	{
		return (false);
	}
	element = element->next;
	if (!get_rgb_or_fov((char *)element->content,
			&data_mat[max_element_size - 1], 255))
	{
		return (false);
	}
	return (true);
}
