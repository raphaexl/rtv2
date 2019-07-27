/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:55:48 by ebatchas          #+#    #+#             */
/*   Updated: 2019/06/14 16:54:24 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

t_object	*ft_plane_new(void)
{
	t_object	*new;

	if ((new = (t_object *)malloc(sizeof(*new))))
	{
		new->type = PLANE;
		new->name = "PLANE";
		new->pos = (t_vec3){0.0, 0.0, 0.0};
		new->translate = (t_vec3){0.0, -1.0, 0.0};
		new->rotate = (t_vec3){0.0, 0.0, 0.0};
		new->scale = (t_vec3){1.0f, 1.0f, 1.0f};
		new->e.plane.normal = (t_vec3){0.0, 1.0, 0.0};
		new->material = (t_material){DIFFUSE, {1.0, 0.0, 0.0, 0.0},
			{ft_rand48(), ft_rand48(), ft_rand48()},
			{ft_rand48(), ft_rand48(), ft_rand48()}, 60.0, 0, 0, 0};
		new->next = NULL;
	}
	else
		ft_print_error("malloc error");
	return (new);
}

t_vec3		ft_normal_plane(t_plane *plane, int ret)
{
	t_vec3	p;

	if (ret == 1)
		p = plane->normal;
	else
		p = ft_vec3_kmult(-1.0, plane->normal);
	return (p);
}

int			ft_plane_compute(t_object *p, t_intersect *in)
{
	t_ray	r;
	int		ret;

	r = in->ray;
	r.start = ft_rotate_vec3(r.start, p->rotate, -1);
	r.dir = ft_rotate_vec3(r.dir, p->rotate, -1);
	r.start = ft_translate_vec3(r.start, p->translate, -1);
	ret = ft_plane_intersect(&p->e.plane, &r, &in->t);
	if (!ret)
		return (0);
	in->current = p;
	in->p = ft_vec3_sum(r.start, ft_vec3_kmult(in->t, r.dir));
	in->n = ft_normal_plane(&p->e.plane, ret);
	in->p = ft_translate_vec3(in->p, p->translate, 0);
	in->p = ft_rotate_vec3(in->p, p->rotate, 0);
	in->n = ft_rotate_vec3(in->n, p->rotate, 0);
	return (1);
}

int			ft_plane_intersect(t_plane *plane, t_ray *r, float *t)
{
	float		ddn;
	t_vec3		dist;
	float		t1;

	ddn = ft_vec3_dot(plane->normal, r->dir);
	if (fabs(ddn) >= 1.0e-6)
	{
		dist = (t_vec3){-r->start.x, -r->start.y, -r->start.z};
		t1 = (ft_vec3_dot(dist, plane->normal)) / ddn;
		if (t1 < *t && t1 > 0.001f)
		{
			*t = t1;
			if (ddn > 0.001f)
				return (2);
			return (1);
		}
	}
	return (0);
}
