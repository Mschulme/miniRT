/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_atof.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:39:36 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/29 20:17:27 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	is_sign_correct(char **str, bool negative_allowed, int *sign);
static bool	is_decimal_fraction_correct(char **str, bool *decimal_fraction);
static bool	calculate_number(char **str, double *number,
				double *fraction_multiplier, bool decimal_fraction);

bool	get_atof(char *str, double *number, double max_value,
			bool negative_allowed)
{
	bool	decimal_fraction;
	double	fraction_multiplier;
	int		sign;

	decimal_fraction = false;
	sign = 1;
	*number = 0;
	fraction_multiplier = 0.1;
	if (!is_sign_correct(&str, negative_allowed, &sign))
		return (false);
	while (*str)
	{
		if (!is_decimal_fraction_correct(&str, &decimal_fraction))
			return (false);
		else if (!ft_isdigit(*str))
			return (print_error(ERR_NUM_ONLY, NULL, NULL), false);
		if (!calculate_number(&str, number,
				&fraction_multiplier, decimal_fraction))
			return (false);
		if (*number > max_value)
			return (print_error(ERR_NUM_TOO_LARGE, NULL, NULL), false);
	}
	*number *= sign;
	return (true);
}

static bool	is_sign_correct(char **str, bool negative_allowed, int *sign)
{
	if (**str == '-' && !negative_allowed)
		return (print_error(ERR_NUM_NEG, NULL, NULL), false);
	else if (**str == '-' && negative_allowed)
		*sign = -1;
	if (**str == '+' || **str == '-')
		(*str)++;
	if (!ft_isdigit(**str) && **str != '.')
		return (print_error(ERR_NUM_ONLY, NULL, NULL), false);
	return (true);
}

static bool	is_decimal_fraction_correct(char **str, bool *decimal_fraction)
{
	if (**str == '.' && !*decimal_fraction)
	{
		(*str)++;
		*decimal_fraction = true;
	}
	else if (**str == '.' && *decimal_fraction)
		return (print_error(ERR_POINTS, NULL, NULL), false);
	return (true);
}

static bool	calculate_number(char **str, double *number,
				double *fraction_multiplier, bool decimal_fraction)
{
	if (*fraction_multiplier < 0.000001)
		return (print_error(ERR_NUM_TOO_PRECISE, NULL, NULL), false);
	if (decimal_fraction)
	{
		*number += *fraction_multiplier * (**str - '0');
		*fraction_multiplier *= 0.1;
		(*str)++;
	}
	else
	{
		*number = *number * 10 + (**str - '0');
		(*str)++;
	}
	return (true);
}
