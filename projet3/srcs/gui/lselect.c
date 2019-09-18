/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lselect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 16:51:39 by ebatchas          #+#    #+#             */
/*   Updated: 2019/09/16 14:43:17 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

void	ft_no_light_select(t_lview *view)
{
	int		i;
	int		j;

	view->e.mes = ft_strdup("NONE");
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		view->v[i].e[j].mes = ft_strdup("0.00");
	}
}

void	ft_light_select1(t_lview *view, t_light *l)
{
	if (!ft_strcmp("DIRECTIONNAL", view->e.mes) ||
			(!ft_strcmp("DISTANT", view->e.mes)))
		l->type = DISTANT_LIGHT;
	else if (!ft_strcmp("SPHERICAL", view->e.mes) ||
			(!ft_strcmp("POINT", view->e.mes)))
		l->type = POINT_LIGHT;
	else
		l->type = POINT_LIGHT;
	if (l->type == POINT_LIGHT)
		view->e.mes = ft_strdup("POINT"); 
		else
			view->e.mes = ft_strdup("DISTANT"); 
		view->v[0].e[0].mes = ft_itoaf(l->u.def.pos.x, 2);
		view->v[0].e[1].mes = ft_itoaf(l->u.def.pos.y, 2);
		view->v[0].e[2].mes = ft_itoaf(l->u.def.pos.z, 2);
		view->v[1].e[0].mes = ft_itoaf(l->u.direct.dir.x, 2);
		view->v[1].e[1].mes = ft_itoaf(l->u.direct.dir.y, 2);
		view->v[1].e[2].mes = ft_itoaf(l->u.direct.dir.z, 2);
		view->v[2].e[0].mes = ft_itoaf(l->diffuse.red, 2);
		view->v[2].e[1].mes = ft_itoaf(l->diffuse.green, 2);
		view->v[2].e[2].mes = ft_itoaf(l->diffuse.blue, 2);
}

void	ft_lview_light(t_lview *view, t_light *l)
{
	if (!l)
		ft_no_light_select(view);
	else
	{
		ft_light_select1(view, l);
	}
}
