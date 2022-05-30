/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_root.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 01:12:08 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/31 02:19:50 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// root(t) = -1 : 근이 없다
// 반환값은 항상 >= 0 이거나 -1(근이 없다는 뜻)
double	get_root(double a, double b, double c)
{
	double	root;
	double	root1;
	double	root2;
	double	discriminant;

	root = -1;
	if (a == 0)
	{
		if (b && c)
			root = -1 * c / b;
		else if (b && !c)
			root = 0;
		return (root);
	}
	discriminant = b * b - 4 * a * c;
	if (discriminant > 0)
	{
		root1 = (-b - sqrt(discriminant)) * 0.5 * (1 / a);
		root2 = (-b + sqrt(discriminant)) * 0.5 * (1 / a);
		if (root1 >= 0 && root2 >= 0)
			root = root1;
		else if (root1 < 0 && root2 >= 0)
			root = root2;
	}
	else if (!discriminant)
		root = -b * 0.5 * (1 / a);
	if (root < 0)
		root = -1;
	return (root);
}
