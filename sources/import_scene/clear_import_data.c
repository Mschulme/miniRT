/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_import_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:46:11 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/29 14:14:14 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	clear_data_mat(t_data *data);
static void	clear_elements_array(t_list **elements_array);

void	clear_import_data(t_data *data, bool clear_matrix)
{
	ft_lstclear(&data->rt_file_lines, free);
	clear_elements_array(data->elements_array);
	data->elements_array = NULL;
	if (clear_matrix)
		clear_data_mat(data);
}

static void	clear_data_mat(t_data *data)
{
	int	i;

	i = 0;
	if (!data->data_mat)
		return ;
	while (data->data_mat[i])
	{
		free(data->data_mat[i]);
		i++;
	}
	free(data->data_mat);
	data->data_mat = NULL;
	data->amb = NULL;
	data->cam = NULL;
	data->light = NULL;
}

static void	clear_elements_array(t_list **elements_array)
{
	int	i;

	i = 0;
	if (!elements_array)
		return ;
	while (elements_array[i])
	{
		ft_lstclear(&elements_array[i], free);
		i++;
	}
	free(elements_array);
}
