/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:58:58 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/29 15:08:18 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// void	print_list(t_list *rt_file_lines)
// {
// 	t_list	*current;

// 	current = rt_file_lines;
// 	while (current)
// 	{
// 		printf("%s\n", (char *)current->content);
// 		current = current->next;
// 	}
// }

// void	print_double_data_mat(double **data_mat)
// {
// 	int	i;
// 	int	j;
// 	int	size_of_element;

// 	i = 0;
// 	while (data_mat[i])
// 	{
// 		if (data_mat[i][0] == A)
// 			size_of_element = A_SIZE;
// 		else if (data_mat[i][0] == C)
// 			size_of_element = C_SIZE;
// 		else if (data_mat[i][0] == L)
// 			size_of_element = L_SIZE;
// 		else if (data_mat[i][0] == sp)
// 			size_of_element = sp_SIZE;
// 		else if (data_mat[i][0] == pl)
// 			size_of_element = pl_SIZE;
// 		else if (data_mat[i][0] == cy)
// 			size_of_element = cy_SIZE;
// 		else
// 			return ;
// 		j = 0;
// 		while (j < size_of_element)
// 		{
// 			printf("%f ", data_mat[i][j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// }

// void	print_all_element_tokens(t_list **elements_array)
// {
// 	int	i;

// 	i = 0;
// 	while (elements_array[i])
// 	{
// 		printf("element %d:\n", i);
// 		print_list(elements_array[i]);
// 		printf("\n");
// 		i++;
// 	}
// }