/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 06:39:09 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/16 15:30:46 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_object	*ft_plane_new(void)
{
	t_object	*new;

	if ((new = (t_object *)malloc(sizeof(*new))))
	{
		new->type = PLANE;
		new->name = "PLANE";
		new->pos = (t_vec3){0.0, -1.0, 0.0};
		new->translate = (t_vec3){0.0, 0.0, 0.0};
		new->rotate = (t_vec3){0.0, 0.0, 0.0};
		new->normal = (t_vec3){0.0, 1.0, 0.0};
		new->material = (t_material){{1.0, 1.0, 1.0}, {0, 0, 0}, 0, 0, 0, 0};
		new->radius = 0.0;
		new->angle = 0.0;
		new->next = NULL;
	}
	else
		ft_print_error("malloc error");
	return (new);
}

int			ft_plane_compute(t_object *p, t_intersect *in)
{
	t_ray	r;
	int		ret;

	r = in->ray;
	r.start = ft_rotate_vec3(r.start, p->rotate, -1);
	r.dir = ft_rotate_vec3(r.dir, p->rotate, -1);
	r.start = ft_translate_vec3(r.start, p->translate, -1);
	ret = ft_plane_intersect(p, &r, &in->t);
	if (!ret)
		return (0);
	in->current = p;
	in->p = ft_vec3_sum(r.start, ft_vec3_kmult(in->t, r.dir));
	in->n = ft_normal_plane(p, ret);
	in->p = ft_translate_vec3(in->p, p->translate, 0);
	in->p = ft_rotate_vec3(in->p, p->rotate, 0);
	in->n = ft_rotate_vec3(in->n, p->rotate, 0);
	return (1);
}

int			ft_plane_intersect(t_object *plane, t_ray *r, float *t)
{
	float	ddn;
	t_vec3		dist;
	float		t1;

	ddn = ft_vec3_dot(plane->normal, r->dir);
	if (fabs(ddn) > 0.01f)
	{
		dist = ft_vec3_sub(plane->pos, r->start);
		t1 = (ft_vec3_dot(dist, plane->normal)) / ddn;
		if (t1 < *t && t1 > 0.01f)
		{
			*t = t1;
			if (ddn > 0.01f)
				return (2);
			return (1);
		}
	}
	return (0);
}
