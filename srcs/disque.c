/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disque.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 19:13:22 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/16 16:08:41 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_object	*ft_disk_new(void)
{
	t_object	*new;

	if ((new = (t_object *)malloc(sizeof(*new))))
	{
		new->type = DISK;
		new->name = "DISK";
		new->pos = (t_vec3){0.0, -1.0, 0.0};
		new->translate = (t_vec3){0.0, 0.0, 0.0};
		new->rotate = (t_vec3){0.0, 0.0, 0.0};
		new->normal = (t_vec3){0.0, 1.0, 0.0};
		new->material = (t_material){{1.0, 1.0, 1.0}, {0, 0, 0}, 0, 0, 0, 0};
		new->radius = 1.0;
		new->angle = 0.0;
		new->next = NULL;
	}
	else
		ft_print_error("malloc error");
	return (new);
}

int			ft_disk_compute(t_object *p, t_intersect *in)
{
	t_ray	r;
	int		ret;

	r = in->ray;
	r.start = ft_rotate_vec3(r.start, p->rotate, -1);
	r.dir = ft_rotate_vec3(r.dir, p->rotate, -1);
	r.start = ft_translate_vec3(r.start, p->translate, -1);
	ret = ft_disk_intersect(p, &r, &in->t);
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

int			ft_disk_intersect(t_object *d, t_ray *r, float *t)
{
	float		ddn;
	t_vec3		v;
	t_vec3		dist;
	float		t1;

	ddn = ft_vec3_dot(r->dir, d->normal);
	if (ddn == 0.000001)
		return (0);
	dist = ft_vec3_sub(d->pos, r->start);
	t1 = (ft_vec3_dot(dist, d->normal)) / ddn;
	v = ft_vec3_sum(r->start, ft_vec3_kmult(t1, r->dir));
	if (t1 < *t && t1 > 0.001 && (ft_vec3_dot(v, v) <= d->angle))
	{
		*t = t1;
		if (ddn > 0)
			return (2);
		return (1);
	}
	return (0);
}
