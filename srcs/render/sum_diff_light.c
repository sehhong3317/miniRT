/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sum_diff_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:10:43 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/20 16:44:21 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"



static	t_vec	get_diff_light_sp(t_light *light, t_poi poi)
{
	t_vec	light_vec;
	t_vec	norm_vec;
	double	diff_factor;

	norm_vec = normalize_vec(subtract_vecs(poi.poi, \
		((t_sp *)(poi.obj->data))->centre));
	/* 만약 ray와 구의 법선벡터가 같은 방향일 경우, 카메라가 구 안의 경우임.
	이럴 경우, 아무것도 안보여야 정상 -> (0, 0, 0)의 빛을 반환 */
	if (dot_vecs(norm_vec, poi.ray) > 0)
		return (new_vec(0, 0, 0));
	// 빛위치 ~ 접점까지의 단위벡터
	light_vec = normalize_vec(subtract_vecs(light->pos, poi.poi));
	// 둘사이 dot product (음수 제거)
	diff_factor = fmax(dot_vecs(light_vec, norm_vec), 0);
	// 보너스에서는 new_vec대신 light->color를 넣으면 될듯
	return (scale_vec(new_vec(1, 1, 1), light->b_ratio * diff_factor));
}

static	t_vec	get_diff_light_pl(t_light *light, t_poi poi)
{
	t_vec	light_vec;
	t_vec	norm_vec;
	double	diff_factor;

	norm_vec = ((t_pl *)(poi.obj->data))->n_vector;
	/* 평면의 법선벡터와 ray가 반대 방향일 경우에만 diffuse light를 적절하게
	구할 수 있음 -> 둘이 같은 방향일 경우, 벡터를 평면의 반대방향으로 설정 */
	if (dot_vecs(norm_vec, poi.ray) > 0)
		norm_vec = scale_vec(norm_vec, -1);
	light_vec = normalize_vec(subtract_vecs(light->pos, poi.poi));
	diff_factor = fmax(dot_vecs(light_vec, norm_vec), 0);
	return (scale_vec(new_vec(1, 1, 1), light->b_ratio * diff_factor));
}

// 한 교점을 기준으로 받는 diffuse light -> 모든 빛으로 부터 받는 diffuse light
t_vec	sum_diff_light(t_box *box, t_poi poi)
{
	t_light	*light;
	t_vec	diff_sum;

	diff_sum = new_vec(0, 0, 0);
	light = box->lights;
	while (light)
	{
		if (poi.obj->type == SPHERE)
			diff_sum = add_vecs(diff_sum, get_diff_light_sp(light, poi));
		else if (poi.obj->type == PLANE)
			diff_sum = add_vecs(diff_sum, get_diff_light_pl(light, poi));
		light = light->next;
	}
	return (diff_sum);
}
