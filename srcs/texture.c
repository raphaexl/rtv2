/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 17:46:00 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/17 20:24:58 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_texture	*ft_texture_new(char *img)
{
	t_texture	*new;

	if (!(new = (t_texture *)malloc(sizeof(t_texture))))
		ft_print_error("Error malloc !");
	if (!(new->data = ft_load_pixels(img, &new->w, &new->h)))
		ft_print_error("Error loading texture image !");
	return (new);
}

void	ft_sphere_uv(t_vec3 p, float *u, float *v)
{
	float 	phi;
	float	theta;

	phi = atan2(p.y, p.x);
	theta = asin(p.z);
	*u = 1.0 - (phi + M_PI) / (2.0 * M_PI);
	*v = (theta + M_PI / 2.0) / M_PI;
}

void	ft_torus_uv(t_vec3 p, float r, float *u, float *v)
{
	float	theta;

	theta = atan2(p.y, p.x);
	*u = 0.5 + theta / 2.0 * M_PI;
	theta = atan2(p.z, sqrt(p.x * p.x + p.y * p.y) - r);
	*v = theta / (2.0 * M_PI + 0.5);
}

t_col3	ft_texture_image(t_texture *t, float u, float v)
{
	int		i;
	int		j;
	t_col3	c;
	Uint32	col;

	i = u * t->w;
	j = (1.0 - v) * t->h - 0.001;
	if (i < 0)
		i = 0;
	if (j < 0)
		j = 0;
	if (i > t->w - 1)
		i = t->w - 1;
	if (j > t->h - 1)
		j = t->h - 1;
	col = t->data[j * t->w + i];
	c.red = (float)((col >> 16) & 0xFF) / 255.0;
	c.green = (float)((col >> 8) & 0xFF) / 255.0;
	c.blue = (float)(col & 0xFF) / 255.0;
	return (c);
}

void	ft_texture_clean(t_texture **t)
{
	free((*t)->data);
	free(*t);
}
