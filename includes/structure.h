/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:10:00 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/30 15:45:04 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef enum e_otype
{
	SPHERE = 0,
	PLANE,
	CYLINDER,
	CONE,
	ELSE
}	t_otype;

typedef enum e_ptype
{
	TOP = 0,
	BASE,
	SIDE,
	NONE
}	t_ptype;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_camera
{
	t_vec	pos;
	t_vec	n_vector;
	double	foc_len;
}	t_camera;

typedef struct s_amb
{
	double	b_ratio;
	t_vec	color;
}	t_amb;

typedef struct s_light
{
	t_vec			pos;
	double			b_ratio;
	t_vec			color;
	struct s_light	*next;
}	t_light;

typedef struct s_sp
{
	t_vec	centre;
	double	radius;
	t_vec	color;
}	t_sp;

typedef struct s_pl
{
	t_vec	point;
	t_vec	n_vector;
	t_vec	color;
}	t_pl;

typedef struct s_cy
{
	t_vec	point_top;
	t_vec	point_base;
	t_vec	n_vector;
	double	radius;
	double	height;
	t_vec	color;
}	t_cy;

typedef struct s_cn
{
	double	radius;
	double	height;
	t_vec	point;
	t_vec	n_vector;
	t_vec	color;
}	t_cn;


typedef struct s_obj
{
	t_otype			type;
	void			*data;
	struct s_obj	*next;
}	t_obj;

typedef struct s_poi
{
	double	t;
	t_vec	poi;
	t_obj	*obj;
	t_vec	ray;
	t_vec	view_dir;
	t_ptype	cy_poi_on;
}	t_poi;

typedef struct s_box
{
	void		*mlx;
	void		*win;
	t_camera	*camera;
	t_img		frame;
	t_vec		top_left;
	t_light		*lights;
	t_amb		*amb_light;
	t_obj		*objs;
}	t_box;

#endif