/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:13:24 by ebatchas          #+#    #+#             */
/*   Updated: 2019/09/17 13:33:49 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void	ft_obj_init(t_obj *obj)
{
	ft_vector_init(&obj->vertices, sizeof(t_vec3));
	ft_vector_init(&obj->uvs, sizeof(t_vec2));
	ft_vector_init(&obj->normals, sizeof(t_vec3));
	ft_vector_init(&obj->v_indices, sizeof(int));
	ft_vector_init(&obj->uv_indices, sizeof(int));
	ft_vector_init(&obj->n_indices, sizeof(int));
}

void	ft_obj_clean(t_obj *obj)
{
	ft_vector_free(&obj->vertices);
	ft_vector_free(&obj->uvs);
	ft_vector_free(&obj->normals);
	ft_vector_free(&obj->v_indices);
	ft_vector_free(&obj->uv_indices);
	ft_vector_free(&obj->n_indices);
}

int		ft_load_obj_file(t_obj *obj, const char *file_name)
{
	int			fd;
	char		*line;
	t_vector	v_list;
	t_vector	uv_list;
	t_vector	n_list;

	fd = open(file_name, O_RDONLY);
	if (fd < 0 || fd > 4096)
		return (-1);
	ft_vector_init(&v_list, sizeof(t_vec3));
	ft_vector_init(&uv_list, sizeof(t_vec2));
	ft_vector_init(&n_list, sizeof(t_vec3));
	while (ft_get_next_line(fd, &line) && line)
	{
		if (line[0] == 'v' && line[1] == ' ')
			ft_parse_obj_vector(&v_list, line);
		else if (line[0] == 'v' && line[1] == 't')
			ft_parse_obj_uv(&uv_list, line);
		else if (line[0] == 'v' && line[1] == 'n')
			ft_parse_obj_normal(&n_list, line);
		else if (line[0] == 'f' && line[1] == ' ')
			ft_parse_obj_faces(obj, line);
		free(line);
	}
	ft_make_obj(obj, &v_list, &uv_list, &n_list);
	ft_vector_free(&v_list);
	ft_vector_free(&uv_list);
	ft_vector_free(&n_list);
	close(fd);
	return (0);
}

void	ft_parse_mesh(t_mesh *mesh, const char *file_name)
{
	t_obj obj;

	ft_memset(&obj, 0, sizeof(t_obj));
	ft_obj_init(&obj);
	ft_load_obj_file(&obj, file_name);
	ft_mesh_triangulate(mesh, &obj);
	ft_putendl("Did not segfault");
	ft_print_obj(&obj);
	ft_obj_clean(&obj);
}
