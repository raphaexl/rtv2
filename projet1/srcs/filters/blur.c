/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blur.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 22:37:37 by ebatchas          #+#    #+#             */
/*   Updated: 2019/06/14 16:49:05 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

void		ft_filter_blur(t_filter *f)
{
	f->filter[0][0] = 0.0;
	f->filter[0][1] = 0.2;
	f->filter[0][2] = 0.0;
	
	f->filter[1][0] = 0.2;
	f->filter[1][1] = 0.2;
	f->filter[1][2] = 0.2;

	f->filter[2][0] = 0.0;
	f->filter[2][1] = 0.2;
	f->filter[2][2] = 0.0;
	f->factor = 1.0;
	f->bias = 0.0;
	f->h = 3;
	f->w = 3;
}

void		ft_filter_blur2(t_filter *f)
{
	f->filter[0][0] = 0.0;
	f->filter[0][1] = 0.0;
	f->filter[0][2] = 1.0;
	f->filter[0][3] = 1.0;
	f->filter[0][4] = 1.0;
	
	f->filter[1][0] = 0.2;
	f->filter[1][1] = 0.2;
	f->filter[1][2] = 0.2;
	f->filter[1][3] = 0.2;
	f->filter[1][4] = 0.2;

	f->filter[2][0] = 1.0;
	f->filter[2][1] = 1.0;
	f->filter[2][2] = 1.0;
	f->filter[2][3] = 1.0;
	f->filter[2][4] = 1.0;
	
	f->filter[3][0] = 0.0;
	f->filter[3][1] = 1.0;
	f->filter[3][2] = 1.0;
	f->filter[3][3] = 1.0;
	f->filter[3][4] = 0.0;

	f->filter[4][0] = 0.0;
	f->filter[4][1] = 0.0;
	f->filter[4][2] = 1.0;
	f->filter[4][3] = 0.0;
	f->filter[4][4] = 0.0;
	f->factor = 1.0 / 13.0;
	f->bias = 0.0;
	f->h = 5;
	f->w = 5;
}

void		ft_filter_gaussian_blur(t_filter *f)
{
	f->filter[0][0] = 0.077847;
	f->filter[0][1] = 0.123317;
	f->filter[0][2] = 0.077847;
	
	f->filter[1][0] = 0.123317;
	f->filter[1][1] = 0.195346;
	f->filter[1][2] = 0.123317;

	f->filter[2][0] = 0.077847;
	f->filter[2][1] = 0.123317;
	f->filter[2][2] = 0.077847;
	f->factor = 1.0;
	f->bias = 0.0;
	f->h = 3;
	f->w = 3;
}

void		ft_filter_gaussian_blur2(t_filter *f)
{
	f->filter[0][0] = 1.0;
	f->filter[0][1] = 4.0;
	f->filter[0][2] = 6.0;
	f->filter[0][3] = 4.0;
	f->filter[0][4] = 1.0;
	
	f->filter[1][0] = 4.0;
	f->filter[1][1] = 16.0;
	f->filter[1][2] = 24.0;
	f->filter[1][3] = 16.0;
	f->filter[1][4] = 16.0;

	f->filter[2][0] = 6.0;
	f->filter[2][1] = 24.0;
	f->filter[2][2] = 36.0;
	f->filter[2][3] = 24.0;
	f->filter[2][4] = 6.0;
	
	f->filter[3][0] = 4.0;
	f->filter[3][1] = 16.0;
	f->filter[3][2] = 24.0;
	f->filter[3][3] = 16.0;
	f->filter[3][4] = 4.0;

	f->filter[4][0] = 1.0;
	f->filter[4][1] = 4.0;
	f->filter[4][2] = 6.0;
	f->filter[4][3] = 4.0;
	f->filter[4][4] = 1.0;
	f->factor = 1.0 / 256.0;
	f->bias = 0.0;
	f->h = 5;
	f->w = 5;
}
void		ft_filter_motion_blur(t_filter *f)
{
	int		i;
	int		j;

	j = -1;
	while (++j < 9)
	{
		i = -1;
		while (++i < 9)
			f->filter[j][i] = i == j ? 1.0 : 0.0;
	}
	f->factor = 1.0 / 9.0;
	f->bias = 0.0;
	f->h = 9;
	f->w = 9;
}

