/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turbulence.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:40:40 by ebatchas          #+#    #+#             */
/*   Updated: 2019/09/18 15:59:25 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/rt.h"
/*
t_vec3	ft_normal_bump(t_hit *hit)
{
	t_vec3	pert;
	t_vec3	rand_ang;
	double		angle;
	t_vec3	normal;

	if (hit->current->material.pert == RIPPLES)
		angle = sin(ft_vec3_norm(hit->p));
	else if (hit->current->material.pert == WAVES)
		angle = sin(hit->p.x);
	else
		angle = 0.0;
	pert = ft_vec3_normalized(ft_rotate_axis(hit->n,
				ft_vec3_normalized(ft_vec3_cross(hit->n, hit->p)), angle * 0.2));
	if (hit->current->material.pert == NOISE)
	{
		ft_putendl("Is Called");
		angle = 0.12;
		rand_ang.x = (double)(rand() % 100) / 100 * angle - angle / 2;
		rand_ang.y = (double)(rand() % 100) / 100 * angle - angle / 2;
		rand_ang.z = (double)(rand() % 100) / 100 * angle - angle / 2;
		pert = ft_rotate_vec3(pert, rand_ang, 0);
	}
	normal = ft_vec3_normalized(pert);	
	return (normal);
}
*/

t_vec3	ft_normal_bump(t_hit *hit)
{
	t_vec3	noise;
	t_vec3	normal;
	float	bump;
	double sc = 10.0;

	bump = hit->current->material.bump;
	normal = hit->n;
   	noise.x = ft_perlin(sc * (double)hit->p.x, sc * (double)hit->p.y,sc * (double)hit->p.z);
	noise.y = ft_perlin(sc * (double)hit->p.y, sc * (double)hit->p.z,sc * (double)hit->p.x);
	noise.z = ft_perlin(sc * (double)hit->p.z, sc * (double)hit->p.x,sc * (double)hit->p.y);
	normal.x = (1.0f - bump) * normal.x + bump * noise.x;
	normal.y = (1.0f - bump) * normal.y + bump * noise.y;
	normal.z = (1.0f - bump) * normal.z + bump * noise.z;
	normal = ft_vec3_normalized(normal);
	return (normal);
}

t_col3		ft_perlin_color(t_hit *hit)
{
	double	noisecoef;
	int		i;
	t_col3	c1;
	t_col3	c2;	

	noisecoef = 0;
	i = 1;
	while (i < 5)
	{
		noisecoef += (1.0f / i) * fabs((ft_perlin(i * 10 * hit->p.x,
						i * 10 * hit->p.y,
						i * 10 * hit->p.z)));
		i++;
	}
	c1 = hit->current->material.diffuse;
	c2 = hit->current->material.diffuse2;
	return (ft_col3_sum(ft_col3_kmult(noisecoef, c1), ft_col3_kmult(1.0 - noisecoef, c2)));
}


t_col3		ft_marble_color(t_hit *hit)
{
	double	noisecoef;
	int		i;
	t_col3	c1;
	t_col3	c2;	

	noisecoef = 0;
	i = 1;
	while (i < 5)
	{
		noisecoef += (1.0f / i) * fabs((ft_perlin(i * 10 * hit->p.x,
						i * 10 * hit->p.y,
						i * 10 * hit->p.z)));
		i++;
	}
	noisecoef = 0.5f * sin((hit->p.x + hit->p.y) *
			5.0f + noisecoef) + 0.5f;
	c1 = hit->current->material.diffuse;
	c2 = hit->current->material.diffuse2;
	return (ft_col3_sum(ft_col3_kmult(noisecoef, c1), ft_col3_kmult(1.0 - noisecoef, c2)));
}

float	ft_turb(t_vec3 p, int depth)
{
	float 	accum;
	t_vec3	temp_p;
	float	weight;
	int		i;

	weight = 1.0;
	i = 0;
	accum = 0.0;
	temp_p = p;
	while (++i < depth)
	{
		accum += weight * ft_perlin(temp_p.x, temp_p.y, temp_p.z);
		weight *= 0.5;
		temp_p = ft_vec3_kmult(2.0, temp_p);
	}
	return (fabs(accum));
}

t_col3		ft_perlin_turbulance1(t_hit *hit)
{
	t_col3	c1;
	//t_col3	c2;
	float    t;

	/*c1 = ft_col3_kmult(0.5, hit->current->material.diffuse);
	  t =  1.0 + ft_turb(ft_vec3_kmult(10.0, hit->p), 7);//hit->current->material.diffuse2));
	  return (ft_col3_kmult(t, c1));*/	
	/*	c1 =  hit->current->material.diffuse;
		t =  ft_turb(ft_vec3_kmult(10.0, hit->p), 7);//hit->current->material.diffuse2));
		return (ft_col3_kmult(t, c1));	*/
	c1 = ft_col3_kmult(0.5, hit->current->material.diffuse);
	t =  1.0 + sin(0.5 * hit->p.x + 0.2 * hit->p.y + 10.0 * hit->p.z) + 10.0 * ft_turb(hit->p, 7);//hit->current->material.diffuse2));
	return (ft_col3_kmult(t, c1));
	/*	double noisecoef = 10.0 * cos(hit->p.x + ft_perlin(hit->p.x, hit->p.y, hit->p.z));
		c2 = hit->current->material.diffuse;
		c1 = hit->current->material.diffuse2;
		return (ft_col3_sum(ft_col3_kmult(noisecoef, c1), ft_col3_kmult(1.0 - noisecoef, c2)));*/
}

t_col3		ft_perlin_noise(t_hit *hit)
{
	t_col3	c1;
	t_col3	c2;

	if (hit->current->material.pert == PERLIN)
		return (ft_perlin_color(hit));
	else if (hit->current->material.pert == MARBLE)
	{
		return (ft_perlin_turbulance1(hit));
		return (ft_marble_color(hit));
	}
	c1 = hit->current->material.diffuse;
	c2 = hit->current->material.diffuse2;
	if (hit->current->material.pert == CHESS &&
			(((sin(hit->p.x) > 0 ? 1 : -1) *
			  (sin(hit->p.z) > 0 ? 1 : -1)) > 0))
		return (c1);
	return (c2);
}
