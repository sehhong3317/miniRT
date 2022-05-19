/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_closest_poi.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:08:14 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/18 23:05:52 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	double	get_poi_sp(t_sp *data, t_vec ray)
{
	double	t;
	t_vec	oc;
	double	r;

	oc = data->centre;
	r = data->radius;
	t = get_root(dot_vecs(ray, ray), -2 * dot_vecs(oc, ray), \
		dot_vecs(oc, oc) - r * r);
	return (t);
}

static	double	get_poi_pl(t_pl *data, t_vec ray)
{
	double	factor;

	factor = dot_vecs(data->n_vector, ray);
	if (!factor)
		exit_with_err("Dividing value by 0 is not allowed ", NULL);
	return (dot_vecs(data->n_vector, data->point) / factor);
}

/* 
    double   get_poi_cylinder(t_cy *data, t_vec ray);
*/

t_poi	find_closest_poi(t_box *box, t_vec ray)
{
	t_obj	*obj;
	t_poi	poi;
	double	t;

	poi.t = INFINITY;
	poi.obj = NULL;
	obj = box->objs;
	while (obj)
	{
		if (obj->type == SPHERE)
			t = get_poi_sp((t_sp *)(obj->data), ray);
		else if (obj->type == PLANE)
			t = get_poi_pl((t_pl *)(obj->data), ray);
		if (t >= 1 && t < poi.t)
		{
			poi.t = t;
			poi.poi = scale_vec(ray, t);
			poi.obj = obj;
		}
		obj = obj->next;
	}
	return (poi);
}
