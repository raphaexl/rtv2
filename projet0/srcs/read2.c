/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:57:20 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/28 17:07:27 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

t_object		*ft_box_read(int fd)
{
	t_object	item;

	item.name = "BOX";
	item.pos = ft_vec3_read(fd);
	item.translate = ft_vec3_read(fd);
	item.rotate = ft_vec3_read(fd);
	item.translate = ft_translate_vec3(item.translate, item.pos, 0);
	item.e.box.bounds[0] = ft_vec3(-1.0, -1.0, -1.0);
	item.e.box.bounds[1] = ft_vec3(1.0, 1.0, 1.0);
	item.material = ft_material_read(fd);
	return (ft_object_new(BOX, &item));
}

t_object		*ft_torus_read(int fd)
{
	t_object	item;
	char		*line;

	item.name = "TORUS";
	item.pos = ft_vec3_read(fd);
	item.translate = ft_vec3_read(fd);
	item.translate = ft_translate_vec3(item.translate, item.pos, 0);
	item.pos = ft_vec3(0.0, 0.0, 0.0);
	item.rotate = ft_vec3_read(fd);
	if (ft_get_next_line(fd, &line) == 1 && line)
		item.e.torus.radius1 = ft_atof(line);
	else
		ft_print_error("torus Radius :)");
	if (ft_get_next_line(fd, &line) == 1 && line)
		item.e.torus.radius2 = ft_atof(line);
	else
		ft_print_error("torus radius :)");
	item.material = ft_material_read(fd);
	return (ft_object_new(TORUS, &item));
}

t_object		*ft_cube_read(int fd)
{
	t_object	item;
	char		*line;

	item.name = "CUBE";
	item.pos = ft_vec3_read(fd);
	item.translate = ft_vec3_read(fd);
	item.translate = ft_translate_vec3(item.translate, item.pos, 0);
	item.pos = ft_vec3(0.0, 0.0, 0.0);
	item.rotate = ft_vec3_read(fd);
	if (ft_get_next_line(fd, &line) == 1 && line)
		item.e.cube.radius = ft_atof(line);
	else
		item.e.cube.radius = 11.8;
	item.material = ft_material_read(fd);
	return (ft_object_new(CUBE, &item));
}

t_object		*ft_triangle_read(int fd)
{
	t_object	item;

	item.name = "TRIANGLE";
	item.pos = ft_vec3_read(fd);
	item.translate = ft_vec3_read(fd);
	item.translate = ft_translate_vec3(item.translate, item.pos, 0);
	item.pos = ft_vec3(0.0, 0.0, 0.0);
	item.rotate = ft_vec3_read(fd);
	item.e.triangle.a = ft_vec3_read(fd);
	item.e.triangle.b = ft_vec3_read(fd);
	item.e.triangle.c = ft_vec3_read(fd);
	item.e.triangle.u = 0.0f;
	item.e.triangle.v = 0.0f;
	item.e.triangle.t = 0.0f;
	item.material = ft_material_read(fd);
	return (ft_object_new(TRIANGLE, &item));
}

t_object		*ft_parallelogram_read(int fd)
{
	t_object	item;

	item.name = "PARALLELOGRAM";
	item.pos = ft_vec3_read(fd);
	item.translate = ft_vec3_read(fd);
	item.translate = ft_translate_vec3(item.translate, item.pos, 0);
	item.pos = ft_vec3(0.0, 0.0, 0.0);
	item.rotate = ft_vec3_read(fd);
	item.e.para.a = ft_vec3_read(fd);
	item.e.para.b = ft_vec3_read(fd);
	item.e.para.c = ft_vec3_read(fd);
	item.e.para.d = ft_vec3_read(fd);
	item.e.para.u = 0.0f;
	item.e.para.v = 0.0f;
	item.e.para.t = 0.0f;
	item.material = ft_material_read(fd);
	return (ft_object_new(PARALLELOGRAM, &item));
}

t_light			*ft_light_read(int fd)
{
	char		*line;
	char		**tab;
	t_iterm		item;
	int			i;

	if (ft_get_next_line(fd, &line) == 1 && line)
	{
		if ((tab = ft_strsplit(line, ' ')) && ft_tab_len(tab) != 6)
			ft_print_error("invalid light paramters");
		item.pos.x = ft_atof(tab[0]);
		item.pos.y = ft_atof(tab[1]);
		item.pos.z = ft_atof(tab[2]);
		item.color.red = ft_atof(tab[3]);
		item.color.green = ft_atof(tab[4]);
		item.color.blue = ft_atof(tab[5]);
		i = -1;
		while (++i < 6)
			free(tab[i]);
		free(tab);
		tab = NULL;
	}
	else
		ft_print_error("light invalid :)");
	return (ft_light_new(item.pos, item.color));
}
