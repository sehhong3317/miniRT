/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sum_extra_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:05:03 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/31 05:35:20 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	t_vec	get_norm_vec_cy(t_poi poi)
{
	t_vec	norm_vec;
	t_vec	cp;
	t_vec	h;

	norm_vec = new_vec(0, 0, 0);
	cp = subtract_vecs(poi.poi, ((t_cy*)(poi.obj->data))->point_base);
	h = ((t_cy*)(poi.obj->data))->n_vector;
	if (poi.cy_poi_on == SIDE)
		norm_vec = normalize_vec(add_vecs(scale_vec(h ,dot_vecs(cp, h)), cp));
	else if (poi.cy_poi_on == TOP)
		norm_vec = ((t_cy*)(poi.obj->data))->n_vector;
	else if (poi.cy_poi_on == BASE)
		norm_vec = scale_vec(((t_cy*)(poi.obj->data))->n_vector, -1);
	return (norm_vec);
}

static	t_vec	get_norm_vec(t_poi poi)
{
	t_vec	norm_vec;
	
	if (poi.obj->type == SPHERE)
		norm_vec = normalize_vec(subtract_vecs(poi.poi, \
			((t_sp *)(poi.obj->data))->centre));
	else if (poi.obj->type == PLANE)
	{	
		norm_vec = ((t_pl *)(poi.obj->data))->n_vector;
		if (dot_vecs(norm_vec, poi.ray) > 0)
			norm_vec = scale_vec(norm_vec, -1);
	}
	else if (poi.obj->type == CYLINDER)
		norm_vec = get_norm_vec_cy(poi);
	else
		norm_vec = new_vec(0, 0, 0);
	return (norm_vec);
}

static	double	get_diff_factor(t_vec light_vec, t_vec norm_vec)
{
	return (fmax(dot_vecs(normalize_vec(light_vec), norm_vec), 0));
}

static	double	get_spec_factor(t_poi poi, t_vec light_vec, t_vec norm_vec)
{
	t_vec	reflect_vec;
	double	spec;

	reflect_vec = normalize_vec(add_vecs(scale_vec(light_vec, -1), \
		scale_vec(norm_vec, 2 * dot_vecs(norm_vec, light_vec))));
	spec = pow(fmax(dot_vecs(reflect_vec, poi.view_dir), 0.0), 2);
	// 0.7 = specular light strength
	return (spec * 0.7);
}

static	t_vec	get_extra_light(t_light *light, t_poi poi)
{
	t_vec	light_vec;
	t_vec	norm_vec;
	double	factor;

	factor = 0;
	norm_vec = get_norm_vec(poi);
	if (poi.obj->type == SPHERE && dot_vecs(norm_vec, poi.ray) > 0)
		return (new_vec(0, 0, 0));
	light_vec = subtract_vecs(light->pos, poi.poi);
	if (poi.obj->type == PLANE && dot_vecs(norm_vec, light_vec) <= 0)
		return (new_vec(0, 0, 0));
	factor += get_diff_factor(light_vec, norm_vec);
	factor += get_spec_factor(poi, light_vec, norm_vec);
	//원래 흰색 빛: (255, 255, 255) -> (1, 1, 1)
	return (scale_vec(new_vec(1, 1, 1), factor * light->b_ratio * 0.5));
}

t_vec	sum_extra_light(t_box *box, t_poi poi)
{
	t_light	*light;
	t_vec	total_light;

	total_light = new_vec(0, 0, 0);
	light = box->lights;
	while (light)
	{
		total_light = add_vecs(total_light, get_extra_light(light, poi));
		light = light->next;
	}
	return (total_light);
}