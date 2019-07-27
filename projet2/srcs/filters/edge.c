/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 22:38:31 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/16 15:48:30 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

void		ft_filter_edge(t_filter *f)
{
	f->filter[0][0] = -1.0;
	f->filter[0][1] = -1.0;
	f->filter[0][2] = -1.0;
	
	f->filter[1][0] = -1.0;
	f->filter[1][1] = 8.0;
	f->filter[1][2] = -1.0;

	f->filter[2][0] = -1.0;
	f->filter[2][1] = -1.0;
	f->filter[2][2] = -1.0;
	f->factor = 1.0;
	f->bias = 0.0;
	f->h = 3;
	f->w = 3;
}

void		ft_filter_edge2(t_filter *f)
{
	f->filter[0][0] = 0.0;
	f->filter[0][1] = 0.0;
	f->filter[0][2] = -1.0;
	f->filter[0][3] = 0.0;
	f->filter[0][4] = 0.0;
	
	f->filter[1][0] = 0.0;
	f->filter[1][1] = 0.0;
	f->filter[1][2] = -1.0;
	f->filter[1][3] = 0.0;
	f->filter[1][4] = 0.0;

	f->filter[2][0] = 0.0;
	f->filter[2][1] = 0.0;
	f->filter[2][2] = 4.0;
	f->filter[2][3] = 0.0;
	f->filter[2][4] = 0.0;
	
	f->filter[3][0] = 0.0;
	f->filter[3][1] = 0.0;
	f->filter[3][2] = -1.0;
	f->filter[3][3] = 0.0;
	f->filter[3][4] = 0.0;

	f->filter[4][0] = 0.0;
	f->filter[4][1] = 0.0;
	f->filter[4][2] = -1.0;
	f->filter[4][3] = 0.0;
	f->filter[4][4] = 0.0;
	f->factor = 1.0;
	f->bias = 0.0;
	f->h = 5;
	f->w = 5;
}

void		ft_filter_edge3(t_filter *f)
{
	f->filter[0][0] = -1.0;
	f->filter[0][1] = 0.0;
	f->filter[0][2] = 0.0;
	f->filter[0][3] = 0.0;
	f->filter[0][4] = 0.0;
	
	f->filter[1][0] = 0.0;
	f->filter[1][1] = -2.0;
	f->filter[1][2] = 0.0;
	f->filter[1][3] = 0.0;
	f->filter[1][4] = 0.0;

	f->filter[2][0] = 0.0;
	f->filter[2][1] = 0.0;
	f->filter[2][2] = 6.0;
	f->filter[2][3] = 0.0;
	f->filter[2][4] = 0.0;
	
	f->filter[3][0] = 0.0;
	f->filter[3][1] = 0.0;
	f->filter[3][2] = 0.0;
	f->filter[3][3] = -2.0;
	f->filter[3][4] = 0.0;

	f->filter[4][0] = 0.0;
	f->filter[4][1] = 0.0;
	f->filter[4][2] = 0.0;
	f->filter[4][3] = 0.0;
	f->filter[4][4] = -1.0;
	f->factor = 1.0;
	f->bias = 0.0;
	f->h = 5;
	f->w = 5;
}

void		ft_filter_edge4(t_filter *f)
{
	f->filter[0][0] = 0.0;
	f->filter[0][1] = 0.0;
	f->filter[0][2] = -1.0;
	f->filter[0][3] = 0.0;
	f->filter[0][4] = 0.0;
	
	f->filter[1][0] = 0.0;
	f->filter[1][1] = 0.0;
	f->filter[1][2] = -1.0;
	f->filter[1][3] = 0.0;
	f->filter[1][4] = 0.0;

	f->filter[2][0] = 0.0;
	f->filter[2][1] = 0.0;
	f->filter[2][2] = 2.0;
	f->filter[2][3] = 0.0;
	f->filter[2][4] = 0.0;
	
	f->filter[3][0] = 0.0;
	f->filter[3][1] = 0.0;
	f->filter[3][2] = 0.0;
	f->filter[3][3] = 0.0;
	f->filter[3][4] = 0.0;

	f->filter[4][0] = 0.0;
	f->filter[4][1] = 0.0;
	f->filter[4][2] = 0.0;
	f->filter[4][3] = 0.0;
	f->filter[4][4] = 0.0;
	f->factor = 1.0;
	f->bias = 0.0;
	f->h = 5;
	f->w = 5;
}


