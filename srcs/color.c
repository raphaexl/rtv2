/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 19:58:56 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/14 20:30:23 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_col3		ft_col3(float r, float g, float b)
{
	t_col3	col3;

	col3.red = r;
	col3.green = g;
	col3.blue = b;
	return (col3);
}

t_col3		ft_col3_sum(t_col3 a, t_col3 b)
{
	t_col3 res;

	res.red = a.red + b.red;
	res.green = a.green + b.green;
	res.blue = a.blue + b.blue;
	return (res);
}

t_col3		ft_col3_mult(t_col3 a, t_col3 b)
{
	t_col3 res;

	res.red = a.red * b.red;
	res.green = a.green * b.green;
	res.blue = a.blue * b.blue;
	return (res);
}

t_col3		ft_col3_kmult(float k, t_col3 a)
{
	t_col3 res;

	res.red = k * a.red;
	res.green = k * a.green;
	res.blue = k * a.blue;
	return (res);
}

t_col3		ft_background_col3(t_ray *r)
{
	t_vec3	dir;
	t_col3		col3;
	float		t;

	dir = ft_vec3_normalized(r->dir);
	t = 0.5 * (dir.y + 1.0);
	dir = ft_vec3_sum(ft_vec3_kmult(1.0 - t, ft_vec3(1.0, 1.0, 1.0)),
			ft_vec3_kmult(t, ft_vec3(0.5, 0.7, 1.0)));
	col3.red = dir.x;
	col3.green = dir.y;
	col3.blue = dir.z;
	return (col3);
}
