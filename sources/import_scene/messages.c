/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:20:51 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/29 14:35:04 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_error(char *error_message, char *info1, char *info2)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(error_message, STDERR_FILENO);
	if (info1)
	{
		ft_putstr_fd(" ", STDERR_FILENO);
		ft_putstr_fd(info1, STDERR_FILENO);
	}
	if (info2)
	{
		ft_putstr_fd(" ", STDERR_FILENO);
		ft_putstr_fd(info2, STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
}
