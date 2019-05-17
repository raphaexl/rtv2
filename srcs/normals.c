/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 11:33:09 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/17 16:10:22 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vec3	ft_normal_sphere(t_object *s, t_vec3 p)
{
	return (ft_vec3_kmult(1.0 / s->radius, p));
}

t_vec3	ft_normal_plane(t_object *plane, int ret)
{
	t_vec3	p;

	if (ret == 1)
		p = plane->normal;
	else
		p = ft_vec3_kmult(-1.0, plane->normal);
	return (p);
}

t_vec3	ft_normal_cone(t_object *cone, t_vec3 p)
{
	if (p.y > 0)
		p.y = -sqrt(p.z * p.z + p.x * p.x) * tan(cone->angle);
	else
		p.y = sqrt(p.z * p.z + p.x * p.x) * tan(cone->angle);
	return (ft_vec3_normalized(p));
}

t_vec3	ft_normal_cylindre(t_object *cylindre, t_vec3 p)
{
	p = ft_vec3_kmult(1.0 / cylindre->radius, p);
	return (ft_vec3(p.x, 0.001, p.z));
}

t_vec3	ft_normal_box(t_object *b, t_vec3 h)
{
	t_vec3	c;
	t_vec3	d;
	t_vec3	p;
	float	bias;

	bias = 1.00001;
	c = ft_vec3_kmult(0.5, ft_vec3_sum(b->pos, b->normal));
	d = ft_vec3_kmult(0.5, ft_vec3_sub(b->pos, b->normal));
	d.x = fabs(d.x) * bias;
	d.y = fabs(d.y) * bias;
	d.z = fabs(d.z) * bias;
	p = ft_vec3_sub(h, c);
	return (ft_vec3_normalized(ft_vec3(p.x / d.x, p.y / d.y, p.z / d.z)));
}

t_vec3	ft_normal_torus(t_object *b, t_vec3 h)
{
	t_vec3	p;
	float	x;
	float	y;
	float	z;

	x = h.x;
	y = h.y;
	z = h.z;
	p.x = 4.0 * x * (x * x + y * y + z * z -
		   	b->angle * b->angle - b->radius * b->radius);
	p.y = 4.0 * y * (x * x + y * y + z * z - 
			b->angle * b->angle - b->radius * b->radius + 2.0 * b->radius * b->radius);
	p.z = 4.0 * z * (x * x + y * y + z * z - 
			b->angle * b->angle - b->radius * b->radius);
	return (ft_vec3_normalized(p));
}
