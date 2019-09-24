/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sobel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 14:12:38 by ebatchas          #+#    #+#             */
/*   Updated: 2019/09/24 11:37:43 by ebatchas         ###   ########.fr       */
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
	ft_process_filter(env, filter, 3, 1);
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
