/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 15:37:56 by ebatchas          #+#    #+#             */
/*   Updated: 2019/06/15 18:43:24 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

void		ft_print_mesh(t_mesh *m)
{
	printf("mesh %s\n", m->name);
	printf("%d\n", m->n_faces);
	for (int i = 0; i < m->n_faces; ++i)
	printf("%d ", m->face_index[i]);
	puts("");
	for (int i = 0; i < m->verts_index_array_size; i++)
	   printf("%d ", m->verts_index[i]);
	puts("");
	for (int i = 0; i < m->verts_array_size; i++)
		printf("%.0f %.0f %.0f ", m->verts[i].x, m->verts[i].y, m->verts[i].z);
	puts("");
	for (int i = 0; i < m->verts_index_array_size; i++)
		printf("%.0f %.0f %.0f ", m->normals[i].x, m->normals[i].y, m->normals[i].z);
	puts("");
	for (int i = 0; i < m->verts_index_array_size; i++)
		printf("%.3f %.3f ", m->st[i].x, m->st[i].y);
	puts("");
}
