/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 13:07:21 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/02 21:43:23 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

void	ft_object_aplly1(t_inspector *ins, t_object **o)
{
	(*o)->translate.x = ft_atof(ins->v3[0].e[0].mes );
	(*o)->translate.y = ft_atof(ins->v3[0].e[1].mes );
	(*o)->translate.z = ft_atof(ins->v3[0].e[2].mes );
	(*o)->rotate.x = ft_atof(ins->v3[1].e[0].mes);
	(*o)->rotate.y = ft_atof(ins->v3[1].e[1].mes);
	(*o)->rotate.z = ft_atof(ins->v3[1].e[2].mes);
	(*o)->scale.x = ft_atof(ins->v3[2].e[0].mes);
	(*o)->scale.y = ft_atof(ins->v3[2].e[1].mes);
	(*o)->scale.z = ft_atof(ins->v3[2].e[2].mes);
	(*o)->material.diffuse.red = ft_atof(ins->v3[8].e[0].mes);
	(*o)->material.diffuse.green = ft_atof(ins->v3[8].e[1].mes);
	(*o)->material.diffuse.blue = ft_atof(ins->v3[8].e[2].mes);
	(*o)->material.specular.red = ft_atof(ins->v3[9].e[0].mes);
	(*o)->material.specular.green = ft_atof(ins->v3[9].e[1].mes);
	(*o)->material.specular.blue = ft_atof(ins->v3[9].e[2].mes);
	(*o)->material.spec_pow = ft_atof(ins->v1[4].e.mes);
	(*o)->material.albedo[0] = ft_atof(ins->v4[0].e[0].mes);
	(*o)->material.albedo[1] = ft_atof(ins->v4[0].e[1].mes);
	(*o)->material.albedo[2] = ft_atof(ins->v4[0].e[2].mes);
	(*o)->material.albedo[3] = ft_atof(ins->v4[0].e[3].mes);
}

int 	ft_object_apllyv(t_inspector *ins, t_object **o)
{
	if ((*o)->type == RING)
	{
		(*o)->e.ring.v.x =	ft_atof(ins->v3[3].e[0].mes);
		(*o)->e.ring.v.y =	ft_atof(ins->v3[3].e[1].mes);
		(*o)->e.ring.v.z =	ft_atof(ins->v3[3].e[2].mes);
	}
	else if ((*o)->type == CYLINDER)
	{
		(*o)->e.cylinder.v.x = ft_atof(ins->v3[3].e[0].mes);
		(*o)->e.cylinder.v.y = ft_atof(ins->v3[3].e[1].mes);
		(*o)->e.cylinder.v.z = ft_atof(ins->v3[3].e[2].mes);
	}
	else if ((*o)->type == ELLIPSOID)
	{
		(*o)->e.ellipse.v.x = ft_atof(ins->v3[3].e[0].mes);
		(*o)->e.ellipse.v.y = ft_atof(ins->v3[3].e[1].mes);
		(*o)->e.ellipse.v.z = ft_atof(ins->v3[3].e[2].mes);
	}
	else if ((*o)->type == PARABOLOID)
	{
		(*o)->e.parab.v.x = ft_atof(ins->v3[3].e[0].mes);
		(*o)->e.parab.v.y = ft_atof(ins->v3[3].e[1].mes);
		(*o)->e.parab.v.z = ft_atof(ins->v3[3].e[2].mes);
	}
	else
		return (0);
	return (1);
}

void	ft_object_aplly2(t_inspector *ins, t_object **o)
{
	if ((*o)->type == PLANE)
	{
		(*o)->e.plane.normal.x = ft_atof(ins->v3[3].e[0].mes);
		(*o)->e.plane.normal.y = ft_atof(ins->v3[3].e[1].mes);
		(*o)->e.plane.normal.z = ft_atof(ins->v3[3].e[2].mes);
	}
	else if ((*o)->type == DISK)
	{
		(*o)->e.disk.normal.x = ft_atof(ins->v3[3].e[0].mes);
		(*o)->e.disk.normal.y = ft_atof(ins->v3[3].e[1].mes);
		(*o)->e.disk.normal.z = ft_atof(ins->v3[3].e[2].mes);
	}
	else if ((*o)->type == CONE)
	{
		(*o)->e.cone.v.x = ft_atof(ins->v3[3].e[0].mes);
		(*o)->e.cone.v.y = ft_atof(ins->v3[3].e[1].mes);
		(*o)->e.cone.v.z = ft_atof(ins->v3[3].e[2].mes);
	}
}

void	ft_object_aplly3(t_inspector *ins, t_object **o)
{
	if ((*o)->type == SPHERE)
		(*o)->e.sphere.radius = ft_atof(ins->v1[0].e.mes);
	else if ((*o)->type == CYLINDER)
		(*o)->e.cylinder.radius = ft_atof(ins->v1[0].e.mes);
	else if ((*o)->type == RING)
		(*o)->e.ring.radius = ft_atof(ins->v1[0].e.mes);
	else if ((*o)->type == DISK)
		(*o)->e.disk.radius = ft_atof(ins->v1[0].e.mes);
	else if ((*o)->type == ELLIPSOID)
		(*o)->e.ellipse.radius = ft_atof(ins->v1[0].e.mes);
	else if ((*o)->type == TORUS)
		(*o)->e.torus.radius1 = ft_atof(ins->v1[0].e.mes);
	else if ((*o)->type == CUBE)
		(*o)->e.cube.radius = ft_atof(ins->v1[0].e.mes);
}

void	ft_object_aplly4(t_inspector *ins, t_object **o)
{
	if ((*o)->type == SPHERE)
		(*o)->e.sphere.radius2 = (*o)->e.sphere.radius * (*o)->e.sphere.radius;
	else if ((*o)->type == CYLINDER)
		(*o)->e.cylinder.radius2 = (*o)->e.cylinder.radius * (*o)->e.cylinder.radius;
	else if ((*o)->type == RING)
		(*o)->e.ring.radius2 = (*o)->e.ring.radius * (*o)->e.ring.radius;
	else if ((*o)->type == DISK)
		(*o)->e.disk.radius2 = (*o)->e.disk.radius * (*o)->e.disk.radius;
	else if ((*o)->type == ELLIPSOID)
		(*o)->e.ellipse.k = ft_atof(ins->v1[1].e.mes); 
	else if ((*o)->type == TORUS)
		(*o)->e.torus.radius2 = ft_atof(ins->v1[1].e.mes); 
}

void	ft_object_apply34(t_inspector *ins, t_object **o)
{
	if ((*o)->type == TRIANGLE)
	{
		(*o)->e.triangle.a.x = ft_atof(ins->v3[4].e[0].mes);
		(*o)->e.triangle.a.y = ft_atof(ins->v3[4].e[1].mes);
		(*o)->e.triangle.a.z = ft_atof(ins->v3[4].e[2].mes);
		(*o)->e.triangle.b.x = ft_atof(ins->v3[5].e[0].mes);
		(*o)->e.triangle.b.y = ft_atof(ins->v3[5].e[1].mes);
		(*o)->e.triangle.b.z = ft_atof(ins->v3[5].e[2].mes);
		(*o)->e.triangle.c.x = ft_atof(ins->v3[6].e[0].mes);
		(*o)->e.triangle.c.y = ft_atof(ins->v3[6].e[1].mes);
		(*o)->e.triangle.c.z = ft_atof(ins->v3[6].e[2].mes);
	}
	else if ((*o)->type == PARALLELOGRAM)
	{
		(*o)->e.para.a.x = ft_atof(ins->v3[4].e[0].mes);
		(*o)->e.para.a.y = ft_atof(ins->v3[4].e[1].mes);
		(*o)->e.para.a.z = ft_atof(ins->v3[4].e[2].mes);
		(*o)->e.para.b.x = ft_atof(ins->v3[5].e[0].mes);
		(*o)->e.para.b.y = ft_atof(ins->v3[5].e[1].mes);
		(*o)->e.para.b.z = ft_atof(ins->v3[5].e[2].mes);
		(*o)->e.para.c.x = ft_atof(ins->v3[6].e[0].mes);
		(*o)->e.para.c.y = ft_atof(ins->v3[6].e[1].mes);
		(*o)->e.para.c.z = ft_atof(ins->v3[6].e[2].mes);
		(*o)->e.para.d.x = ft_atof(ins->v3[7].e[0].mes);
		(*o)->e.para.d.y = ft_atof(ins->v3[7].e[1].mes);
		(*o)->e.para.d.z = ft_atof(ins->v3[7].e[2].mes);
	}
}

void	ft_object_apply35(t_inspector *ins, t_object **o)
{
	if ((*o)->type == BOX)
	{
		(*o)->e.box.bounds[0].x = ft_atof(ins->v3[4].e[0].mes);
		(*o)->e.box.bounds[0].y = ft_atof(ins->v3[4].e[1].mes);
		(*o)->e.box.bounds[0].z = ft_atof(ins->v3[4].e[2].mes);
		(*o)->e.box.bounds[1].x = ft_atof(ins->v3[5].e[0].mes);
		(*o)->e.box.bounds[1].y = ft_atof(ins->v3[5].e[1].mes);
		(*o)->e.box.bounds[1].z = ft_atof(ins->v3[5].e[2].mes);

	}
	else if ((*o)->type == ELLIPSOID)
	{
		(*o)->e.ellipse.c.x = ft_atof(ins->v3[4].e[0].mes);
		(*o)->e.ellipse.c.y = ft_atof(ins->v3[4].e[1].mes);
		(*o)->e.ellipse.c.z = ft_atof(ins->v3[4].e[2].mes);
	}
	else if ((*o)->type == PARABOLOID)
	{
		(*o)->e.parab.c.x = ft_atof(ins->v3[4].e[0].mes);
		(*o)->e.parab.c.y = ft_atof(ins->v3[4].e[1].mes);
		(*o)->e.parab.c.z = ft_atof(ins->v3[4].e[2].mes);
	}
}


void	ft_object_aplly5(t_inspector *ins, t_object **o)
{
	if ((*o)->type == CYLINDER)
		(*o)->e.cylinder.height = ft_atof(ins->v1[2].e.mes);
	else if ((*o)->type == RING)
		(*o)->e.ring.height = ft_atof(ins->v1[2].e.mes);
	if ((*o)->type == CONE)
		(*o)->e.cone.angle = ft_atof(ins->v1[3].e.mes);
	ft_object_apply34(ins, o);
	ft_object_apply35(ins, o);
}

void	ft_inspector_apply(t_inspector *ins, t_object **o)
{
	if (!*o)
		return ;
	else
	{
		ft_object_aplly1(ins, o);
		ft_object_aplly2(ins, o);
		ft_object_aplly3(ins, o);
		ft_object_aplly4(ins, o);
		ft_object_aplly5(ins, o);
	}
}
