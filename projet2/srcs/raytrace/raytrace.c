/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:56:51 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/27 09:40:38 by ebatchas         ###   ########.fr       */
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
	t_uv		uv;

	amount = 10.0;
	uv = (t_uv){0.0, .0};
	if (o->type != SPHERE)
		amount = 1.0;
	if ((m)->chess == 1)
	{
		if (o->type == TORUS)
		{
		pos = ft_scale_vec3(pos, o->scale, -1);
		pos = ft_rotate_vec3(pos, o->rotate, -1);
		pos = ft_translate_vec3(pos, o->translate, -1);
		ft_torus_uv(&o->e.torus, ft_vec3(.0, .0, .0), pos, &uv);
		uv.u *= 4.0;
		uv.v *= 4.0;
		int tx = (int)10 * uv.u;
		int ty = (int)10 * uv.v;
		int		pair = (tx & 0x01) == (ty & 0x01);
		int		edge = ((10 * uv.u - tx < 0.1) &&  pair) || (10 * uv.v - ty < 0.1);
		m->diffuse = edge ? ft_col3(1.0, 1.0, 1.0) : ft_col3(1.0, 0.0, 0.0);
		}
		else if (o->type == SPHERE)
		{
		pos = ft_scale_vec3(pos, o->scale, -1);
		pos = ft_rotate_vec3(pos, o->rotate, -1);
		pos = ft_translate_vec3(pos, o->translate, -1);
		pos = ft_vec3_kmult(1.0 / o->e.sphere.radius, pos);
		ft_sphere_uv(&o->e.sphere, ft_vec3(0.0, 0.0, 0), pos, &uv);
	/*	u *= 4.0;
		v *= 4.0;*/
		int tx = (int)10 * uv.u;
		int ty = (int)10 * uv.v;
		int		pair = (tx & 0x01) == (ty & 0x01);
		int		edge = ((10 * uv.u - tx < 0.1) &&  pair) || (10 * uv.v - ty < 0.1);
		m->diffuse = edge ? ft_col3(1.0, 1.0, 1.0) : ft_col3(1.0, 0.0, 0.0);
		}

		else{sines = sin(amount * pos.x) * sin(amount * pos.y) * sin(amount * pos.z);
		if (sines < 0.001)
			(m)->diffuse = (t_col3){1.0, 1.0, 0.0};}
	}
	else if (m->chess == 2 /*&& (o->type == SPHERE)*/)
	{
		pos = ft_scale_vec3(pos, o->scale, -1);
		pos = ft_rotate_vec3(pos, o->rotate, -1);
		pos = ft_translate_vec3(pos, o->translate, -1);
		if (o->type == SPHERE)
		ft_sphere_uv(&o->e.sphere, ft_vec3(0., 0.,0.0), pos, &uv);
		else if (o->type == CYLINDER)
			ft_cylinder_uv(&o->e.cylinder, ft_vec3(.0, .0, 0.0), pos, &uv);
		else if(o->type == PLANE)
			ft_plane_uv(&o->e.plane, o->e.plane.normal, pos, &uv);
		else if(o->type == TORUS)
		ft_torus_uv(&o->e.torus, ft_vec3(0.0, 0.0, 0.), pos, &uv);
		else if(o->type == BOX)
			ft_box_uv(&o->e.box, ft_vec3(0.0, 0.0, 0.0), pos, &uv);
		m->diffuse = ft_texture_image(t, uv.u, uv.v);
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
		return (s->bg_color);/*(s->ft_bg_color(s, in, 0));*/
	c = ft_col3_sum(c, ft_light(s, in, in->current->material, c));
/*	if (in->current->material.chess == 2)
		c = ft_col3_kmult(ft_perlin_turbulence(in->current->material.perlin, c, 5), c);*/
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
