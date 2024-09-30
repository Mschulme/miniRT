/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_scene.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:06:42 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/29 20:15:30 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMPORT_SCENE_H
# define IMPORT_SCENE_H

# include "miniRT.h"

/* import_scene */
	/* import_scene.c */
bool	import_scene(char *rt_file, t_data *data);
	/* is_rt_file.c */
bool	is_rt_file(const char *filename);
	/* read_rt_file.c */
bool	read_rt_file(t_list **rt_file_lines, char *rt_file);
	/* tokenize_one_element.c */
bool	tokenize_one_element(char *line, t_list **tokens);
	/* convert_to_double_matrix.c */
bool	convert_to_double_matrix(t_data *data, char count_a_c_l[4]);
	/* get_ambient_cam_light.c */
bool	get_a_data(t_list *element, double *data_mat, double **amb_reference);
bool	get_c_data(t_list *element, double *data_mat, double **cam_reference);
bool	get_l_data(t_list *element, double *data_mat, double **light_reference);
	/* get_elemente_data.c */
bool	get_sp_data(t_list *element, double *data_mat);
bool	get_pl_data(t_list *element, double *data_mat);
bool	get_cy_data(t_list *element, double *data_mat);
	/* get_xyz_vector_rgb.c */
bool	get_xyz_coordinates(t_list **element, double *data_mat);
bool	get_xyz_normalized_vector(t_list **element, double *data_mat,
			double tolerance);
bool	get_rgb_values(t_list *element, double *data_mat, int max_element_size);
	/* get_rgb_or_fov.c */
bool	get_rgb_or_fov(char *str, double *number, double max_value);
	/* get_atof.c */
bool	get_atof(char *str, double *number, double max_value,
			bool negative_allowed);
	/* clear_import_data.c */
void	clear_import_data(t_data *data, bool clear_matrix);
	/* print_functions.c */
// void	print_list(t_list *rt_file_lines)
// void	print_double_data_mat(double **data_mat);
// void	print_all_element_tokens(t_list **elements_array);

#endif