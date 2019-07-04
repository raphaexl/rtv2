/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sharpen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 22:39:31 by ebatchas          #+#    #+#             */
/*   Updated: 2019/06/14 16:49:47 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

void		ft_filter_sharpen(t_filter *f)
{
	f->filter[0][0] = -1.0;
	f->filter[0][1] = -1.0;
	f->filter[0][2] = -1.0;
	
	f->filter[1][0] = -1.0;
	f->filter[1][1] = 9.0;
	f->filter[1][2] = -1.0;

	f->filter[2][0] = -1.0;
	f->filter[2][1] = -1.0;
	f->filter[2][2] = -1.0;
	f->factor = 1.0;
	f->bias = 0.0;
	f->h = 3;
	f->w = 3;
}

void		ft_filter_sharpen2(t_filter *f)
{
	f->filter[0][0] = 1.0;
	f->filter[0][1] = 1.0;
	f->filter[0][2] = 1.0;
	
	f->filter[1][0] = 1.0;
	f->filter[1][1] = -7.0;
	f->filter[1][2] = 1.0;

	f->filter[2][0] = 1.0;
	f->filter[2][1] = 1.0;
	f->filter[2][2] = 1.0;
	f->factor = 1.0;
	f->bias = 0.0;
	f->h = 3;
	f->w = 3;
}

void		ft_filter_sharpen3(t_filter *f)
{
	f->filter[0][0] = -1.0;
	f->filter[0][1] = -1.0;
	f->filter[0][2] = -1.0;
	f->filter[0][3] = -1.0;
	f->filter[0][4] = -1.0;
	
	f->filter[1][0] = -1.0;
	f->filter[1][1] = 2.0;
	f->filter[1][2] = 2.0;
	f->filter[1][3] = 2.0;
	f->filter[1][4] = -1.0;

	f->filter[2][0] = -1.0;
	f->filter[2][1] = 2.0;
	f->filter[2][2] = 8.0;
	f->filter[2][3] = 2.0;
	f->filter[2][4] = -1.0;
	f->filter[3][0] = -1.0;
	f->filter[3][0] = 2.0;
	f->filter[3][0] = 2.0;
	f->filter[3][1] = 2.0;
	f->filter[3][2] = -1.0;
	
	f->filter[4][0] = -1.0;
	f->filter[4][1] = -1.0;
	f->filter[4][2] = -1.0;
	f->filter[4][3] = -1.0;
	f->filter[4][4] = -1.0;

	f->factor = 1.0 / 8.0;
	f->bias = 0.0;
	f->h = 5;
	f->w = 5;
}

