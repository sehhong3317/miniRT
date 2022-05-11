/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:10:00 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/11 22:13:47 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef	struct s_vec3	t_vec;
typedef struct s_vec3 	t_point;
typedef struct s_vec3 	t_color;

typedef enum e_otype
{
	SPHERE = 0,
	PLANE,
	CYLINDER,
	ELSE
}	t_otype;

typedef	struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

struct	s_vec3
{
	double	x;
	double	y;
	double	z;
};

typedef	struct	s_ray
{
	t_point	origin;
	t_vec	dir;
}	t_ray;

typedef	struct	s_camera
{
	t_point	pos;
	t_vec	n_vector;
	double	foc_len;
	int		is_filled;
}	t_camera;

typedef	struct	s_light
{
	t_point	pos;
	double	b_ratio;
	t_color	color;
	int		is_filled;
}	t_light;


typedef	struct s_sp
{
	t_point	centre;
	double	radius;
	t_color	color;
}	t_sp;

typedef	struct s_pl
{
	t_point	point;
	t_vec	n_vector;
	t_color	color;
}	t_pl;

typedef struct s_cy
{
	t_point	point;
	t_vec	n_vector;
	double	radius;
	double	height;
	t_color	color;
}	t_cy;

typedef struct	s_obj
{
	t_otype			type;
	void			*obj;
	struct	s_obj	*next;
}	t_obj;

typedef	struct	s_box
{
	void		*mlx;
	void		*win;
	t_camera	camera;
	t_img		frame;
	t_point		top_left;
	t_light		light;
	t_light		amb_light;
	t_obj		*objs;
}	t_box;

#endif