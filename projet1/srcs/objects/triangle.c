/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:59:44 by ebatchas          #+#    #+#             */
/*   Updated: 2019/06/14 16:55:17 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

t_object	*ft_triangle_new(void)
{
	t_object	*new;

	if ((new = (t_object *)malloc(sizeof(*new))))
	{
		new->type = TRIANGLE;
		new->name = "TRIANGLE";
		new->pos = (t_vec3){0.0, 0.0, 0.0};
		new->translate = (t_vec3){0.0, 0.0, 0.0};
		new->rotate = (t_vec3){0.0, 0.0, 0.0};
		new->scale = (t_vec3){1.0f, 1.0f, 1.0f};
		new->e.triangle.a = (t_vec3){-1.0, -1.0, 0.0};
		new->e.triangle.b = (t_vec3){1.0, -1.0, 0.0};
		new->e.triangle.c = (t_vec3){0.0, 1.0, 0.0};
		new->e.triangle.u = 0.0f;
		new->e.triangle.v = 0.0f;
		new->e.triangle.t = 0.0f;
		new->material = (t_material){DIFFUSE, {1.0, 0.0, 0.0, 0.0},
			{ft_rand48(), ft_rand48(), ft_rand48()},
			{ft_rand48(), ft_rand48(), ft_rand48()}, 60.0, 0, 0, 0};
		new->next = NULL;
	}
	else
		ft_print_error("malloc error");
	return (new);
}

t_vec3		ft_normal_triangle(t_triangle *tr)
{
	t_vec3	n;

	n = ft_vec3_cross(ft_vec3_sub(tr->b, tr->a), ft_vec3_sub(tr->c, tr->a));
	return (ft_vec3_normalized(n));
}

int			ft_triangle_compute(t_object *p, t_intersect *in)
{
	t_ray	r;

	r = in->ray;
	r.start = ft_rotate_vec3(r.start, p->rotate, -1);
	r.dir = ft_rotate_vec3(r.dir, p->rotate, -1);
	r.start = ft_translate_vec3(r.start, p->translate, -1);
	if (!ft_triangle_intersect(&p->e.triangle, &r, &in->t))
		return (0);
	in->current = p;
	in->p = ft_vec3_sum(r.start, ft_vec3_kmult(in->t, r.dir));
	in->n = ft_normal_triangle(&p->e.triangle);
	in->p = ft_translate_vec3(in->p, p->translate, 0);
	in->p = ft_rotate_vec3(in->p, p->rotate, 0);
	in->n = ft_rotate_vec3(in->n, p->rotate, 0);
	return (1);
}

int			ft_triangle_intersect(t_triangle *tr, t_ray *r, float *t)
{
	float		det;
	float		invdet;
	t_vec3		h;
	t_vec3		s;
	t_vec3		q;
	t_vec3		edge1;
	t_vec3		edge2;
	float		t1;
	float		u;
	float		v;

	edge1 = ft_vec3_sub(tr->b, tr->a);
   	edge2 = ft_vec3_sub(tr->c, tr->a);
	h = ft_vec3_cross(r->dir, edge2);
	det = ft_vec3_dot(edge1, h);
	if (fabs(det) >= 1.0e-6)
	{
		invdet = 1.0 / det;
		s = ft_vec3_sub(r->start, tr->a);
		u = ft_vec3_dot(s, h) * invdet;
		if (u < 1.0e-6 || u > 1.0001)
			return (0);
		q = ft_vec3_cross(s, edge1);
		v = ft_vec3_dot(r->dir, q) * invdet;
		if ((v < 1.0e-6) || ((u + v) > 1.0001f))
			return (0);
		t1 = ft_vec3_dot(edge2, q) * invdet;
		if (t1 < *t && t1 > 1.0e-6f)
		{
			*t = t1;
			if (det > 0.001f)
				return (2);
			return (1);
		}
	}
	return (0);
}

/*int			ft_triangle_intersect(t_triangle *tr, t_ray *r, float *t)
{
	float		det;
	float		invdet;
	t_vec3		h;
	t_vec3		s;
	t_vec3		q;
	t_vec3		edge1;
	t_vec3		edge2;
	float		t1;

	edge1 = ft_vec3_sub(tr->b, tr->a);
   	edge2 = ft_vec3_sub(tr->c, tr->a);
	h = ft_vec3_cross(r->dir, edge2);
	det = ft_vec3_dot(edge1, h);
	if (fabs(det) >= 1.0e-6)
	{
		invdet = 1.0 / det;
		s = ft_vec3_sub(r->start, tr->a);
		tr->u = ft_vec3_dot(s, h) * invdet;
		if (tr->u < 1.0e-6 || tr->u > 1.0001)
			return (0);
		q = ft_vec3_cross(s, edge1);
		tr->v = ft_vec3_dot(r->dir, q) * invdet;
		if ((tr->v < 1.0e-6) || ((tr->u + tr->v) > 1.0001f))
			return (0);
		tr->t = ft_vec3_dot(edge2, q) * invdet;
		t1 = tr->t;
		if (t1 < *t && t1 > 1.0e-6f)
		{
			*t = t1;
			if (det > 0.001f)
				return (2);
			return (1);
		}
	}
	return (0);
}*/
