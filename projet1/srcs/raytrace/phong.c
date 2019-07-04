/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:55:35 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/02 19:54:03 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

static t_col3	ft_ambient_light(t_col3 *diffuse, t_col3 *ambiant)
{
	t_col3		c;

	c.red = ambiant->red * diffuse->red;
	c.green = ambiant->green * diffuse->green;
	c.blue = ambiant->blue * diffuse->blue;
	return (c);
}

static t_col3	ft_diffuse_light(t_col3 *intens, t_col3 *diff, float lamb)
{
	t_col3	c;

	c.red = lamb * intens->red * diff->red * (1.0 / M_PI);
	c.green = lamb * intens->green * diff->green * (1.0 / M_PI);
	c.blue = lamb * intens->blue * diff->blue * (1.0 / M_PI);
	return (c);
}

static t_col3	ft_phong_shading(t_intersect *in, t_material *m, t_col3 *ints)
{
	float	reflect;
	t_vec3	tp;
	t_vec3	phong_dir;
	float	phong_term;

	reflect = 2.0f * ft_vec3_dot(in->ray_light.dir, in->n);
	tp = ft_vec3_kmult(reflect, in->n);
	phong_dir = ft_vec3_sub(in->ray_light.dir, tp);
	phong_term = fmax(ft_vec3_dot(phong_dir, in->ray.dir), 0.0f);
	phong_term = pow(phong_term, m->spec_pow) * m->albedo[1];
	return (ft_col3_mult(*ints, ft_col3_kmult(phong_term, m->specular)));
}

t_col3			ft_trace(t_intersect *in, t_material *m, t_light *l, t_col3 *a)
{
	t_col3	intensity;
	float	lambert;
	t_col3	c;

	c = (t_col3){0.0, 0.0, 0.0};
	intensity = ft_col3_kmult(l->intensity, l->color);
	c = ft_ambient_light(&m->diffuse, a);
//	lambert = ft_clamp(0, 1.0, ft_vec3_dot(in->ray_light.dir, in->n));
	//lambert = ft_vec3_dot(in->ray_light.dir, in->n);
	lambert = m->albedo[0] * ft_vec3_dot(in->n, in->ray_light.dir) ;/// M_PI;
	c = ft_col3_sum(c, ft_diffuse_light(&intensity, &m->diffuse, lambert));
//	if (m->type == SPECULAR)
		return (ft_col3_sum(c, ft_phong_shading(in, m, &intensity)));
//	return (c);
}
