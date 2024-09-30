/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_one_element.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:39:41 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/29 19:48:58 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	skip_to_next_non_delimiter(char **line);
static bool	find_next_token(char **string, char **start, t_list **tokens);
static bool	move_one_dot_or_comma(char **line, char c);
static bool	create_one_token(char *start, char *end, t_list **tokens);

bool	tokenize_one_element(char *line, t_list **tokens)
{
	char	*start;

	while (*line)
	{
		skip_to_next_non_delimiter(&line);
		start = line;
		if (!find_next_token(&line, &start, tokens))
			return (false);
		if (!create_one_token(start, line, tokens))
			return (false);
	}
	return (true);
}

static void	skip_to_next_non_delimiter(char **line)
{
	while (**line == ' ')
		*line += 1;
}

static bool	find_next_token(char **string, char **start, t_list **tokens)
{
	while (**string)
	{
		if (**string == ',')
		{
			if (!create_one_token(*start, *string, tokens))
				return (false);
			if (!move_one_dot_or_comma(string, ','))
				return (print_error(ERR_COMMA, NULL, NULL), false);
			*start = *string;
			return (true);
		}
		if (**string == '.' && !move_one_dot_or_comma(string, '.'))
			return (print_error(ERR_POINTS, NULL, NULL), false);
		if (**string == ' ')
			break ;
		if (**string)
			*string += 1;
	}
	return (true);
}

static bool	move_one_dot_or_comma(char **line, char c)
{
	int	max_len;

	max_len = 1;
	while (**line == c)
	{
		if (max_len == 0)
			return (false);
		*line += 1;
		max_len--;
	}
	return (true);
}

static bool	create_one_token(char *start, char *end, t_list **tokens)
{
	t_list		*new_node;
	int			len;
	char		*string;

	len = end - start;
	if (len == 0)
		return (true);
	string = ft_substr(start, 0, len);
	if (!string)
		return (perror("error creating string for token"), false);
	new_node = ft_lstnew((void *)string);
	if (!new_node)
	{
		free(string);
		return (perror("error creating token"), false);
	}
	ft_lstadd_back(tokens, new_node);
	return (true);
}
