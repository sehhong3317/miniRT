/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_frame.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 11:49:38 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/22 18:56:10 by sehhong          ###   ########.fr       */
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

static	double	limit_range(double x)
{
	double	new_x;

	if (x > 255)
		new_x = 255;
	else if (x < 0)
		new_x = 0;
	else
		new_x = x;
	return (new_x);
}

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
		// printf("haha");
		// sum = 최종 빛의 양
		sum = add_vecs(sum, scale_vec(box->amb_light->color, \
			box->amb_light->b_ratio / 255));
		sum = add_vecs(sum, sum_extra_light(box, poi));
		// 픽셀 색 = 최종 빛의 양 * 물체의 색
		pixel_color = multiply_vecs(sum, get_obj_color(poi));
		// 각 rgb값이 0 - 255사이인가?
		pixel_color.x = limit_range(pixel_color.x);
		pixel_color.y = limit_range(pixel_color.y);
		pixel_color.z = limit_range(pixel_color.z);
		// printf("pixel color = (%f, %f, %f)\n", pixel_color.x, pixel_color.y, pixel_color.z);
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
