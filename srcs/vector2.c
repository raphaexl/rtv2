/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 20:15:39 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/14 20:16:03 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vector.h"

float		ft_vec3_norm(t_vec3 a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

float		ft_vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	ft_vec3_normalized(t_vec3 a)
{
	t_vec3	res;
	float		k;

	k = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	k = 1.0 / k;
	res.x = a.x * k;
	res.y = a.y * k;
	res.z = a.z * k;
	return (res);
}

t_vec3	ft_reflect(t_vec3 v, t_vec3 n)
{
	t_vec3	tmp;

	tmp = ft_vec3_kmult(2.0 * ft_vec3_dot(v, n), n);
	return (ft_vec3_sub(v, tmp));
}

int			ft_refract(t_vec3 v, t_vec3 n, float ni_over_nt, t_vec3 *r)
{
	t_vec3	uv;
	t_vec3	tmp;
	float		dt;
	float		discr;

	uv = ft_vec3_normalized(v);
	dt = ft_vec3_dot(uv, n);
	discr = 1.0 - ni_over_nt * ni_over_nt * (1.0 - dt * dt);
	if (discr > 0.00001)
	{
		tmp = ft_vec3_kmult(ni_over_nt, ft_vec3_sub(uv,
					ft_vec3_kmult(dt, n)));
		*r = ft_vec3_sub(tmp, ft_vec3_kmult(sqrtf(discr), n));
		return (1);
	}
	else
		return (0);
}
