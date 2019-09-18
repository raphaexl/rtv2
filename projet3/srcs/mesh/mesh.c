/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 15:37:56 by ebatchas          #+#    #+#             */
/*   Updated: 2019/09/17 17:48:44 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

int		ft_mesh_triangulate(t_mesh *m, t_obj *obj)
{
	int		i;
	int		size;

	i = -1;
	size = obj->vertices.length / 3; 
	if (!(m->triangles = ft_memalloc(sizeof(t_triangle) * size)))
		return (-1);
	if (!(m->normals = ft_memalloc(sizeof(t_normal) * size)))
		return (-1);
	if (!(m->texels = ft_memalloc(sizeof(t_texel) * size)))
		return (-1);
	while (++i < size)
	{
		m->triangles[i].a = *(t_vec3 *)obj->vertices.items[i * 3 + 0];
		m->triangles[i].b = *(t_vec3 *)obj->vertices.items[i * 3 + 1];
		m->triangles[i].c = *(t_vec3 *)obj->vertices.items[i * 3 + 2];
		m->normals[i].a = *(t_vec3 *)obj->normals.items[i * 3 + 0];
		m->normals[i].b = *(t_vec3 *)obj->normals.items[i * 3 + 1];
		m->normals[i].c = *(t_vec3 *)obj->normals.items[i * 3 + 2];
		m->texels[i].a = *(t_vec2 *)obj->uvs.items[i * 3 + 0];
		m->texels[i].b = *(t_vec2 *)obj->uvs.items[i * 3 + 1];
		m->texels[i].c = *(t_vec2 *)obj->uvs.items[i * 3 + 2];
	}
	m->size = size;
	return (0);
}


void		ft_print_mesh(t_mesh *m)
{
	printf("mesh %s\n", m->name);
	for (int i = 0; i < m->size; i++)
	{
		printf("Triangle : %d\n", i);
		printf ("a : x = %.2f\ty = %.2f\tz = %.2f\n", m->triangles[i].a.x, m->triangles[i].a.y,
				m->triangles[i].a.z);
		printf ("b : x = %.2f\ty = %.2f\tz = %.2f\n", m->triangles[i].b.x, m->triangles[i].b.y,
				m->triangles[i].b.z);
		printf ("c : x = %.2f\ty = %.2f\tz = %.2f\n", m->triangles[i].c.x, m->triangles[i].c.y,
				m->triangles[i].c.z);
	}
}
