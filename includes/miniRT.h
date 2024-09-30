/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschulme <mschulme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 20:57:15 by mschulme          #+#    #+#             */
/*   Updated: 2023/08/29 20:57:15 by mschulme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef WIDTH
#  define WIDTH 640
# endif

# ifndef HEIGHT
#  define HEIGHT 480
# endif

# include <math.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <ctype.h>
# include <limits.h>

# include "../mlx/mlx.h"
# include "../libft/includes/libft.h"
# include "structs.h"
# include "messages.h"
# include "import_scene.h"

# define A 1
# define C 2
# define L 3
# define SP 4
# define PL 5
# define CY 6

/* v_function.c */

t_vector	v_add(t_vector a, t_vector b);
t_vector	v_sub(t_vector a, t_vector b);
t_vector	v_scale(t_vector v, double s);
double		v_dot(t_vector a, t_vector b);
double		v_length(t_vector v);
t_vector	v_normalize(t_vector v);
t_vector	v_cross(t_vector a, t_vector b);
double		v_dist(t_vector v1, t_vector v2);
bool		v_equals(t_vector a, t_vector b);

/* render_and_init_mlx.c*/

void		render_and_init_mlx(t_data *data);

/* pixel_to_image.c */

void		img_pix_put(t_img *img, unsigned int x, unsigned int y, int color);
int			rgb_to_int(double r, double g, double b);

/* compute_camera_ray.c */

t_ray		compute_camera_ray(t_data *data, int i, int j);

/* sphere.c */

bool		int_sp(t_data *data, t_info *info, double *array,
				t_vector light);
void		dist_sphere(t_info *info, double *array);

/* plane.c */

bool		int_pl(t_data *data, t_info *info, double *array,
				t_vector light);
void		dist_plane(t_info *info, double *array);

/* cylinder.c */

bool		int_cy(t_data *data, t_info *info, double *array, t_vector light);
void		dist_cylinder(t_data *data, t_info *info, double *array);
void		cap_intersection(t_info *info, const t_cylinder *cyl,
				const t_data *data);
void		body_intersection(t_info *info, const t_cylinder *cyl,
				t_rescyl *rescyl);
bool		cap_intersection_check(t_info *info, t_vector cam_pos,
				t_vector light, t_cylinder *cyl);

/* shadows.c */

int			rgbint(double r, double g, double b);
void		imgpixput(t_img *img, unsigned int x, unsigned int y, int color);

void		shadows(t_data *data, t_info *info, int i, int j);
void		color_function(t_data *data, bool intersect,
				t_vector light_vector, t_info *info);
void		set_colors_intersecting(t_info *info, const t_data *data);
/* exit_functions.c */

int			exitfunction(t_data *data);
int			exit_function(int Keypress, t_data *data);

#endif
