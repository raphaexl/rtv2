/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 20:12:46 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/16 13:01:46 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static int		ft_min_ray(float t1, float t2, float *t)
{
	if (((t1 < t2 || t2 < 0.001) && t1 > 0.1) && (t1 < *t))
	{
		*t = t1;
		return (1);
	}
	else if (((t2 < t1 || t1 < 0.001) && t2 > 0.1) && (t2 < *t))
	{
		*t = t2;
		return (1);
	}
	else
		return (0);
}

t_object	*ft_box_new(void)
{
	t_object	*new;

	if ((new = (t_object *)malloc(sizeof(*new))))
	{
		new->type = BOX;
		new->name = "BOX";
		new->pos = (t_vec3){0.0, -1.0, 0.0};
		new->translate = (t_vec3){0.0, 0.0, 0.0};
		new->rotate = (t_vec3){0.0, 0.0, 0.0};
		new->normal = (t_vec3){0.0, 0.0, 0.0};
		new->material = (t_material){{1.0, 1.0, 1.0}, {0, 0, 0}, 0, 0, 0, 0};
		new->radius = 0.0;
		new->angle = 0.0;
		new->next = NULL;
	}
	else
		ft_print_error("malloc error");
	return (new);
}

int			ft_box_compute(t_object *p, t_intersect *in)
{
	t_ray	r;

	r = in->ray;
	r.start = ft_rotate_vec3(r.start, p->rotate, -1);
	r.dir = ft_rotate_vec3(r.dir, p->rotate, -1);
	r.start = ft_translate_vec3(r.start, p->translate, -1);
	if (!ft_box_intersect(p, &r, &in->t))
		return (0);
	in->current = p;
	in->p = ft_vec3_sum(r.start, ft_vec3_kmult(in->t, r.dir));
	in->n = ft_normal_box(p, in->p);
	in->p = ft_translate_vec3(in->p, p->translate, 0);
	in->p = ft_rotate_vec3(in->p, p->rotate, 0);
	in->n = ft_rotate_vec3(in->n, p->rotate, 0);
	return (1);
}

int			ft_box_intersect(t_object *b, t_ray *r, float *t)
{
	float		tmin, tmax, tymin, tymax, tzmin, tzmax;
	t_vec3		invdir;
	int			sign[3];
	t_vec3		bounds[2];

	bounds[0] = b->pos;
	bounds[1] = b->normal;
	invdir = (t_vec3){1.0 / r->dir.x, 1.0 / r->dir.y, 1.0 / r->dir.z};
	sign[0] = invdir.x < 0.00001;
	sign[1] = invdir.y < 0.00001;
    sign[2] = invdir.z < 0.00001;
	tmin = (bounds[sign[0]].x - r->start.x) * invdir.x;
	tmax = (bounds[1 - sign[0]].x - r->start.x) * invdir.x;
	tymin = (bounds[sign[1]].y - r->start.y) * invdir.y;
	tymax = (bounds[1 - sign[1]].y - r->start.y) * invdir.y;
	if ((tmin > tymax) || (tymin > tmax))
		return (0);
	if (tymin > tmin)
		tmin = tymin;
	if (tymax < tmax)
		tmax = tymax;
	tzmin = (bounds[sign[2]].z - r->start.z) * invdir.z;
	tzmax = (bounds[1 - sign[2]].z - r->start.z) * invdir.z;
	if ((tmin > tzmax) || (tzmin > tmax))
		return (0);
	if (tzmin > tmin)
		tmin = tzmin;
	if (tzmax < tmax)
		tmax = tzmax;
	return (ft_min_ray(tmin, tmax, t));
}
