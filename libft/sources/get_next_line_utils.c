/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:13:07 by mschulme          #+#    #+#             */
/*   Updated: 2023/08/23 21:49:08 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	gnl_strlen(char	*str)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*gnl_strchr(char *str, int c)
{
	if (str == NULL)
		return (NULL);
	if (c == 0)
		return (&str[gnl_strlen(str)]);
	while (*str)
	{
		if (*str++ == (char) c)
			return (str);
	}
	return (NULL);
}

char	*gnl_strjoin(char *save, char *buff, char *join)
{
	int	i;
	int	j;

	if (!save)
	{
		save = malloc(1);
		if (!save)
			return (NULL);
		save[0] = '\0';
	}
	join = malloc(gnl_strlen(save) + gnl_strlen(buff) + 1);
	if (!join)
	{
		free(save);
		return (NULL);
	}
	i = -1;
	while (save[i++ + 1] != 0)
		join[i] = save[i];
	j = 0;
	while (buff[j] != 0)
		join[i++] = buff[j++];
	join[i] = 0;
	free(save);
	return (join);
}
