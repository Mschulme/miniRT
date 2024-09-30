/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 22:41:53 by cmenke            #+#    #+#             */
/*   Updated: 2023/08/30 00:37:23 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "miniRT.h"

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

typedef struct s_rescyl
{
	double	d;
	double	t0;
	double	t1;
}	t_rescyl;

typedef struct s_cylinder
{
	t_vector	cent;
	t_vector	dir;

	double		radius;
	double		height;
}	t_cylinder;

typedef struct s_sphere
{
	t_vector	center;
	double		radius;

	t_vector	mv;
	double		a;
	double		b;
	double		c;
	double		d;
}	t_sphere;

typedef struct s_ray
{
	t_vector	pos;
	t_vector	dir;
}	t_ray;

typedef struct s_camera
{
	t_vector	help;
	t_vector	pos;
	t_vector	dir;
	t_vector	result;
	t_vector	right;
	t_vector	up;
	double		aspect_ratio;
	double		scale;
	double		norm_i;
	double		norm_j;
}	t_camera;

typedef struct s_info
{
	t_ray		ray;
	double		t0;
	t_vector	intpoint;
	t_vector	save_intpoint;
	t_vector	normal;
	t_vector	save_normal;
	double		t_old;
	int			index_close;
	t_color		color;
	t_color		c_p;
}	t_info;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_plane
{
	t_vector	coordinates;
	t_vector	normal_vector;
	t_vector	color;
}	t_plane;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	t_img			img;
	int				width;
	int				height;

	char			*filename;
	char			***total_token;
	char			**token;
	char			*str;
	int				error;
	double			**data_mat;

	t_list			*rt_file_lines;
	t_list			**elements_array;
	char			count_a_c_l[4];
	double			*amb;
	double			*cam;
	double			*light;
}	t_data;

enum	e_element_sizes
{
	A_SIZE = 5,
	C_SIZE = 8,
	L_SIZE = 8,
	sp_SIZE = 8,
	pl_SIZE = 10,
	cy_SIZE = 12
};

#endif