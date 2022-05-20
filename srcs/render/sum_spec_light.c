/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sum_spec_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:10:03 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/20 13:20:40 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	t_vec	get_spec_light_sp(t_light *light, t_poi poi, t_vec view_dir)
{
	t_vec	reflect_vec;
	t_vec	light_vec;
	t_vec	norm_vec;
	double	spec_factor;

	norm_vec = normalize_vec(subtract_vecs(poi.poi, \
		((t_sp *)(poi.obj->data))->centre));
	if (dot_vecs(norm_vec, poi.ray) > 0)
		return (new_vec(0, 0, 0));
	light_vec = subtract_vecs(light->pos, poi.poi);
	reflect_vec = add_vecs(scale_vec(light->pos, -1), \
		scale_vec(view_dir, 2 * dot_vecs(norm_vec, light_vec)));
	spec_factor = pow(dot_vecs(reflect_vec, view_dir) / \
		(get_vec_len(reflect_vec) * get_vec_len(view_dir)), 132);
	return (scale_vec(new_vec(1, 1, 1), light->b_ratio * spec_factor));
}

static	t_vec	get_spec_light_pl(t_light *light, t_poi poi, t_vec view_dir)
{
	t_vec	reflect_vec;
	t_vec	light_vec;
	t_vec	norm_vec;
	double	spec_factor;

	norm_vec = ((t_pl *)(poi.obj->data))->n_vector;
	if (dot_vecs(norm_vec, poi.ray) > 0)
		norm_vec = scale_vec(norm_vec, -1);
	light_vec = normalize_vec(subtract_vecs(light->pos, poi.poi));
	reflect_vec =add_vecs();
	spec_factor = pow()
	
}

t_vec	sum_spec_light(t_box *box, t_poi poi)
{
	t_light	*light;
	t_vec	spec_sum;
	t_vec	view_dir;

	spec_sum = new_vec(0, 0, 0);
	view_dir = normalize_vec(subtract_vecs(box->camera->pos, poi.poi));
	light = box->lights;
	while (light)
	{
		if (poi.obj->type == SPHERE)
			spec_sum = add_vecs(spec_sum, get_spec_light_sp(light, poi, view_dir));
		else if (poi.obj->type == PLANE)
			spec_sum = add_vecs(spec_summ get_spec_light_pl(light, poim view_dir));
		light = light->next;
	}
	return (spec_sum);
}
