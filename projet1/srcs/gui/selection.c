/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 09:42:08 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/02 20:45:30 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

void	ft_no_object_select(t_inspector *ins)
{
	int		i;
	int		j;

	i = -1;
	while (++i < N_PROPERTIES)
	{
		j = -1;
		while (++j < 3)
			ins->v3[i].e[j].mes = ft_strdup("0.00");
	}
	i = -1;
	while (++i < N_VIEW1)
		ins->v1[i].e.mes = ft_strdup("0.00");
	i = -1;
	while (++i < N_VIEW4)
	{
		j = -1;
		while (++j < 3)
			ins->v4[i].e[j].mes = ft_strdup("0.00");
	}
}

void	ft_object_select1(t_inspector *ins, t_object *o)
{
	ins->v3[0].e[0].mes = ft_itoaf(o->translate.x, 2);
	ins->v3[0].e[1].mes = ft_itoaf(o->translate.y, 2);
	ins->v3[0].e[2].mes = ft_itoaf(o->translate.z, 2);
	ins->v3[1].e[0].mes = ft_itoaf(o->rotate.x, 2);
	ins->v3[1].e[1].mes = ft_itoaf(o->rotate.y, 2);
	ins->v3[1].e[2].mes = ft_itoaf(o->rotate.z, 2);
	ins->v3[2].e[0].mes = ft_itoaf(o->scale.x, 2);
	ins->v3[2].e[1].mes = ft_itoaf(o->scale.y, 2);
	ins->v3[2].e[2].mes = ft_itoaf(o->scale.z, 2);
	ins->v3[8].e[0].mes = ft_itoaf(o->material.diffuse.red, 2);
	ins->v3[8].e[1].mes = ft_itoaf(o->material.diffuse.green, 2);
	ins->v3[8].e[2].mes = ft_itoaf(o->material.diffuse.blue, 2);
	ins->v3[9].e[0].mes = ft_itoaf(o->material.specular.red, 2);
	ins->v3[9].e[1].mes = ft_itoaf(o->material.specular.green, 2);
	ins->v3[9].e[2].mes = ft_itoaf(o->material.specular.blue, 2);
	ins->v1[4].e.mes = ft_itoaf(o->material.spec_pow, 2);
	ins->v4[0].e[0].mes = ft_itoaf(o->material.albedo[0], 2);
	ins->v4[0].e[1].mes = ft_itoaf(o->material.albedo[1], 2);
	ins->v4[0].e[2].mes = ft_itoaf(o->material.albedo[2], 2);
	ins->v4[0].e[3].mes = ft_itoaf(o->material.albedo[3], 2);
}

int 	ft_object_selectv(t_inspector *ins, t_object *o)
{
	if (o->type == RING)
	{
		ins->v3[3].e[0].mes = ft_itoaf(o->e.ring.v.x, 2);
		ins->v3[3].e[1].mes = ft_itoaf(o->e.ring.v.y, 2);
		ins->v3[3].e[2].mes = ft_itoaf(o->e.ring.v.z, 2);
	}
	else if (o->type == CYLINDER)
	{
		ins->v3[3].e[0].mes = ft_itoaf(o->e.cylinder.v.x, 2);
		ins->v3[3].e[1].mes = ft_itoaf(o->e.cylinder.v.y, 2);
		ins->v3[3].e[2].mes = ft_itoaf(o->e.cylinder.v.z, 2);
	}
	else if (o->type == ELLIPSOID)
	{
		ins->v3[3].e[0].mes = ft_itoaf(o->e.ellipse.v.x, 2);
		ins->v3[3].e[1].mes = ft_itoaf(o->e.ellipse.v.y, 2);
		ins->v3[3].e[2].mes = ft_itoaf(o->e.ellipse.v.z, 2);
	}
	else if (o->type == PARABOLOID)
	{
		ins->v3[3].e[0].mes = ft_itoaf(o->e.parab.v.x, 2);
		ins->v3[3].e[1].mes = ft_itoaf(o->e.parab.v.y, 2);
		ins->v3[3].e[2].mes = ft_itoaf(o->e.parab.v.z, 2);
	}
	else
		return (0);
	return (1);
}

void	ft_object_select2(t_inspector *ins, t_object *o)
{
	if (o->type == PLANE)
	{
		ins->v3[3].e[0].mes = ft_itoaf(o->e.plane.normal.x, 2);
		ins->v3[3].e[1].mes = ft_itoaf(o->e.plane.normal.y, 2);
		ins->v3[3].e[2].mes = ft_itoaf(o->e.plane.normal.z, 2);
	}
	else if (o->type == DISK)
	{
		ins->v3[3].e[0].mes = ft_itoaf(o->e.disk.normal.x, 2);
		ins->v3[3].e[1].mes = ft_itoaf(o->e.disk.normal.y, 2);
		ins->v3[3].e[2].mes = ft_itoaf(o->e.disk.normal.z, 2);
	}
	else if (o->type == CONE)
	{
		ins->v3[3].e[0].mes = ft_itoaf(o->e.cone.v.x, 2);
		ins->v3[3].e[1].mes = ft_itoaf(o->e.cone.v.y, 2);
		ins->v3[3].e[2].mes = ft_itoaf(o->e.cone.v.z, 2);
	}
	else if (!ft_object_selectv(ins, o))
	{
		ins->v3[3].e[0].mes = ft_strdup("0.00");
		ins->v3[3].e[1].mes = ft_strdup("0.00");
		ins->v3[3].e[2].mes = ft_strdup("0.00");
	}
}

void	ft_object_select3(t_inspector *ins, t_object *o)
{
	if (o->type == SPHERE)
		ins->v1[0].e.mes = ft_itoaf(o->e.sphere.radius, 2);
	else if (o->type == CYLINDER)
		ins->v1[0].e.mes = ft_itoaf(o->e.cylinder.radius, 2);
	else if (o->type == RING)
		ins->v1[0].e.mes = ft_itoaf(o->e.ring.radius, 2);
	else if (o->type == DISK)
		ins->v1[0].e.mes = ft_itoaf(o->e.disk.radius, 2);
	else if (o->type == ELLIPSOID)
		ins->v1[0].e.mes = ft_itoaf(o->e.ellipse.radius, 2);
	else if (o->type == TORUS)
		ins->v1[0].e.mes = ft_itoaf(o->e.torus.radius1, 2);
	else if (o->type == CUBE)
		ins->v1[0].e.mes = ft_itoaf(o->e.cube.radius, 2);
	else
		ins->v1[0].e.mes = ft_strdup("0.00");
}

void	ft_object_select4(t_inspector *ins, t_object *o)
{
	if (o->type == SPHERE)
		ins->v1[1].e.mes = ft_itoaf(o->e.sphere.radius2, 2);
	else if (o->type == CYLINDER)
		ins->v1[1].e.mes = ft_itoaf(o->e.cylinder.radius2, 2);
	else if (o->type == RING)
		ins->v1[1].e.mes = ft_itoaf(o->e.ring.radius2, 2);
	else if (o->type == DISK)
		ins->v1[1].e.mes = ft_itoaf(o->e.disk.radius2, 2);
	else if (o->type == ELLIPSOID)
		ins->v1[1].e.mes = ft_itoaf(o->e.ellipse.k, 2);
	else if (o->type == TORUS)
		ins->v1[1].e.mes = ft_itoaf(o->e.torus.radius2, 2);
	else if (o->type == CUBE)
		ins->v1[1].e.mes = ft_itoaf(o->e.cube.radius, 2);
	else
		ins->v1[1].e.mes = ft_strdup("0.00");
}

int		ft_object_select34(t_inspector *ins, t_object *o)
{
	if (o->type == TRIANGLE)
	{
		ins->v3[4].e[0].mes = ft_itoaf(o->e.triangle.a.x, 2);
		ins->v3[4].e[1].mes = ft_itoaf(o->e.triangle.a.y, 2);
		ins->v3[4].e[2].mes = ft_itoaf(o->e.triangle.a.z, 2);
		ins->v3[5].e[0].mes = ft_itoaf(o->e.triangle.b.x, 2);
		ins->v3[5].e[1].mes = ft_itoaf(o->e.triangle.b.y, 2);
		ins->v3[5].e[2].mes = ft_itoaf(o->e.triangle.b.z, 2);
		ins->v3[6].e[0].mes = ft_itoaf(o->e.triangle.c.x, 2);
		ins->v3[6].e[1].mes = ft_itoaf(o->e.triangle.c.y, 2);
		ins->v3[6].e[2].mes = ft_itoaf(o->e.triangle.c.z, 2);
	}
	else if (o->type == PARALLELOGRAM)
	{
		ins->v3[4].e[0].mes = ft_itoaf(o->e.para.a.x, 2);
		ins->v3[4].e[1].mes = ft_itoaf(o->e.para.a.y, 2);
		ins->v3[4].e[2].mes = ft_itoaf(o->e.para.a.z, 2);
		ins->v3[5].e[0].mes = ft_itoaf(o->e.para.b.x, 2);
		ins->v3[5].e[1].mes = ft_itoaf(o->e.para.b.y, 2);
		ins->v3[5].e[2].mes = ft_itoaf(o->e.para.b.z, 2);
		ins->v3[6].e[0].mes = ft_itoaf(o->e.para.c.x, 2);
		ins->v3[6].e[1].mes = ft_itoaf(o->e.para.c.y, 2);
		ins->v3[6].e[2].mes = ft_itoaf(o->e.para.c.z, 2);
		ins->v3[7].e[0].mes = ft_itoaf(o->e.para.d.x, 2);
		ins->v3[7].e[1].mes = ft_itoaf(o->e.para.d.y, 2);
		ins->v3[7].e[2].mes = ft_itoaf(o->e.para.d.z, 2);
	}
	else
		return (0);
	return (1);
}

int		ft_object_select35(t_inspector *ins, t_object *o)
{
	if (o->type == BOX)
	{
		ins->v3[4].e[0].mes = ft_itoaf(o->e.box.bounds[0].x, 2);
		ins->v3[4].e[1].mes = ft_itoaf(o->e.box.bounds[0].y, 2);
		ins->v3[4].e[2].mes = ft_itoaf(o->e.box.bounds[0].z, 2);
		ins->v3[5].e[0].mes = ft_itoaf(o->e.box.bounds[1].x, 2);
		ins->v3[5].e[1].mes = ft_itoaf(o->e.box.bounds[1].y, 2);
		ins->v3[5].e[2].mes = ft_itoaf(o->e.box.bounds[1].z, 2);

	}
	else if (o->type == ELLIPSOID)
	{
		ins->v3[4].e[0].mes = ft_itoaf(o->e.ellipse.c.x, 2);
		ins->v3[4].e[1].mes = ft_itoaf(o->e.ellipse.c.y, 2);
		ins->v3[4].e[2].mes = ft_itoaf(o->e.ellipse.c.z, 2);
	}
	else if (o->type == PARABOLOID)
	{
		ins->v3[4].e[0].mes = ft_itoaf(o->e.ellipse.c.x, 2);
		ins->v3[4].e[1].mes = ft_itoaf(o->e.ellipse.c.y, 2);
		ins->v3[4].e[2].mes = ft_itoaf(o->e.ellipse.c.z, 2);
	}
	else
		return (0);
	return (1);
}

void	ft_object_select5(t_inspector *ins, t_object *o)
{
	if (o->type == CYLINDER)
		ins->v1[2].e.mes = ft_itoaf(o->e.cylinder.height, 2);
	else if (o->type == RING)
		ins->v1[2].e.mes = ft_itoaf(o->e.ring.height, 2);
	else
		ins->v1[2].e.mes = ft_strdup("0.00");
	if (o->type == CONE)
		ins->v1[3].e.mes = ft_itoaf(o->e.cone.angle, 2);
	else
		ins->v1[3].e.mes = ft_strdup("0.00");
	if (!ft_object_select34(ins, o) && !ft_object_select35(ins, o))
	{
		ins->v3[4].e[0].mes = ft_strdup("0.00");
		ins->v3[4].e[1].mes = ft_strdup("0.00");
		ins->v3[4].e[2].mes = ft_strdup("0.00");
		ins->v3[5].e[0].mes = ft_strdup("0.00");
		ins->v3[5].e[1].mes = ft_strdup("0.00");
		ins->v3[5].e[2].mes = ft_strdup("0.00");
		ins->v3[6].e[0].mes = ft_strdup("0.00");
		ins->v3[6].e[1].mes = ft_strdup("0.00");
		ins->v3[6].e[2].mes = ft_strdup("0.00");
		ins->v3[7].e[0].mes = ft_strdup("0.00");
		ins->v3[7].e[1].mes = ft_strdup("0.00");
		ins->v3[7].e[2].mes = ft_strdup("0.00");
	}
}

void	ft_inspector_object(t_inspector *ins, t_object *o)
{
	if (!o)
		ft_no_object_select(ins);
	else
	{
		ft_object_select1(ins, o);
		ft_object_select2(ins, o);
		ft_object_select3(ins, o);
		ft_object_select4(ins, o);
		ft_object_select5(ins, o);
	}
}
