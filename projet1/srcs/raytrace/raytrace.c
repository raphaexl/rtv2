/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:56:51 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/02 20:03:31 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

static int		ft_reflect_light(t_intersect *in)
{
	t_vec3	reflect;

	reflect = ft_reflect(in->ray.dir, in->n);
	in->ray.start = ft_vec3_sum(in->p, ft_vec3_kmult(0.001, reflect));
	in->ray.dir = ft_vec3_normalized(reflect);
	return (1);
}

static void		ft_floor_object(t_texture *t, t_object *o, t_material *m,
		t_vec3 pos)
{
	float		amount;
	float		sines;
	float		u;
	float		v;

	amount = 10.0;
	u = 0.0;
	v = 0.0;
	if (o->type != SPHERE)
		amount = 1.0;
	if ((m)->chess == 1)
	{
		sines = sin(amount * pos.x) * sin(amount * pos.y) * sin(amount * pos.z);
		if (sines < 0.001)
			(m)->diffuse = (t_col3){1.0, 1.0, 0.0};
	}
	else if ((m->chess == 2) && (o->type == SPHERE))
	{
		pos = ft_scale_vec3(pos, o->scale, -1);
		pos = ft_rotate_vec3(pos, o->rotate, -1);
		pos = ft_translate_vec3(pos, o->translate, -1);
		pos = ft_vec3_kmult(1.0 / o->e.sphere.radius, pos);
		ft_sphere_uv(pos, &u, &v);
		m->diffuse = ft_texture_image(t, u, v);
	}
}

static	int	ft_illuminate(t_light *l, t_intersect *in)
{
	t_vec3		dist;

	if (l->type)
	{
		dist = ft_vec3_sub(l->pos, in->p);
		if (ft_vec3_dot(in->n, dist) <= 0.0f)
			return (0);
		in->t = sqrt(ft_vec3_dot(dist, dist));
		if (in->t <= 0.0f)
			return (0);
		in->ray_light = (t_ray){in->p, ft_vec3_kmult(1.0 / in->t, dist)};
	}
	else
	{
		if (ft_vec3_dot(in->n, l->dir) <= 0.0f)
			return (0);
		in->t = INFINITY;
		t_vec3	po = ft_vec3_sum(in->p, ft_vec3_kmult(1e-4, in->n));
		in->ray_light = (t_ray){po, l->dir};	
	}
	return (1);
}

static t_col3	ft_light(t_scene *s, t_intersect *in, t_material m, t_col3 c)
{
	t_light		*p;

	p = s->light;
	ft_floor_object(s->earth, in->current, &m, in->p);
	while (p)
	{
		if (!ft_illuminate(p, in))
		{
			p = p->next;
			continue;
		}
		if (!ft_scene_intersectl(s, in))
			c = ft_col3_sum(c, ft_trace(in, &m, p, &s->ambiant));
		p = p->next;
	}
	return (c);
}

t_col3			ft_ray_trace(t_scene *s, t_intersect *in, int depth)
{
	t_col3		c;

	c = (t_col3){0.0, 0.0, 0.0};
	in->t = INFINITY;
	if (depth >= MAX_DEPTH)
		return (c);
	if (!ft_scene_intersect(s, in))
		return (s->bg_color);
	c = ft_col3_sum(c, ft_light(s, in, in->current->material, c));
	if ((in->current->material.albedo[2] > 1.0) && ft_metal_sc(in, &c))
		c = ft_col3_mult(c, ft_ray_trace(s, in, depth + 1));
	else if (in->current->material.albedo[3] > 0.0)
	{
		if (ft_dielectric_sc(in, &c, in->current->material.albedo[3]))
			c = ft_col3_mult(c, ft_ray_trace(s, in, depth + 1));
	}
	else if (in->current->material.albedo[2] > 0.0)
	{
		ft_reflect_light(in);
		c = ft_col3_sum(c, ft_col3_kmult(in->current->material.albedo[2],
					ft_ray_trace(s, in, depth + 1)));
	}
	return (c);
}
/*
t_col3			ft_ray_trace(t_scene *s, t_intersect *in, int depth)
{
	t_col3		c;

	c = (t_col3){0.0, 0.0, 0.0};
	in->t = INFINITY;
	if (depth >= MAX_DEPTH)
		return (c);
	if (!ft_scene_intersect(s, in))
		return (s->bg_color);
	if ((in->current->material.type == METAL) && ft_metal_sc(in, &c))
	{
		ft_reflect_light(in);
		c = ft_col3_sum(c, ft_col3_kmult(in->current->material.albedo[2],
					ft_ray_trace(s, in, depth + 1)));
		c = ft_col3_mult(c, ft_ray_trace(s, in, depth + 1));
	}
	else if (in->current->material.type == DIELECTRIC)
	{
		if (ft_dielectric_sc(in, &c, in->current->material.albedo[3]))
			c = ft_col3_mult(c, ft_ray_trace(s, in, depth + 1));
	}
	else
		c = ft_col3_sum(c, ft_light(s, in, in->current->material, c));
	return (c);
}*/
