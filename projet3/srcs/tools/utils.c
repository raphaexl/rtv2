/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:59:58 by ebatchas          #+#    #+#             */
/*   Updated: 2019/09/17 11:00:56 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

float	ft_modulo(float f)
{
	return (f - floor(f));
}

float	ft_clamp(float min, float max, float val)
{
	return (fmax(min, fmin(max, val)));
}

float	ft_rand48(void)
{
	static int	initialized = 0;

	if (!initialized)
	{
		initialized = 1;
		srand(time(NULL));
	}
	return ((float)(rand() % RAND_MAX) / ((float)(RAND_MAX + 1.0)));
}

int		ft_tab_len(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}



t_pixel		ft_scale_color(t_pixel c, double t)
{
	t_pixel	ret;

	ret.r = c.r * t;
	ret.g = c.g * t;
	ret.b = c.b * t;
	ret.col = ret.r * 0x10000 + ret.g * 0x100 + ret.b;
	return (ret);
}

t_pixel			ft_add_colors(t_pixel c1, t_pixel c2)
{
	t_pixel	ret;

	ret.r = c1.r + c2.r > 0xFF ? 0xFF : c1.r + c2.r;
	ret.g = c1.g + c2.g > 0xFF ? 0xFF : c1.g + c2.g;
	ret.b = c1.b + c2.b > 0xFF ? 0xFF : c1.b + c2.b;
	ret.col = ret.r * 0x10000 + ret.g * 0x100 + ret.b;
	return (ret);
}

t_pixel			ft_interpole_color(double t, t_pixel c1, t_pixel c2)
{
	t_pixel	ip;

	ip.r = c1.r + (c2.r - c1.r) * t;
	ip.g = c1.g + (c2.g - c1.g) * t;
	ip.b = c1.b + (c2.b - c1.b) * t;
	ip.col = ip.r * 0x10000 + ip.g * 0x100 + ip.b;
	return (ip);
}

t_pixel		ft_get_color(int color)
{
	t_pixel  c;

	c.col = color;
	c.r = color / 0x10000;
	c.g = color / 0x100;
	c.b = color % 0x100;
	return (c);
}

void			ft_put_pixel(t_point p, t_pixel c, int *pixels, t_point size)
{
	pixels[p.x + p.y * size.x] = c.col;
}
