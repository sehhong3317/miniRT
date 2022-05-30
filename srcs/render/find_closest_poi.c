/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_closest_poi.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:08:14 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/31 02:46:55 by sehhong          ###   ########.fr       */
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
		return (0);
	return (dot_vecs(data->n_vector, data->point) / factor);
}

static	double	find_t(t_cy *data, t_vec ray)
{
	t_vec	co;
	double	a;
	double	b;
	double	c;

	co = scale_vec(data->point_base, -1);
	a = dot_vecs(ray, ray) - pow(dot_vecs(ray, data->n_vector), 2);
	b = 2 * (dot_vecs(ray, co) - (dot_vecs(ray, data->n_vector) * dot_vecs(co, data->n_vector)));
	c = dot_vecs(co, co) - pow(dot_vecs(co, data->n_vector), 2) - (data->radius * data->radius);
	return (get_root(a, b, c));
}

// 옆면에서의 접점구하기
static	double	get_poi_cy_side(t_cy *data, t_vec ray)
{
	double	t;
	t_vec	poi;
	double	prj;

	t = find_t(data, ray);
	if (t > 1)
	{	
		poi = scale_vec(ray, t);
		prj = dot_vecs(subtract_vecs(poi, data->point_base), data->n_vector);
		if (prj > 0 && prj < data->height)
			return (t);
	}
	return (1);
}

// t = 1 ?
static	double	get_poi_cy_cap(t_cy *data, t_vec ray, int is_top)
{
	double	t;
	double	factor;
	double	distance;
	t_vec	centre;

	factor = dot_vecs(ray, data->n_vector);
	if (!factor)
		return (1);
	if (is_top)
		centre = data->point_top;
	else
		centre = data->point_base;
	t = (dot_vecs(data->n_vector, centre) / factor);
	distance = get_distance(scale_vec(ray, t), centre);
	if (distance > data->radius)
		t = 1;
	return (t);
}

//tmin = INFINITY?
static	double   get_poi_cy(t_cy *data, t_vec ray, t_ptype *ptype)
{
	double	tmin;
	double	t;

	tmin = INFINITY;
	t = get_poi_cy_side(data, ray);
	if (t > 1 && t < tmin)
	{	
		tmin = t;
		*ptype = SIDE;
	}
	t = get_poi_cy_cap(data, ray, 1);
	if (t > 1 && t < tmin)
	{	
		tmin = t;
		*ptype = TOP;
	}
	t= get_poi_cy_cap(data, ray, 0);
	if (t > 1 && t < tmin)
	{	
		tmin = t;
		*ptype = BASE;
	}
	return (tmin);
}

t_poi	find_closest_poi(t_box *box, t_vec ray)
{
	t_obj	*obj;
	t_poi	poi;
	double	t;

	poi.t = INFINITY;
	poi.obj = NULL;
	poi.ray = ray;
	poi.view_dir = new_vec(0, 0, 0);
	poi.cy_poi_on = NONE;
	obj = box->objs;
	while (obj)
	{
		if (obj->type == SPHERE)
			t = get_poi_sp((t_sp *)(obj->data), ray);
		else if (obj->type == PLANE)
			t = get_poi_pl((t_pl *)(obj->data), ray);
		else if (obj->type == CYLINDER)
			t = get_poi_cy((t_cy *)(obj->data), ray, &(poi.cy_poi_on));
		if (t >= 0 && t < poi.t)
		{
			poi.t = t;
			poi.poi = scale_vec(ray, t);
			poi.obj = obj;
			poi.view_dir = normalize_vec(scale_vec(poi.poi, -1));
			// if (obj->type != CYLINDER && poi.cy_poi_on != NONE)
			// 	poi.cy_poi_on = NONE;
		}
		obj = obj->next;
	}
	return (poi);
}
