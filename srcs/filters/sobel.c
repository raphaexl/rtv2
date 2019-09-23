/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sobel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 14:12:38 by ebatchas          #+#    #+#             */
/*   Updated: 2019/09/21 14:14:08 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

void		ft_sobel(t_env *env)
{
	double	*filter;

	if (!(filter = ft_memalloc(sizeof(double) * 9)))
		ft_print_error("error malloc");
	filter[0] = 0;
	filter[1] = 4;
	filter[2] = 0;
	filter[3] = 4;
	filter[4] = -16;
	filter[5] = 4;
	filter[6] = 0;
	filter[7] = 4;
	filter[8] = 0;
	ft_convolute(env, filter, 3, 1);
	free(filter);
}

void		ft_grey(t_env *e)
{
	int	i;
	int	j;

	i = -1;
	while (++i < W_W)
	{
		j = -1;
		while (++j < W_H)
			e->pixels[i + j * W_W] = ft_scale_convert_col3(ft_greyscale(
						ft_get_col3(ft_get_color(e->pixels[i + j * W_W]))),
					1).col;
	}
}

static void	ft_draw_border_pixl(Uint32 *pixels, int i, int j, Uint32 *tmp)
{
	t_pixel	col;

	col = ft_get_color(pixels[i +
			j * W_W]);
	if (col.r > 180 || col.g > 180 || col.b > 180)
		pixels[i + j * W_W] = 0x0;
	else
		pixels[i + j * W_W] = tmp[i + j * W_W];
}

void		ft_draw_borders(t_env *e)
{
	Uint32	*tmp;
	int		i;
	int		j;

	if (!(tmp = ft_memalloc(sizeof(Uint32) * W_W * W_H)))
		ft_print_error("error malloc");
	tmp = ft_memcpy(tmp, e->pixels,
			sizeof(Uint32) * W_W * W_H);
	ft_sobel(e);
	i = -1;
	while (++i < W_W)
	{
		j = -1;
		while (++j < W_H)
			ft_draw_border_pixl(e->pixels, i, j, tmp);
	}
	free(tmp);
}
