/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_mesh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 14:50:20 by ebatchas          #+#    #+#             */
/*   Updated: 2019/06/15 19:06:09 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

int		ft_mesh_part5(t_mesh *m, int fd)
{
	char	*line;
	char	**tab;
	int		i;

	i = -1;
	tab = NULL;
	if (!(m->st = (t_vec2 *)malloc(sizeof(t_vec2) * m->verts_index_array_size)))
		ft_print_error("malloc error in mesh loading 5");
	if (ft_get_next_line(fd, &line) && line)
	{
		if (!(tab = ft_strsplit(line, ' ')) || !ft_tab_len(tab))
			ft_print_error("texture array spliting error 5");
		while (++i < m->verts_index_array_size)
		{
			m->st[i].x  = ft_atof(tab[i * 2]);
			m->st[i].y = ft_atof(tab[i * 2 + 1]);
		}
	}
	i = ft_tab_len(tab);
	while (--i >= 0)
		free(tab[i]);
	free(tab);
	return (1);
}

int		ft_mesh_part4(t_mesh *m, int fd)
{
	char	*line;
	char	**tab;
	int		i;

	i = -1;
	tab = NULL;
	if (!(m->normals = (t_vec3 *)malloc(sizeof(t_vec3) * m->verts_index_array_size)))
		ft_print_error("malloc error in mesh loading 4");
	if (ft_get_next_line(fd, &line) && line)
	{
		if (!(tab = ft_strsplit(line, ' ')) || (!ft_tab_len(tab)))
			ft_print_error("normals array spliting error 4");
	//	printf("%s\n", line);
		//printf("%s\n", m->vertex_index_array_size);
		while (++i < m->verts_index_array_size)
		{
			m->normals[i].x  = ft_atof(tab[i * 3]);
			m->normals[i].y = ft_atof(tab[i * 3 + 1]);
			m->normals[i].z = ft_atof(tab[i * 3 + 2]);
		}
	}
	i = ft_tab_len(tab);
	while (--i >= 0)
		free(tab[i]);
	free(tab);
	if (!ft_mesh_part5(m, fd))
		ft_print_error("part2 mesh loading failed");
	return (1);
}

int		ft_mesh_part3(t_mesh *m, int fd)
{
	char	*line;
	char	**tab;
	int		i;

	i = -1;
	tab = NULL;
	if (!(m->verts = (t_vec3 *)malloc(sizeof(t_vec3) * m->verts_array_size)))
		ft_print_error("malloc error in mesh loading 3");
	if (ft_get_next_line(fd, &line) && line)
	{
		if (!(tab = ft_strsplit(line, ' ')) || (!ft_tab_len(tab)))
				ft_print_error("verts array spliting error 3");
		while (++i < m->verts_array_size)
		{
			m->verts[i].x  = ft_atof(tab[i * 3]);
			m->verts[i].y = ft_atof(tab[i * 3 + 1]);
			m->verts[i].z = ft_atof(tab[i * 3 + 2]);
		}
	}
	i = ft_tab_len(tab);
	while (--i >= 0)
		free(tab[i]);
	free(tab);
	if (!ft_mesh_part4(m, fd))
		ft_print_error("part2 mesh loading failed");
	return (1);
}

int		ft_mesh_part2(t_mesh *m, int fd)
{
	char	*line;
	char	**tab;
	int		i;

	i = -1;
	tab = NULL;
	if (!(m->verts_index = (int *)malloc(sizeof(int) * m->verts_index_array_size)))
		ft_print_error("malloc error in mesh loading 2");
	if (ft_get_next_line(fd, &line) && line)
	{
		if (!(tab = ft_strsplit(line, ' ')) || (ft_tab_len(tab) != m->verts_index_array_size))
			ft_print_error("verts index spliting error 2");
		m->verts_array_size = 0;
		//exit(0);
		while (++i < m->verts_index_array_size)
		{
			m->verts_index[i] = ft_atoi(tab[i]);
			if (m->verts_index[i] > m->verts_array_size)
				m->verts_array_size = m->verts_index[i];
		}
		m->verts_array_size += 1;
	}
	if (!ft_mesh_part3(m, fd))
		ft_print_error("part2 mesh loading failed");
	while (--i >= 0)
		free(tab[i]);
	free(tab);
	return (1);
}

int		ft_mesh_part1(t_mesh *m, int fd)
{
	char	*line;
	char	**tab;
	int		i;

	i = -1;
	tab = NULL;
	if (ft_get_next_line(fd, &line) && line && (m->n_faces = ft_atoi(line)))
	{
		if (!(m->face_index = (int *)malloc(sizeof(int) * m->n_faces)))
			ft_print_error("malloc error in mesh loading 1");
		if (ft_get_next_line(fd, &line) && line)
		{
			if (!(tab = ft_strsplit(line, ' ')) || (ft_tab_len(tab) != m->n_faces))
				ft_print_error("face index spliting error 1");
			m->verts_index_array_size = 0;
			while (++i < m->n_faces)
			{
				m->face_index[i] = ft_atoi(tab[i]);
				m->verts_index_array_size += m->face_index[i];
			}
		}
	}
	while (--i >= 0)
		free(tab[i]);
	free(tab);
	if (!ft_mesh_part2(m, fd))
		ft_print_error("part1 mesh loading failed");
	return (1);
}


int		ft_mesh_triangulate(t_mesh *m)
{
	int		i;
	int		j;
	int		k;

	k = 0;
	i = -1; 
	m->max_verts_index = 0;
	while (++i < m->n_faces)
	{
		m->num_tris += m->face_index[i] - 2;
		j = -1;
		while (++j < m->face_index[i])
		{
			if (m->verts_index[k + j] > m->max_verts_index)
				m->max_verts_index = m->verts_index[k + j];
		}
		k += m->face_index[i];
	}
	m->max_verts_index += 1;
	if (m->max_verts_index == m->verts_index_array_size)
		printf("%d\t", m->verts_index_array_size);
	 if (m->max_verts_index == m->verts_array_size)
		printf("%d\t", m->verts_array_size);
	write(1, "Bye\n", 4);
	exit(0);
}

int		ft_mesh_load(t_mesh *m, char *file_name)
{
	int		fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0 || fd > 4096)
		ft_print_error("Error bad mesh file\n");
	m->name = file_name;
	ft_mesh_part1(m, fd);
	ft_mesh_triangulate(m);
	return (1);
}

void	ft_mesh_clean(t_mesh *m)
{
	free(m->face_index);
	m->face_index = NULL;
	free(m->verts_index);
	m->verts_index = NULL;
	free(m->verts);	
	m->verts = NULL;
	free(m->normals);
	m->normals = NULL;
	free(m->st);
	m->st = NULL;
}
