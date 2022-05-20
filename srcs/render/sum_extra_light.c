/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sum_extra_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:05:03 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/20 16:13:06 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	sum_extra_light(t_box *box, t_poi poi)
{
	t_light	*light;
	t_vec	total_light;

	total_light = new_vec(0, 0, 0);
	light = box->lights;
	while (light)
	{
		
		light = light->next;
	}
	return (total_light);
}