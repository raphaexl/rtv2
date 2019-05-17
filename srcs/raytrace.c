/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 14:03:14 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/17 20:16:29 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static	int		ft_reflect_light(t_intersect *in)
{
	t_vec3	reflect;

	reflect = ft_reflect(in->ray.dir, in->n);
	in->ray.start = ft_vec3_sum(in->p, ft_vec3_kmult(0.001, reflect));
	in->ray.dir = ft_vec3_normalized(reflect);
	return (1);
}

static void		ft_floor_object(t_texture *t, t_object *o, t_material *m, t_vec3 pos)
{
	float		amount;
	float		sines;

	amount = 100.0;
	if (o->type != SPHERE)
		amount = 1.0;
	if ((m)->chess == 1)
	{
		sines = sin(amount * pos.x) * sin(amount * pos.y) * sin(amount * pos.z);
	if (sines < 0.001)
	{
			(m)->diffuse.red = 0.01f;
			(m)->diffuse.green = 0.01f;
			(m)->diffuse.blue = 0.01f;
	}
	}
	else if (m->chess == 2)
	{
		float u = 0, v = 0;
		if (o->type == SPHERE)
			ft_sphere_uv(pos, &u, &v);
		else if (o->type == TORUS)
			ft_torus_uv(pos, o->radius, &u, &v);
		m->diffuse = ft_texture_image(t, u, v);
	}
}

static t_col3	ft_light(t_scene *s, t_intersect *in, t_material m, t_col3 c)
{
	t_light			*p;
	t_vec3		dist;

	p = s->light;
	ft_floor_object(s->earth, in->current, &m, in->p);
	while (p)
	{
		dist = ft_vec3_sub(p->pos, in->p);
		if ((ft_vec3_dot(in->n, dist) <= 0.0001f))
		{
			p = p->next;
			continue;
		}
		if ((in->t = sqrt(ft_vec3_dot(dist, dist))) && in->t <= 0.001f)
		{
			p = p->next;
			continue;
		}
		in->ray_light = (t_ray){in->p, ft_vec3_kmult(1.0f / in->t, dist)};
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
	if (!ft_scene_intersect(s, in))
		return (s->bg_col3);
	if (depth >= MAX_DEPTH)
		return (c);
	c = ft_col3_sum(c, ft_light(s, in, in->current->material, c));
	if (in->current->material.reflection > 1.001f && ft_metal_sc(in, &c))
		c = ft_col3_mult(c, ft_ray_trace(s, in, depth + 1));
	else if (in->current->material.refraction > 0.0)
	{
		if (ft_dielectric_sc(in, &c, in->current->material.refraction))
			c = ft_col3_mult(c, ft_ray_trace(s, in, depth + 1));
	}
	else if (in->current->material.reflection > 0.01f)
	{
		ft_reflect_light(in);
		c = ft_col3_sum(c, ft_col3_kmult(in->current->material.reflection,
					ft_ray_trace(s, in, depth + 1)));
	}
	return (c);
}
