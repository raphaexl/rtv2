/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:57:20 by ebatchas          #+#    #+#             */
/*   Updated: 2019/06/08 22:56:08 by ebatchas         ###   ########.fr       */
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

t_object		*ft_ellipsoid_read(int fd)
{
	t_object	item;
	char		*line;

	item.name = "ELLIPSOID";
	item.pos = ft_vec3_read(fd);
	item.translate = ft_vec3_read(fd);
	item.translate = ft_translate_vec3(item.translate, item.pos, 0);
	item.pos = ft_vec3(0.0, 0.0, 0.0);
	item.rotate = ft_vec3_read(fd);
	if (ft_get_next_line(fd, &line) == 1 && line)
		item.e.ellipse.radius = ft_atof(line);
	else
		ft_print_error("ellipsoid radius :)");
	if (ft_get_next_line(fd, &line) == 1 && line)
		item.e.ellipse.k = ft_clamp(0.1, 0.9, ft_atof(line));
	else
		ft_print_error("ellipsoid distance between the two centers :)");
	item.e.ellipse.radius2 = item.e.ellipse.radius * item.e.ellipse.radius;
	item.e.ellipse.v = ft_vec3_normalized(ft_vec3_read(fd));
	item.material = ft_material_read(fd);
	return (ft_object_new(ELLIPSOID, &item));
}

t_object		*ft_paraboloid_read(int fd)
{
	t_object	item;
	char		*line;

	item.name = "PARABOLOID";
	item.pos = ft_vec3_read(fd);
	item.translate = ft_vec3_read(fd);
	item.translate = ft_translate_vec3(item.translate, item.pos, 0);
	item.pos = ft_vec3(0.0, 0.0, 0.0);
	item.rotate = ft_vec3_read(fd);
	if (ft_get_next_line(fd, &line) == 1 && line)
		item.e.parab.k = ft_clamp(0.1, 0.9, ft_atof(line));
	else
		ft_print_error("paraboloid distance between the two centers :)");
	item.e.parab.v = ft_vec3_normalized(ft_vec3_read(fd));
	item.material = ft_material_read(fd);
	return (ft_object_new(PARABOLOID, &item));
}

t_light			*ft_light_read(int fd)
{
	char		*line;
	t_light		l;

	l.pos = (t_vec3){0.0, 0.0, 0.0};
	l.dir = (t_vec3){0.0, 0.0, -1.0};
	if (ft_get_next_line(fd, &line) == 1 && line)
	{
		if (!ft_strcmp("DIRECTIONNAL", line) || (!ft_strcmp("DISTANT", line)))
		{
			l.type = DISTANT;
			l.dir = ft_vec3_read(fd);
		}
		else if (!ft_strcmp("SPHERICAL", line) || (!ft_strcmp("POINT", line)))
		{
			write(1, "Hi\n", 3);
			l.type = POINT;
			l.pos = ft_vec3_read(fd);
		}
	}
	else
		ft_print_error("light invalid :)");
	l.color = ft_col3_read(fd);
	if (ft_get_next_line(fd, &line) == 1 && line)
		l.intensity = ft_atof(line);
	else
		l.intensity = 1.0;
	return (ft_light_new(l.type, &l));
}
