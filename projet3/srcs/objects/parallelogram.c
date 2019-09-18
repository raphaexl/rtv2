/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallelogram.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:17:32 by ebatchas          #+#    #+#             */
/*   Updated: 2019/09/18 17:07:51 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

t_object	*ft_parallelogram_new(void)
{
	t_object	*new;

	if ((new = (t_object *)malloc(sizeof(*new))))
	{
		new->type = PARALLELOGRAM;
		new->name = "PARALLELOGRAM";
		new->pos = (t_vec3){0.0, 0.0, 0.0};
		new->translate = (t_vec3){0.0, 0.0, 0.0};
		new->rotate = (t_vec3){0.0, 0.0, 0.0};
		new->scale = (t_vec3){1.0f, 1.0f, 1.0f};
		new->e.para.a = (t_vec3){-1.0, -1.0, 0.0};
		new->e.para.b = (t_vec3){1.0, -1.0, 0.0};
		new->e.para.c = (t_vec3){1.0, 1.0, 0.0};
		new->e.para.d = (t_vec3){-1.0, 1.0, 0.0};
		new->material = (t_material){DIFFUSE, {1.0, 0.0, 0.0, 0.0},
			{ft_rand48(), ft_rand48(), ft_rand48()},
			{ft_rand48(), ft_rand48(), ft_rand48()}, 60.0, 0, 0, 0};
		new->next = NULL;
	}
	else
		ft_print_error("malloc error");
	return (new);
}

t_vec3		ft_normal_parallelogram(t_parallelogram *pr)
{
	t_vec3	n;

	n = ft_vec3_cross(ft_vec3_sub(pr->c, pr->a), ft_vec3_sub(pr->d, pr->a));
	return (ft_vec3_normalized(n));
}

int			ft_parallelogram_compute(t_object *p, t_intersect *in)
{
	t_ray	r;

	r = in->ray;
	r.start = ft_rotate_vec3(r.start, p->rotate, -1);
	r.dir = ft_rotate_vec3(r.dir, p->rotate, -1);
	r.start = ft_translate_vec3(r.start, p->translate, -1);
	if (!ft_parallelogram_intersect(&p->e.para, &r, &in->t))
		return (0);
	in->current = p;
	in->p = ft_vec3_sum(r.start, ft_vec3_kmult(in->t, r.dir));
	in->n = ft_normal_parallelogram(&p->e.para);
	in->p = ft_translate_vec3(in->p, p->translate, 0);
	in->p = ft_rotate_vec3(in->p, p->rotate, 0);
	in->n = ft_rotate_vec3(in->n, p->rotate, 0);
	return (1);
}

int			ft_parallelogram_intersect(t_parallelogram *pa, t_ray *r, float *min)
{
	t_delta	d;
	t_vec3	e01;
	t_vec3	e03;
	t_vec3	e23;
	t_vec3	e21;
	t_vec3	e02;
	t_vec3	p;
	t_vec3	p2;
	t_vec3	t;
	t_vec3	t2;
	t_vec3	q;
	t_vec3	q2;
	t_vec3	n;
	float	det;
	float	det2;
	float	invdet;
	float	invdet2;
	float	a;
	float	b;
	float	a2;
	float	b2;
	float	t1;
	float	a11;
	float	b11;
	float	u;
	float	v = 0.0;

	e01 = ft_vec3_sub(pa->b, pa->a);
	e03 = ft_vec3_sub(pa->d, pa->a);
	p = ft_vec3_cross(r->dir, e03);
	det = ft_vec3_dot(e01, p);
	if (fabs(det) >= 1.0e-6)
	{
		invdet = 1.0 / det;
		t = ft_vec3_sub(r->start, pa->a);
		a = ft_vec3_dot(t, p) * invdet;
		if (a < 1.0e-6)
			return (0);
		q = ft_vec3_cross(t, e01);
		b = ft_vec3_dot(r->dir, q) * invdet;
		if (b < 1.0e-6)
			return (0);
		if ((a + b) > 1.0001f)
		{
			e23 = ft_vec3_sub(pa->d, pa->c);
			e21 = ft_vec3_sub(pa->b, pa->c);
			p2  = ft_vec3_cross(r->dir, e21);
			det2 = ft_vec3_dot(e23, p2);
			if (fabs(det2) < 1.0e-6)
				return (0);
			invdet2 = 1.0 / det2;
			t2 = ft_vec3_sub(r->start, pa->c);
			a2 = ft_vec3_dot(t2, p2) * invdet2;
			if (a2 < 1.0e-6)
				return (0);
			q2 = ft_vec3_cross(t2, e23);
			b2 = ft_vec3_dot(r->dir, q2) * invdet2;
			if (b2 < 1.0e-6)
				return (0);
		}
		t1 = ft_vec3_dot(e03, q) * invdet;
	/*	if (t1 < 1e-6 || t1 > *min)
			return (0);*/
		if (t1 < *min && t1 > 1.0e-6)
		{
		e02 = ft_vec3_sub(pa->c, pa->a);
		n = ft_vec3_cross(e01, e03);
		if ((fabs(n.x) >= fabs(n.y)) && (fabs(n.x) >= fabs(n.z)))
		{
			a11 = (e02.y * e03.z - e02.z * e03.y) / n.x;
			b11 = (e01.y * e02.z - e01.z * e02.y) / n.x;
		}
		else if ((fabs(n.y) >= fabs(n.x)) && (fabs(n.y) >= fabs(n.z)))
		{
			a11 = (e02.z * e03.x - e02.x * e03.z) / n.y;
			b11 = (e01.z * e02.x - e01.x * e02.z) / n.y;
		}
		else
		{
			a11 = (e02.x * e03.y - e02.y * e03.x) / n.z;
			b11 = (e01.x * e02.y - e01.y * e02.x) / n.z;
		}

		if (fabs(a11 - 1.0) < 1.0e-6)
		{
			u = a;
			if (fabs(b11 - 1) < 1.0e-6)
				v = b;
			else
				v = b / (u * (b11 - 1) + 1);
		}
		else if (fabs(b11 - 1) < 1.0e-6)
		{
			v = b;
			u = a * (v * (a11 - 1) + 1);
		}
		else
		{
			d.a = -(b11 - 1);
			d.b = a * (b11 - 1) - b * (a11 - 1) - 1;
			d.c = a;
			d.delta = d.b * d.b - 4.0 * d.a * d.c;
			float	s = -0.5 * (d.b + (d.b < 0 ? -1.0 : 1.0) * sqrt(d.delta));
			u = s / d.a;
			if ((u < 0) || (u > 1.0))
				u = d.c / s;
			v = b / (u * (b11 - 1.0) + 1.0);
		}
		*min = t1;
		return (1);
		}
	}
	return (0);
}
