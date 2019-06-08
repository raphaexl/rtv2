/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:40:26 by ebatchas          #+#    #+#             */
/*   Updated: 2019/06/08 21:40:20 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

float	ft_perlin_noise(t_perlin *pr, t_vec3 p)
{
	float		u;
	float		v;
	float		w;
	int			i;
	int			j;
	int			k;
	int			di, dj, dk;
	t_vec3		c[2][2][2];

	u = p.x - floor(p.x);
	v = p.y - floor(p.y);
	w = p.z - floor(p.z);
	i = floor(p.x);
	j = floor(p.y);
	k = floor(p.z);
	ft_perlin_generate(pr->ranvec);
	ft_perlin_generate_perm(pr->perm_x);
	ft_perlin_generate_perm(pr->perm_y);
	ft_perlin_generate_perm(pr->perm_z);
	di = -1;
	while (++di < 2)
	{
		dj = -1;
		while (++dj < 2)
		{
			dk = -1;
			while (++dk < 2)
			{
				c[di][dj][dk] = pr->ranvec[pr->perm_x[(i + di) & 255] ^
				   	pr->perm_y[(j + dj) & 255] ^ pr->perm_z[(k + dk) & 255]];
			}
		}
	}
	return (ft_perlin_interp(c, u, v, w));
}


void ft_perlin_generate(t_vec3 *p)
{
	int		i;

	i = 0;
	while (i < 256)
		p[i] = ft_vec3_normalized(ft_vec3(-1.0 + 2.0 * ft_rand48(),
					-1.0 + 2.0 * ft_rand48(), -1.0 + 2.0 * ft_rand48()));
}

void	ft_perlin_permute(int *p, int n)
{
	int		i;
	int		target;
	int		tmp;

	i = n;
	while (--i >= 0)
	{
		target = (int)(ft_rand48() * (i + 1));
		tmp = p[i];
		p[i] = p[target];
		p[target] = tmp;
	}
}

void	ft_perlin_generate_perm(int *p)
{
	int		i;

	i = -1;
	while (++i < 256)
		p[i] = i;
	ft_perlin_permute(p, 256);
}

void	ft_perlin_init(t_perlin *p)
{
	if (!(p->ranvec = (t_vec3 *)malloc(sizeof(t_vec3) * 256)))
		ft_print_error("Perlin : malloc error !");
	if (!(p->perm_x = (int *)malloc(sizeof(int) * 256)))
		ft_print_error("Perlin : malloc error !");
	if (!(p->perm_y = (int *)malloc(sizeof(int) * 256)))
		ft_print_error("Perlin : malloc error !");
	if (!(p->perm_z = (int *)malloc(sizeof(int) * 256)))
		ft_print_error("Perlin : malloc error !");
}

float	ft_perlin_interp(t_vec3 c[2][2][2], float u, float v, float w)
{
	float	uu;
	float	vv;
	float	ww;
	float	accum;
	int		i, j, k;

	uu = u * u * (3.0 - 2.0 * u);
	vv = v * v * (3.0 - 2.0 * v);
	ww = w * w * (3.0 - 2.0 * w);
	accum = 0.0;
	i = -1;
	while (++i < 2)
	{
		j = -1;
		while (++j < 2)
		{
			k = -1;
			while (++k < 2)
			{
				accum += (i * uu + (1 - i) * (1 - uu))
					* (j * vv + (1 - j) * (1 - vv))
					* (k * ww + (1 - k) * (1 - ww)) * ft_vec3_dot(c[i][j][k],\
							 ft_vec3(u - i, v - j, w - k));
			}
		}
	}
	return (accum);
}

void	ft_perlin_clean(t_perlin *p)
{
	free(p->ranvec);
	free(p->perm_x);
	free(p->perm_y);
	free(p->perm_z);
}
