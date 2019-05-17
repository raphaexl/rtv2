/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 15:56:59 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/17 16:16:02 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static int	ft_min_ray(double s[4], float *t, int n)
{
	double	min;
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
		if (s[i] > 0.0001 && s[i] < min)
			min = s[i];
	}
	if (min < *t && min > 0.0001)
	{
		*t = min;
		return (n);
	}
	return (0);
}

t_object	*ft_torus_new(void)
{
	t_object	*new;

	if ((new = (t_object *)malloc(sizeof(*new))))
	{
		new->type = TORUS;
		new->name = "TORUS";
		new->pos = (t_vec3){0.0, 0.0, 0.0};
		new->translate = (t_vec3){0.0, 0.0, 0.0};
		new->rotate = (t_vec3){0.0, 0.0, 0.0};
		new->normal = (t_vec3){0.0, 0.0, 0.0};
		new->material = (t_material){{1.0, 1.0, 1.0}, {0, 0, 0}, 0, 0, 0, 0};
		new->radius = 1.0;
		new->angle = 0.5;
		new->next = NULL;
	}
	else
		ft_print_error("malloc error");
	return (new);
}

int			ft_torus_compute(t_object *p, t_intersect *in)
{
	t_ray		r;

	r = in->ray;
	r.start = ft_rotate_vec3(r.start, p->rotate, -1);
	r.dir = ft_rotate_vec3(r.dir, p->rotate, -1);
	r.start = ft_translate_vec3(r.start, p->translate, -1);
	if (!ft_torus_intersect(p, &r, &in->t))
		return (0);
	in->current = p;
	in->p = ft_vec3_sum(r.start, ft_vec3_kmult(in->t, r.dir));
	in->n = ft_normal_torus(p, ft_vec3_sub(in->p, p->pos));
	in->p = ft_translate_vec3(in->p, p->translate, 0);
	in->p = ft_rotate_vec3(in->p, p->rotate, 0);
	in->n = ft_rotate_vec3(in->n, p->rotate, 0);
	return (1);
}

int			ft_torus_intersect(t_object *t, t_ray *r, float *min)
{
	t_vec3	dist;
	int		num;
	double	c[5], s[4];

	c[4] = pow(ft_vec3_dot(r->dir, r->dir), 2);
	dist = ft_vec3_sub(r->start, t->pos);
	c[3] = 4.0 * ft_vec3_dot(r->dir, r->dir) * ft_vec3_dot(dist, r->dir);
	c[2] = 2.0 * ft_vec3_dot(r->dir, r->dir) * (ft_vec3_dot(dist, dist) - 
			(t->radius * t->radius + t->angle * t->angle)) + 4.0 * pow(ft_vec3_dot(dist, r->dir), 2) +
		 4.0 * t->radius * t->radius * r->dir.y * r->dir.y;
	c[1] = 4.0 * (ft_vec3_dot(dist, dist) - (t->radius * t->radius + t->angle * t->angle))
		* ft_vec3_dot(dist, r->dir) + 8.0 * (t->radius * t->radius) * dist.y * r->dir.y;
	c[0] = pow(ft_vec3_dot(dist, dist) - (t->radius * t->radius + t->angle * t->angle), 2)
		- 4.0 * (t->radius * t->radius) * (t->angle * t->angle - dist.y * dist.y);
	num = ft_solve_quartic(c, s);
	if (num == 0)
		return (0);
	else if ((num == 1) && (s[0] > 0.0001f) && (s[0] < *min))
	{
		*min = s[0];
		return (1);
	}
	else
		return (ft_min_ray(s, min, num));
}
