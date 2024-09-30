/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:53:29 by mschulme          #+#    #+#             */
/*   Updated: 2023/06/22 14:53:29 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2 || is_rt_file(av[1]) == 0)
		return (ft_putstr_fd("Wrong map file", 2), EXIT_FAILURE);
	data = malloc(sizeof(t_data));
	if (!data)
		return (perror("Error: allocating t_data"), EXIT_FAILURE);
	ft_memset(data, 0, sizeof(t_data));
	if (WIDTH < 100 || HEIGHT < 100 || WIDTH > 1920 || HEIGHT > 1080)
		return (ft_putstr_fd("Error: invalid resolution", 2), EXIT_FAILURE);
	data->width = WIDTH;
	data->height = HEIGHT;
	if (!import_scene(av[1], data))
		return (free(data), EXIT_FAILURE);
	clear_import_data(data, false);
	render_and_init_mlx(data);
	return (EXIT_SUCCESS);
}
