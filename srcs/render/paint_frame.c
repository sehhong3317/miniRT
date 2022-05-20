/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_frame.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 11:49:38 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/20 16:05:18 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	t_vec	get_obj_color(t_poi poi)
{
	t_otype	type;
	t_vec	color;

	type = poi.obj->type;
	if (type == SPHERE)
		color = ((t_sp *)(poi.obj->data))->color;
	else if (type == PLANE)
		color = ((t_pl *)(poi.obj->data))->color;
	else
		color = ((t_cy *)(poi.obj->data))->color;
	return (color);
}

// static	void	check_range(t_vec *color)
// {
// 	if (color->x > 255)
// 		color->x = 255;
// 	if (color->y > 255)
// 		color->y = 255;
// 	if (color->z > 255)
// 		color->z = 255;
// }

static	t_vec	get_pixel_color(t_box *box, int i, int j)
{
	t_vec	sum;
	t_poi	poi;
	t_vec	ray;
	t_vec	pixel_color;

	ray = new_vec(box->top_left.x + i, box->top_left.y - j, box->top_left.z);
	sum = new_vec(0, 0, 0);
	poi = find_closest_poi(box, ray);
	if (poi.t != INFINITY)
	{
		sum = add_vecs(sum, scale_vec(box->amb_light->color, \
			box->amb_light->b_ratio));
		sum = add_vecs(sum, sum_extra_light(box, poi));
		// sum = add_vecs(sum, sum_diff_light(box, poi));
		// sum_spec_light: 보너스부분
		// sum = add_vecs(sum, sum_spec_light(box, poi));
		pixel_color = multiply_vecs(sum, get_obj_color(poi));
		// check_range(&pixel_color); -> 필요한가?
		return (pixel_color);
	}
	return (sum);
}

// why? 이 함수에 대한 이해 100프로 이해못함 ㅎ
static	void	paint_pixel(t_img *img, int x, int y, t_vec color)
{
	char	*dst;
	int		color_int;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	color_int = ((int)color.x << 16 | (int)color.y << 8 | (int)color.z);
	*(unsigned int *)dst = color_int;
}

void	paint_frame(t_box *box)
{
	int	i;
	int	j;

	box->frame.img = mlx_new_image(box->mlx, SCN_WIDTH, SCN_HEIGHT);
	box->frame.addr = mlx_get_data_addr(box->frame.img, \
		&box->frame.bits_per_pixel, &box->frame.line_length, \
		&box->frame.endian);
	i = -1;
	while (++i < SCN_WIDTH)
	{
		j = -1;
		while (++j < SCN_HEIGHT)
			paint_pixel(&(box->frame), i, j, get_pixel_color(box, i, j));
	}
}