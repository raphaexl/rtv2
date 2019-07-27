/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lapply.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 17:45:52 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/13 19:19:16 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

void	ft_light_aplly1(t_lview *view, t_light **l)
{
	static int		init = 0;	

	if (!init && (init = 1))
		ft_lview_light(view, *l);
	else
	{
	if ((*l)->type == POINT)
	{
		view->e.mes = ft_strdup("POINT");
		(*l)->pos.x = ft_atof(view->v[0].e[0].mes);
		(*l)->pos.y = ft_atof(view->v[0].e[1].mes);
		(*l)->pos.z = ft_atof(view->v[0].e[2].mes);
	}
	else
	{
		view->e.mes = ft_strdup("DISTANT");
		(*l)->dir.x = ft_atof(view->v[1].e[0].mes);
		(*l)->dir.y = ft_atof(view->v[1].e[1].mes);
		(*l)->dir.z = ft_atof(view->v[1].e[2].mes);
	}
	(*l)->color.red = ft_atof(view->v[2].e[0].mes);
	(*l)->color.green = ft_atof(view->v[2].e[1].mes);
	(*l)->color.blue = ft_atof(view->v[2].e[2].mes);
	}
}

void	ft_lview_apply(t_lview *view, t_light **l)
{
	if (!*l)
		return ;
	else
		ft_light_aplly1(view, l);
}
