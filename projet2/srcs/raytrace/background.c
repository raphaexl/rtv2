/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 09:32:44 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/27 09:39:31 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

static	int	ft_limit_int(int min, int max, int value)
{
	return (value < min ? min : value > max ? max : value);
}

t_col3		ft_background_image(t_scene *s, t_intersect *in, int index)
{
	int			width;
	int			height;
	SDL_Color	color;

	index = ft_limit_int(0, N_TEXTURES - 1, index);
	width = s->img[index]->w;
	height = s->img[index]->h;
	int		i = (int)in->p.x;
	int		j = (int)in->p.y;
	printf("i = %d\t j = %d\n", i, j);
	color = ft_sdl_color(s->img[index]->data[j * width + i]);
	return (ft_col3(color.r / 255, color.g / 255, color.b / 255));
}
