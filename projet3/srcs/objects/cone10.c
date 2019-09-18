/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:51:06 by ebatchas          #+#    #+#             */
/*   Updated: 2019/06/14 15:07:45 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

static int		ft_cone_cap(t_ray *r, float *t, t_vec3 pos, t_vec3 n);
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

static int	ft_min_ray2(float s[3], float *t, int n)
{
	float	min;
	int		i;

	i = -1;
	while (++i < n)
	{
		if (s[i] > 0.0001)
		{
			min = s[i];
			break ;
		}
	}
	if (i == n)
		return (0);
	while (++i < n)
	{
		if (s[i] > 1e-6 && s[i] < min)
			min = s[i];
	}
	if (min < *t && min > 1e-6)
	{
		*t = min;
		return (n);
	}
	return (0);
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
		new->material = (t_material){DIFFUSE, {ft_rand48(), ft_rand48(), ft_rand48()},
			{ft_rand48(), ft_rand48(), ft_rand48()}, 60.0, 0, 0, 0};
		new->e.cone.angle = M_PI / 8.0;
		new->next = NULL;
	}
	else
		ft_print_error("malloc error");
	return (new);
}

t_vec3			ft_normal_cone(t_cone *cone, t_vec3 p)
{
	if (p.y > 0)
		p.y = -sqrt(p.z * p.z + p.x * p.x) * tan(cone->angle);
	else
		p.y = sqrt(p.z * p.z + p.x * p.x) * tan(cone->angle);
	return (ft_vec3_normalized(p));
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
    //p->e.cone.v = ft_rotate_vec3(p->e.cone.v, p->rotate, 0);
	in->current = p;
	if (!(ret = ft_cone_intersect(&p->e.cone, &r, &in->t)))
		return (0);
	in->p = ft_vec3_sum(r.start, ft_vec3_kmult(in->t, r.dir));
	m = ft_vec3_dot(r.dir, p->e.cone.v) * in->t;
	m += ft_vec3_dot(r.start, p->e.cone.v);
	m *= (1.0 + tan(p->e.cone.angle / 2.0) * tan(p->e.cone.angle / 2.0)); 
	in->n = ft_vec3_sub(in->p, ft_vec3_kmult(m, p->e.cone.v));
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
	t_vec3	x;
	float	s[3];
	float	k;
	float	m0;
	float	m1;
	float	t0;
	float	t1;
	
	k = tan(c->angle / 2.0);
	s[0] = INFINITY;
	s[1] = INFINITY;
	s[2] = INFINITY;
	x = r->start;
	d.a = ft_vec3_dot(r->dir, r->dir) - (1 + k * k) * pow(ft_vec3_dot(r->dir, c->v), 2);
	d.b = 2.0 * (ft_vec3_dot(r->dir, x) - (1 + k * k) * ft_vec3_dot(r->dir, c->v) * ft_vec3_dot(x, c->v));
	d.c = ft_vec3_dot(x, x) - (1 + k * k) * pow(ft_vec3_dot(x, c->v), 2);
	d.delta = d.b * d.b - 4.0 * d.a * d.c;
	if (d.delta < 0.0)
		return (0);
	d.delta = sqrt(d.delta);
	t0 = (-d.b + d.delta) / (2.0 * d.a);
	t1 = (-d.b - d.delta) / (2.0 * d.a);
	if (c->height <= 0)
		return (ft_min_ray(t0, t1, t));
	if (t1 < 0.0001 && t0 < 0.0001)
		return (0);
	if (t0 >= 0)
	{
	m0 = ft_vec3_dot(r->dir, c->v) * (t0);
	m0 += ft_vec3_dot(x, c->v);
	m1 = ft_vec3_dot(r->dir, c->v) * (t0);
	m1 += ft_vec3_dot(ft_vec3_sub(x, ft_vec3_kmult(c->height, c->v)), c->v);
	if (m0 > 0 && m1 < 0)
		s[0] = t0;
	}
	if (t1 >= 0)
	{
	m0 = ft_vec3_dot(r->dir, c->v) * (t1);
	m0 += ft_vec3_dot(x, c->v);
	m1 = ft_vec3_dot(r->dir, c->v) * (t1);
	m1 += ft_vec3_dot(ft_vec3_sub(x, ft_vec3_kmult(c->height, c->v)), c->v);
	if (m0 > 0 && m1 < 0)
		s[1] = t1;
	}
/*	 float	ddn;

	 ddn = ft_vec3_dot(r->dir, c->v);
	 if (fabs(ddn)< 1e-6)
	 {
	  t_vec3 co = (t_vec3){-r->start.x, -r->start.y, -r->start.z};
	  float t3 = ft_vec3_dot(co, c->v) / ddn;
	  float radius = c->height * tan(c->angle);
	  if (t3 > 1e-6 && t3 < *t && (pow(ft_vec3_norm(ft_vec3_sub(ft_vec3_kmult(t3, r->dir), co)), 2) <= radius * radius))
	  {
		  s[2] = t3;
		//  printf("%.2f\t %.2f\t %.2f\n", t0, t1, t3);
	  }
	 }*/
	return (ft_min_ray2(s, t, 3));
}

int			ft_cone_cap(t_ray *r, float *t, t_vec3 pos, t_vec3 n)
{
	float	ddn;
	float	t1;
	t_vec3	dist;

	ddn = ft_vec3_dot(r->dir, n);
	if (ddn == 1.0e-6)
		return (0);
	dist = ft_vec3_sub(pos, r->start);
	t1 = (ft_vec3_dot(dist, n)) / ddn;
	if (t1 < *t && t1 > 1e-6)
	{
		*t = t1;
		if (ddn > 1e-6)
			return (2);
		return (1);
	}
	return (0);
}
