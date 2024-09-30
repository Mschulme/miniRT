/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 18:03:25 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/29 15:11:30 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	tokenize_elements(t_data *data);

bool	import_scene(char *rt_file, t_data *data)
{
	int	number_of_lines;

	if (!read_rt_file(&data->rt_file_lines, rt_file))
		return (false);
	number_of_lines = ft_lstsize(data->rt_file_lines);
	if (number_of_lines < 3)
	{
		print_error("rt_file", ERR_NUM_A_C_L, NULL);
		return (ft_lstclear(&data->rt_file_lines, free), false);
	}
	data->elements_array = ft_calloc(sizeof(t_list *), number_of_lines + 1);
	if (!data->elements_array)
		return (ft_lstclear(&data->rt_file_lines, free), false);
	if (!tokenize_elements(data))
		return (clear_import_data(data, false), false);
	if (!convert_to_double_matrix(data, data->count_a_c_l))
		return (clear_import_data(data, true), false);
	return (true);
}

static bool	tokenize_elements(t_data *data)
{
	t_list	*current;
	int		i;

	current = data->rt_file_lines;
	i = 0;
	while (current)
	{
		if (!tokenize_one_element((char *)current->content,
				&data->elements_array[i]))
		{
			return (false);
		}
		current = current->next;
		i++;
	}
	return (true);
}
