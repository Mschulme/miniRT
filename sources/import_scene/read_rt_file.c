/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rt_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:36:54 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/29 14:58:55 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	open_rt_file(char *rt_file, int *fd);
static bool	read_file_into_list(int fd, t_list **rt_file_lines);

bool	read_rt_file(t_list **rt_file_lines, char *rt_file)
{
	int	fd;

	if (!open_rt_file(rt_file, &fd))
		return (false);
	if (!read_file_into_list(fd, rt_file_lines))
		return (false);
	close(fd);
	return (true);
}

// flags for open work only on macos
static bool	open_rt_file(char *rt_file, int *fd)
{
	*fd = open(rt_file, O_RDWR, O_DIRECTORY);
	if (*fd == -1)
	{
		perror("Error opening rt_file:\n");
		return (false);
	}
	return (true);
}

static bool	read_file_into_list(int fd, t_list **rt_file_lines)
{
	char	*line;
	t_list	*new_node;

	line = get_next_line(fd);
	while (line)
	{
		if (!line[0])
			free(line);
		else
		{
			new_node = ft_lstnew((void *)line);
			if (!new_node)
			{
				perror("Error: saving rt_file line:\n");
				ft_lstclear(rt_file_lines, free);
				free(line);
				return (false);
			}
			ft_lstadd_back(rt_file_lines, new_node);
		}
		line = get_next_line(fd);
	}
	return (true);
}
