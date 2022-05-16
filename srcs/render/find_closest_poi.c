/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_closest_poi.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:08:14 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/16 20:25:23 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static  double	get_poi_sp(t_sp *data, t_vec ray)
{
	double	t;
	t_vec	oc;
	double	r;

	printf("ray: (%f, %f, %f)\n", ray.x, ray.y, ray.z);
	oc = data->centre;
	printf("oc: (%f, %f, %f)\n", oc.x, oc.y, oc.z);
	r = data->radius;
	printf("radius = %f\n", r);
	printf("a = %f, b= %f, c = %f\n", dot_vecs(ray, ray), -2 * dot_vecs(oc, ray),
		dot_vecs(oc, oc) - r * r);
	t = get_root(dot_vecs(ray, ray), -2 * dot_vecs(oc, ray), \
		dot_vecs(oc, oc) - r * r);
	printf("%f\n", t);
	return (t);
}

/* 
    double   get_poi_plane(t_pl *data, t_vec ray);
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
		{	
			t = get_poi_sp((t_sp *)(obj->data), ray);
			// printf("%f\n", t);
		}
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