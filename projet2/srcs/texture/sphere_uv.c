/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_uv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 10:27:58 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/20 12:27:49 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

void		ft_sphere_uv(t_sphere *s, t_vec3 n, t_vec3 p, t_uv *uv)
{
	float	phi;
	float	theta;

	(void)n;
	p = ft_vec3_kmult(1.0 / s->radius, p);
	phi = atan2(p.y, p.x);
	theta = asin(p.z);
	uv->u = 1.0 - (phi + M_PI) / (2.0 * M_PI);
	uv->v = (theta + M_PI / 2.0) / M_PI;
}
