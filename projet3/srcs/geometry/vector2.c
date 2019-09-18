/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:00:25 by ebatchas          #+#    #+#             */
/*   Updated: 2019/09/18 15:20:45 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

float	ft_vec3_norm(t_vec3 a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

float	ft_vec3_norm2(t_vec3 a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}


float	ft_vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	ft_vec3_normalized(t_vec3 a)
{
	t_vec3	res;
	float	k;

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
/*
int 	ft_refract(t_vec3 v, t_vec3 n, float ior, t_vec3 *r)
{
	t_vec3	tmp;
	float	cosi, etai, etat, eta;
	float	k;

	etai = 1.0;
	etat = ior;
	cosi = ft_clamp(-1.0, 1.0, ft_vec3_dot(v, n));
	if (cosi > 0.0f)
		cosi = -cosi;
	else
	{
	//swap
	float sp = etai;
	etai = etat;
	etat = sp;
	n = ft_vec3_kmult(-1.0, n);
	}
	eta = etai / etat;
	k = 1.0 - eta * eta * (1.0 - cosi * cosi);
	if (k < 0.0f)
		return (0);
	tmp = ft_vec3_kmult(eta, v);
	*r = ft_vec3_sum(tmp, ft_vec3_kmult(eta * cosi - sqrtf(k), n));
	return (1);
}*/

void		ft_fresnel(t_vec3 v, t_vec3 n, float ior, float *kr)
{
	float	cosi, etai, etat;
	float	sint;

	etai = 1.0f;
	etat = ior;
	cosi = ft_clamp(-1.0, 1.0, ft_vec3_dot(v, n));
	if (cosi > 0.0f)
	{
	float sp = etai;
	etai = etat;
	etat = sp;
	n = ft_vec3_kmult(-1.0, n);
	}
	sint = etai / etat * sqrtf(fmax(0.0f, 1.0 - cosi * cosi));
	if (sint >= 1.0f)
		*kr = 1.0f;	
	else
	{
	float cost = sqrtf(fmax(0.0f, 1));
	cosi = fabs(cosi);
	float	rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
	float	rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
	*kr = (rs * rs + rp * rp) / 2.0;
	}
}


int		ft_refract(t_vec3 v, t_vec3 n, float ni_over_nt, t_vec3 *r)
{
	t_vec3	uv;
	t_vec3	tmp;
	float	dt;
	float	discr;

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
