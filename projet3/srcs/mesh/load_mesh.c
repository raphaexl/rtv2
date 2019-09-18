/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_mesh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 14:50:20 by ebatchas          #+#    #+#             */
/*   Updated: 2019/09/17 17:45:25 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

int		ft_mesh_load(t_mesh *m, char *file_name)
{
	m->name = file_name;
	ft_parse_mesh(m, file_name);
	return (1);
}

void	ft_mesh_clean(t_mesh *m)
{
	free(m->triangles);
	m->triangles = NULL;
	free(m->normals);
	m->normals = NULL;
	free(m->texels);
	m->texels = NULL;
}
