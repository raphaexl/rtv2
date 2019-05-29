/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:52:00 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/29 20:30:46 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

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

t_object		*ft_cylindre_new(void)
{
	t_object	*new;

	if ((new = (t_object *)malloc(sizeof(*new))))
	{
		new->type = CYLINDRE;
		new->name = "CYLINDRE";
		new->pos = (t_vec3){0.0, 0.0, 0.0};
		new->translate = (t_vec3){0.0, 0.0, 0.0};
		new->rotate = (t_vec3){0.0, 0.0, 0.0};
		new->scale = (t_vec3){1.0f, 1.0f, 1.0f};
		new->material = (t_material){{ft_rand48(), ft_rand48(), ft_rand48()},
			{ft_rand48(), ft_rand48(), ft_rand48()}, 60.0, 0, 0, 0};
		new->e.cylinder.radius = 1.0;
		new->e.cylinder.radius2 = 1.0;
		new->e.cylinder.height = 1.0;
		new->e.cylinder.v = (t_vec3){0.0, 1.0, 0.0};
		new->next = NULL;
	}
	else
		ft_print_error("malloc error");
	return (new);
}

t_vec3			ft_normal_cylindre(t_cylinder *cylindre, t_vec3 p)
{
	p = ft_vec3_kmult(1.0 / cylindre->radius, p);
	return (ft_vec3(p.x, 0.001, p.z));
}

int				ft_cylindre_compute(t_object *p, t_intersect *in)
{
	t_ray	r;
	float	m;

	r = in->ray;
	r.start = ft_scale_vec3(r.start, p->scale, -1);
	r.start = ft_rotate_vec3(r.start, p->rotate, -1);
	r.start = ft_translate_vec3(r.start, p->translate, -1);
	r.dir = ft_scale_vec3(r.dir, p->scale, -1);
	r.dir = ft_rotate_vec3(r.dir, p->rotate, -1);
	if (!ft_cylindre_intersect(&p->e.cylinder, &r, &in->t))
		return (0);
	in->current = p;
	in->p = ft_vec3_sum(r.start, ft_vec3_kmult(in->t, r.dir));
	m = ft_vec3_dot(r.dir, p->e.cylinder.v) * in->t;
	m += ft_vec3_dot(r.start, p->e.cylinder.v);
//	in->n = ft_normal_cylindre(&p->e.cylinder, in->p);
	in->n = ft_vec3_sub(in->p, ft_vec3_kmult(m, p->e.cylinder.v));
	//in->n = ft_vec3_normalized(ft_vec3_sub(in->p, ft_vec3_kmult(m, p->e.cylinder.v)));
	in->p = ft_translate_vec3(in->p, p->translate, 0);
	in->p = ft_rotate_vec3(in->p, p->rotate, 0);
	in->p = ft_scale_vec3(in->p, p->scale, 0);
	in->n = ft_rotate_vec3(in->n, p->rotate, 0);
	in->n = ft_scale_vec3(in->n, p->scale, -1);
	in->n = ft_vec3_normalized(in->n);
	return (1);
}

int				ft_cylindre_intersect(t_cylinder *c, t_ray *r, float *t)
{
	t_delta	d;
	t_vec3	x;
	float	m0;
	float	m1;
	float	t0;
	float	t1;
	
	x = r->start;
	d.a = ft_vec3_dot(r->dir, r->dir) - pow(ft_vec3_dot(r->dir, c->v), 2);
	d.b = 2.0 * (ft_vec3_dot(r->dir, x) - ft_vec3_dot(r->dir, c->v) * ft_vec3_dot(x, c->v));
	d.c = ft_vec3_dot(x, x) - pow(ft_vec3_dot(x, c->v), 2) - c->radius2;
	d.delta = d.b * d.b - 4.0 * d.a * d.c;
	if (d.delta < 0.0)
		return (0);
	d.delta = sqrt(d.delta);
	t0 = (-d.b + d.delta) / (2.0 * d.a);
	t1 = (-d.b - d.delta) / (2.0 * d.a);
	if (c->height <= 0)
		return (ft_min_ray(t0, t1, t));
	if (t0 > t1)
	{
		m0 = t0;
		t0 = t1;
		t1 = m0;
	}
	m0 = ft_vec3_dot(r->dir, c->v) * (t0);
	m0 += ft_vec3_dot(x, c->v);
	m1 = ft_vec3_dot(r->dir, c->v) * (t1);
	m1 += ft_vec3_dot(x, c->v);
	if (m0 < -c->height)
	{
		if(m1 < -c->height)
			return (0);
		else
		{
			float th = t0 + (t1 - t0) * (m0 + c->height) / (m0 - m1);
			if (th < 1e-6 || th > *t)
				return (0);
			 *t = th;
			return (1);
		}
	}
	else if (m0 >= -c->height && m0 <= c->height)
	{
		if (t0 < 1e-6 || t0 > *t)
			return (0);
		*t = t0;
		return (1);
	}
	else if (m0 > c->height)
	{
		if (m1 > c->height)
			return (0);
		else
		{
			float th = t0 + (t1 - t0) * (m0 - c->height) / (m0 - m1);
			if (th < 1e-6 || th > *t)
				return (0);
			*t = th;
			return (1);
		}
	}
	return (0);
}

/*int				ft_cylindre_intersect(t_cylinder *c, t_ray *r, float *t)
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
