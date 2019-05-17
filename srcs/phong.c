/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 21:53:16 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/16 15:29:42 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

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

	c.red = lamb * intens->red * diff->red;
	c.green = lamb * intens->green * diff->green;
	c.blue = lamb * intens->blue * diff->blue;
	return (c);
}

static t_col3	ft_phong_shading(t_intersect *in, t_material *m, t_col3 *ints)
{
	float		reflect;
	t_vec3	tp;
	t_vec3	phong_dir;
	float		phong_term;

	reflect = 2.0f * ft_vec3_dot(in->ray_light.dir, in->n);
	tp = ft_vec3_kmult(reflect, in->n);
	phong_dir = ft_vec3_sub(in->ray_light.dir, tp);
	phong_term = fmax(ft_vec3_dot(phong_dir, in->ray.dir), 0.0f);
	phong_term = pow(phong_term, m->spec_pow);
	return (ft_col3_mult(*ints, ft_col3_kmult(phong_term, m->specular)));
}

t_col3			ft_trace(t_intersect *in, t_material *m, t_light *l, t_col3 *a)
{
	t_col3		intensity;
	float		lambert;
	t_col3		c;

	c = (t_col3){0.0, 0.0, 0.0};
	intensity = l->intensity;
	c = ft_ambient_light(&m->diffuse, a);
	lambert = ft_vec3_dot(in->ray_light.dir, in->n);
	c = ft_col3_sum(c, ft_diffuse_light(&intensity, &m->diffuse, lambert));
	return (ft_col3_sum(c, ft_phong_shading(in, m, &intensity)));
}
