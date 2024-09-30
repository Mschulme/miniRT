/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 00:20:22 by mschulme          #+#    #+#             */
/*   Updated: 2023/08/29 20:47:56 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	exitfunction(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img.mlx_img);
	mlx_destroy_window(data->mlx, data->win);
	clear_import_data(data, true);
	free(data);
	exit (EXIT_SUCCESS);
}

int	exit_function(int Keypress, t_data *data)
{
	if (Keypress == 53)
	{
		mlx_destroy_image(data->mlx, data->img.mlx_img);
		mlx_destroy_window(data->mlx, data->win);
		clear_import_data(data, true);
		free(data);
	}
	exit (EXIT_SUCCESS);
}
