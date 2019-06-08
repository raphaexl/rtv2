/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:32:05 by ebatchas          #+#    #+#             */
/*   Updated: 2019/06/04 22:06:03 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

static int			ft_cone_cap(t_ray *r, float *t, t_vec3 pos, t_vec3 n);

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
	return (0);
}

static float   ft_get_cone_limits(float t, t_ray *r, t_vec3 va, t_vec3 v)
{
	t_vec3 q;
	float	m1, m2;

	if (t < 0)
		return (INFINITY);
	q = ft_vec3_sum(r->start, ft_vec3_kmult(t, r->dir));
	m1 = ft_vec3_dot(va, q);
	m2 = ft_vec3_dot(va, ft_vec3_sub(q, v));
	if (m1 < 0.0 && m2 > 0)
		return (t);
	return (INFINITY);
}

t_object		*ft_cone_new(void)
{
	t_object	*new;

	if ((new = (t_object *)malloc(sizeof(*new))))
	{
		new->type = CONE;
		new->name = "CONE";
		new->pos = (t_vec3){0.0, 0.0, 0.0};
		new->translate = (t_vec3){0.0, 0.0, 0.0};
		new->rotate = (t_vec3){0.0, 0.0, 0.0};
		new->scale = (t_vec3){1.0f, 1.0f, 1.0f};
		new->material = (t_material){{ft_rand48(), ft_rand48(), ft_rand48()},
			{ft_rand48(), ft_rand48(), ft_rand48()}, 60.0, 0, 0, 0};
		new->e.cone.angle = M_PI / 6.0;
		new->e.cone.height = 1.0;
		new->e.cone.v = (t_vec3){0.0, 1.0, 0.0};
		new->next = NULL;
	}
	else
		ft_print_error("malloc error");
	return (new);
}

t_vec3			ft_normal_cone(t_cone *cone, t_vec3 p)
{
	p = ft_vec3_kmult(1.0 / cone->angle, p);
	return (ft_vec3(p.x, 0.001, p.z));
}

int				ft_cone_compute(t_object *p, t_intersect *in)
{
	t_ray	r;
	float	m;
	int		ret;

	r = in->ray;
	r.start = ft_scale_vec3(r.start, p->scale, -1);
	r.start = ft_rotate_vec3(r.start, p->rotate, -1);
	r.start = ft_translate_vec3(r.start, p->translate, -1);
	r.dir = ft_scale_vec3(r.dir, p->scale, -1);
	r.dir = ft_rotate_vec3(r.dir, p->rotate, -1);
	ret = ft_cone_intersect(&p->e.cone, &r, &in->t);
	if (!ret)
		return (0);
	in->current = p;
	in->p = ft_vec3_sum(r.start, ft_vec3_kmult(in->t, r.dir));
	if (ret < 0)
		in->n = ft_vec3_kmult(-1.0, p->e.cone.v);
	else if (ret > 1)
		in->n = p->e.cone.v;
	else
	{
		m = ft_vec3_dot(r.dir, p->e.cone.v) * in->t;
		m += ft_vec3_dot(r.start, p->e.cone.v);
		in->n = ft_vec3_sub(in->p, ft_vec3_kmult(m, p->e.cone.v));
	}
	//	in->n = ft_normal_cone(&p->e.cone, in->p);
	//in->n = ft_vec3_normalized(ft_vec3_sub(in->p, ft_vec3_kmult(m, p->e.cone.v)));
	in->p = ft_translate_vec3(in->p, p->translate, 0);
	in->p = ft_rotate_vec3(in->p, p->rotate, 0);
	in->p = ft_scale_vec3(in->p, p->scale, 0);
	in->n = ft_rotate_vec3(in->n, p->rotate, 0);
	in->n = ft_scale_vec3(in->n, p->scale, -1);
	in->n = ft_vec3_normalized(in->n);
	return (1);
}

int				ft_cone_intersect(t_cone *c, t_ray *r, float *t)
{
	t_delta	d;
	t_vec3 pa;
	t_vec3 va;
	t_vec3  x;
	t_vec3 a, b;
	float		anglesin, t1, t2, m;
	float		anglecos;

	anglecos = pow(cos(c->angle), 2.0);
	anglesin = pow(sin(c->angle), 2.0);
	pa = (t_vec3){0.0, 0.0, 0.0};
	va = ft_vec3_normalized(ft_vec3_sub(pa, c->v));
	x = ft_vec3_sub(r->start, pa);
	a = ft_vec3_sub(r->dir, ft_vec3_kmult(ft_vec3_dot(r->dir, va), va));
	b = ft_vec3_sub(x, ft_vec3_kmult(ft_vec3_dot(x, va), va));
	d.a = anglecos * ft_vec3_dot(a, a) - anglesin * ft_vec3_dot(r->dir, va) * ft_vec3_dot(r->dir, va);
	d.b = 2.0 * anglecos * ft_vec3_dot(a, b) - 2.0 * anglesin * ft_vec3_dot(r->dir, va) * ft_vec3_dot(x, va); 
	d.c = anglecos * ft_vec3_dot(b, b) -anglesin * ft_vec3_dot(x, va) * ft_vec3_dot(x, va);
	d.delta = d.b * d.b - 4.0 * d.a * d.c;
	if (d.delta < 0.00000001)
		return (0);
	d.delta = sqrt(d.delta);
	t1 = ft_get_cone_limits((-d.b + d.delta) / (2.0 * d.a), r, va, c->v);
	t2 = ft_get_cone_limits((-d.b - d.delta) / (2.0 * d.a), r, va, c->v);
	//	return (ft_min_ray(t1, t2, t));
	if (c->height <= 0)
		return (ft_min_ray(t1, t2, t));
	if (!ft_min_ray(t1, t2, t))
		return (0);
	m = ft_vec3_dot(r->dir, c->v) * (*t);
	m += ft_vec3_dot(r->start, c->v);
	if (m > c->height / 2.0 - 5.0e-1)
	{
		if (ft_cone_cap(r, t, ft_vec3_kmult(*t, c->v), c->v))
		{
			write(1, "disk ?\n", 7);
			return (2);
		}
	}
	return (1);
}

int			ft_cone_cap(t_ray *r, float *t, t_vec3 pos, t_vec3 n)
{
	float	ddn;
	float	t1;
	t_vec3	x;

	ddn = ft_vec3_dot(r->dir, n);
	if (fabs(ddn) < 1.0e-6)
		return (0);
	x = ft_vec3_sub(pos, r->start);
	t1 = (ft_vec3_dot(x, n)) / ddn;
	if (fabs(t1) > 1e-6)
	{
		*t = fabs(t1);
		if (ddn > 1e-6)
			return (2);
		return (1);
	}
	return (0);
}


/*
   int				ft_cone_intersect(t_cone *c, t_ray *r, float *t)
   {
   t_delta	d;
   t_vec3	dist;
   t_vec3	alpha, beta;

   dist = r->start;
   alpha = ft_vec3_sub(r->dir, ft_vec3_kmult(ft_vec3_dot(r->dir, c->v), c->v));
   beta = ft_vec3_sub(dist, ft_vec3_kmult(ft_vec3_dot(dist, c->v), c->v));
   d.a = (alpha.x * alpha.x + alpha.y * alpha.y + alpha.z * alpha.z);
   d.b = 2.0 * (alpha.x * beta.x + alpha.y * beta.y + alpha.z * beta.z);
   d.c = (beta.x * beta.x + beta.y * beta.y + beta.z * beta.z) - c->radius2;
   d.delta = d.b * d.b - 4.0 * d.a * d.c;
   if (d.delta < 0.0)
   return (0);
   d.delta = sqrt(d.delta);
   return (ft_min_ray((-d.b + d.delta) / (2.0 * d.a),
   (-d.b - d.delta) / (2.0 * d.a), t));
   }*/
