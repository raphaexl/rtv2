/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 20:58:28 by ebatchas          #+#    #+#             */
/*   Updated: 2019/09/22 21:55:26 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

void	ft_bizzare(t_obj *obj, char **tab)
{
	int index[3];

	index[0] = ft_atoi(tab[0]);
	index[1] = ft_atoi(tab[1]);
	index[2] = ft_atoi(tab[2]);
	ft_vector_push_back(&obj->v_indices, &index[0]);
	ft_vector_push_back(&obj->uv_indices, &index[1]);
	ft_vector_push_back(&obj->n_indices, &index[2]);
}

void	ft_make_obj(t_obj *obj, t_vector *v, t_vector *uvs, t_vector *normals)
{
	int		i;
	int		size;

	i = -1;
	size = obj->v_indices.size(&obj->v_indices);
	while (++i < size)
		obj->vertices.push_back(&obj->vertices,
				(t_vec3 *)v->items[*(int *)obj->v_indices.items[i] - 1]);
	size = obj->uv_indices.size(&obj->uv_indices);
	i = -1;
	while (++i < size)
		obj->uvs.push_back(&obj->uvs,
				(t_vec2 *)uvs->items[*(int *)obj->uv_indices.items[i] - 1]);
	size = obj->n_indices.size(&obj->n_indices);
	i = -1;
	while (++i < size)
		obj->normals.push_back(&obj->normals,
				(t_vec3 *)normals->items[*(int *)obj->n_indices.items[i] - 1]);
}
