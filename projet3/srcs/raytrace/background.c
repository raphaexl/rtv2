/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 09:32:44 by ebatchas          #+#    #+#             */
/*   Updated: 2019/09/18 15:29:50 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

static	int	ft_limit_int(int min, int max, int value)
{
	return (value < min ? min : value > max ? max : value);
}

t_col3		ft_background_image(t_scene *s, t_intersect *in, int index)
{
	(void)s;
	(void)in;
	(void)index;
/*	t_col3	c = (t_col3){0.01, 0.01, 0.01};
	t_texture	*tex;
	t_vec3		dir = in->ray.dir;
	ft_memcpy(tex, s->img[0], sizeof(t_texture));
	int			envmap_width = tex->w;
	int			envmap_height = tex->h;

	int a = MAX(0, MIN(envmap_width -1, (int)atan2(dir.z, dir.x)/(2*M_PI) + .5)*envmap_width);
	int b = MAX(0, MIN(envmap_height-1, (int)acos(dir.y)/M_PI*envmap_height));
	Uint32 col = tex->data[b * tex->w + a];
	c.red = (float)((col >> 16) & 0xFF) / 255.0;
	c.green = (float)((col >> 8) & 0xFF) / 255.0;
	c.blue = (float)(col & 0xFF) / 255.0;
	return (c);
//	return envmap[a+b*envmap_width];

	t_vec3	p;
	float	phi;
	float	theta;
	float	t = 1.0f;
	t_sphere sphere;
	t_uv	uv;

	sphere.radius = 10.0;
	sphere.radius2 = 10.0 * 10.0;
	ft_sphere_intersect(&s, &in->ray, &t);
	p = ft_vec3_sum(in->ray.start, ft_vec3_kmult(t, in->ray.dir));
	p = ft_vec3_kmult(1.0 / sphere.radius, p);
	phi = atan2(p.y, p.x);
	theta = asin(p.z);
	uv.u = 1.0 - (phi + M_PI) / (2.0 * M_PI);
	uv.v = (theta + M_PI / 2.0) / M_PI;
	c = ft_texture_image(s->img[index], uv.u, uv.v);
	return (c);*/


/*
 *
 *    Dont forget to try dcaling dir
 *
 */

	//return (s->bg_color);
	return (ft_read_cubemap(&s->cmap, in->ray));

/*	int			width;
	int			height;
	SDL_Color	color;

	return (s->bg_color);
	index = ft_limit_int(0, N_TEXTURES - 1, index);
	width = s->img[index]->w;
	height = s->img[index]->h;
	int		i = 0;//in->ray.x;
	int		j = 0;//in->ray.y;
	printf("i = %d\t j = %d\n", i, j);
	color = ft_sdl_color(s->img[index]->data[j * width + i]);
	return (ft_col3(color.r / 255, color.g / 255, color.b / 255));*/
}
