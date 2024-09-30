/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_double_matrix.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 16:12:05 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/29 22:45:43 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	create_data_mat(t_list *rt_file_lines, double ***data_mat);
static bool	is_element_size_correct(t_list *element, int *element_identifier,
				int *size_of_element, char count_a_c_l[4]);
static bool	get_element_identifier(t_list *element,
				int *element_identifier, char count_a_c_l[4]);
static bool	get_element_data(t_list	*element, double *data_mat,
				int element_identifier, t_data *data);

bool	convert_to_double_matrix(t_data *data, char count_a_c_l[4])
{
	int		i;
	int		size_of_element;
	int		element_identifier;

	i = 0;
	if (!create_data_mat(data->rt_file_lines, &data->data_mat))
		return (false);
	while (data->elements_array[i])
	{
		if (!is_element_size_correct(data->elements_array[i],
				&element_identifier, &size_of_element, data->count_a_c_l))
			return (false);
		data->data_mat[i] = ft_calloc(sizeof(double), size_of_element);
		if (!data->data_mat[i])
			return (perror("Error: couldn't allocate data_mat[i]"), false);
		if (!get_element_data(data->elements_array[i],
				data->data_mat[i], element_identifier, data))
			return (false);
		i++;
	}
	if (count_a_c_l[A] != 1 || count_a_c_l[C] != 1 || count_a_c_l[L] != 1)
		return (print_error(ERR_NUM_A_C_L, NULL, NULL), false);
	return (true);
}

static bool	create_data_mat(t_list *rt_file_lines, double ***data_mat)
{
	int	number_of_elements;

	number_of_elements = ft_lstsize(rt_file_lines);
	*data_mat = ft_calloc(sizeof(double *), number_of_elements + 1);
	if (!*data_mat)
		return (perror("Error: couldn't allocate data_mat"), false);
	return (true);
}

static bool	is_element_size_correct(t_list *element, int *element_identifier,
			int *size_of_element, char count_a_c_l[4])
{
	*size_of_element = ft_lstsize(element);
	if (!get_element_identifier(element, element_identifier, count_a_c_l))
		return (false);
	if (*element_identifier == A && *size_of_element != A_SIZE)
		print_error("object", (char *)element->content, ERR_NUM_ARGS);
	else if (*element_identifier == C && *size_of_element != C_SIZE)
		print_error("object", (char *)element->content, ERR_NUM_ARGS);
	else if (*element_identifier == L && *size_of_element != L_SIZE)
		print_error("object", (char *)element->content, ERR_NUM_ARGS);
	else if (*element_identifier == SP && *size_of_element != sp_SIZE)
		print_error("object", (char *)element->content, ERR_NUM_ARGS);
	else if (*element_identifier == PL && *size_of_element != pl_SIZE)
		print_error("object", (char *)element->content, ERR_NUM_ARGS);
	else if (*element_identifier == CY && *size_of_element != cy_SIZE)
		print_error("object", (char *)element->content, ERR_NUM_ARGS);
	else
		return (true);
	return (false);
}

static bool	get_element_identifier(t_list *element,
				int *element_identifier, char count_a_c_l[4])
{
	*element_identifier = -1;
	if (ft_strcmp((char *)(element->content), "A") == 0)
		*element_identifier = A;
	else if (ft_strcmp((char *)(element->content), "C") == 0)
		*element_identifier = C;
	else if (ft_strcmp((char *)(element->content), "L") == 0)
		*element_identifier = L;
	else if (ft_strcmp((char *)(element->content), "sp") == 0)
		*element_identifier = SP;
	else if (ft_strcmp((char *)(element->content), "pl") == 0)
		*element_identifier = PL;
	else if (ft_strcmp((char *)(element->content), "cy") == 0)
		*element_identifier = CY;
	if (*element_identifier <= 3 && *element_identifier > 0
		&& ++(count_a_c_l[*element_identifier]) != 1)
		return (print_error("too many", (char *)element->content, NULL), false);
	if (*element_identifier == -1)
		return (print_error("invalid", (char *)element->content, NULL), false);
	return (true);
}

static bool	get_element_data(t_list	*element, double *data_mat,
				int element_identifier, t_data *data)
{
	int		i;

	i = 0;
	data_mat[0] = element_identifier;
	if (data_mat[0] == A && !get_a_data(element, data_mat, &data->amb))
		return (false);
	else if (data_mat[0] == C && !get_c_data(element, data_mat, &data->cam))
		return (false);
	else if (data_mat[0] == L && !get_l_data(element, data_mat, &data->light))
		return (false);
	else if (data_mat[0] == SP && !get_sp_data(element, data_mat))
		return (false);
	else if (data_mat[0] == PL && !get_pl_data(element, data_mat))
		return (false);
	else if (data_mat[0] == CY && !get_cy_data(element, data_mat))
		return (false);
	return (true);
}
