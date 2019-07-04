/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathtrace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:55:14 by ebatchas          #+#    #+#             */
/*   Updated: 2019/06/26 18:18:32 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

t_vec3		ft_random_unit(void)
{
	t_vec3	p;

	p = (t_vec3){1.0, 1.0, 1.0};
	while (p.x * p.x + p.y * p.y + p.z * p.z >= 1.0)
	{
		p = ft_vec3_sub(ft_vec3_kmult(2.0,
					ft_vec3(ft_rand48(), ft_rand48(), ft_rand48())),
				ft_vec3(1.0, 1.0, 1.0));
	}
	return (p);
}

int			ft_lambertian_sc(t_intersect *in, t_col3 *att)
{
	t_vec3	target;

	in->ray.start = in->p;
	target = ft_vec3_sum(ft_vec3_sum(in->p, in->n), ft_random_unit());
	*att = ft_col3_sum(*att, in->current->material.diffuse);
	in->ray.dir = ft_vec3_sub(target, in->p);
	return (1);
}

int			ft_metal_sc(t_intersect *in, t_col3 *att)
{
	t_vec3	reflected;

	in->ray.start = in->p;
	reflected = ft_reflect(ft_vec3_normalized(in->ray.dir), in->n);
	*att = in->current->material.diffuse;
	in->ray.dir = reflected;
	return (ft_vec3_dot(reflected, in->n) > 0);
}

float	ft_schlick(float cosine, float ref_idx)
{
	float ro = (1.0 - ref_idx) / (1.0 + ref_idx);
	ro = ro * ro;
	return (ro + (1.0 - ro) * pow((1.0 - cosine), 5.0));
}

int			ft_dielectric_sc(t_intersect *in, t_col3 *att, float ref_idx)
{
	t_vec3 reflected;
	t_vec3 refracted;
	t_vec3 out_n;
	float ni_over_nt;
	float  cosine;
	float	reflect_prob;

	*att = (t_col3){1.0, 1.0, 1.0};
	in->ray.start = in->p;    
	reflected = ft_reflect(in->ray.dir, in->n);
	if ((in->ray.dir.x * in->n.x + in->ray.dir.y * in->n.y + in->ray.dir.z * in->n.z) > 0.001)
	{
		out_n = (t_vec3){-in->n.x, -in->n.y, -in->n.z};
		ni_over_nt = ref_idx;
		cosine = ref_idx * ft_vec3_dot(in->ray.dir, in->n) * 1.0 / ft_vec3_norm(in->ray.dir);
	}
	else
	{
		out_n = (t_vec3){in->n.x, in->n.y, in->n.z};
		ni_over_nt = 1.0 / ref_idx;
		cosine = -ft_vec3_dot(in->ray.dir, in->n) * 1.0 / ft_vec3_norm(in->ray.dir);
	}
	if (ft_refract(in->ray.dir, out_n, ni_over_nt, &refracted))
		reflect_prob = ft_schlick(cosine, ref_idx);
	else
	{
		reflect_prob = 1.0;
		//in->ray.dir = reflected;
	}
	if (ft_rand48() < reflect_prob)
		in->ray.dir = reflected;
	else
		in->ray.dir = refracted;
	return (1);
}

t_col3		ft_path_trace(t_scene *s, t_intersect *in, int depth)
{
	t_col3		c;

	c = (t_col3){0.0, 0.0, 0.0};
	in->t = INFINITY;
	if (!ft_scene_intersect(s, in))
		return (ft_background_color(&in->ray));
	if (depth < MAX_DEPTH)
	{
		if (in->current->material.refraction > 0.0)
		{
			if (ft_dielectric_sc(in, &c, in->current->material.refraction))
				return (ft_col3_mult(c, ft_path_trace(s, in, depth + 1)));
		}
		else if (in->current->material.reflection > 0.0)
		{
			if (ft_metal_sc(in, &c))
				return (ft_col3_mult(c, ft_path_trace(s, in, depth + 1)));
		}
		else if (ft_lambertian_sc(in, &c))
			return (ft_col3_mult(c, ft_path_trace(s, in, depth + 1)));
	}
	return (c);
}
