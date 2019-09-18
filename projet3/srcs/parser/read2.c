/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:57:20 by ebatchas          #+#    #+#             */
/*   Updated: 2019/09/18 17:12:41 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

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
	item.material = ft_material_read(fd);
//	ft_print_error("DEBUG");
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

t_object		*ft_mesh_read(int fd)
{
	t_object	item;
	char		*line;

	item.name = "MESH";
	if (ft_get_next_line(fd, &line) == 1 && line)
		ft_mesh_load(&item.e.mesh, line);
	item.pos = ft_vec3_read(fd);
	item.translate = ft_vec3_read(fd);
	item.translate = ft_translate_vec3(item.translate, item.pos, 0);
	item.pos = ft_vec3(0.0, 0.0, 0.0);
	item.rotate = ft_vec3_read(fd);
	item.material = ft_material_read(fd);
	printf("r = %.2f/tg = %.2f\tb = %.2f\n", item.material.diffuse.red, item.material.diffuse.green, item.material.diffuse.blue);
	//ft_print_mesh(&item.e.mesh);
	//exit(0);
	return (ft_object_new(MESH, &item));
}

t_light			*ft_light_read(int fd)
{
	char		*line;
	t_light		l;

	ft_memset(&l, 0, sizeof(l));
	if (ft_get_next_line(fd, &line) == 1 && line)
	{
		if (!ft_strcmp("DEFAULT", line))
		{
			l.type = DEFAULT_LIGHT;
			l.u.def.pos = ft_vec3_read(fd);
		}
		if (!ft_strcmp("DIRECTIONNAL", line) || (!ft_strcmp("DISTANT", line)))
		{
			l.type = DISTANT_LIGHT;
			l.u.direct.dir = ft_vec3_read(fd);
		}
		else if (!ft_strcmp("POINT", line))
		{
			ft_putendl("Before");
			l.type = POINT_LIGHT;
			l.u.point.pos = ft_vec3_read(fd);
			l.u.point.constant = 1.0f;
			if (ft_get_next_line(fd, &line) == 1 && line)
				l.u.point.linear = ft_atof(line);
			else
				ft_print_error("Point light requires linear value :)");
			if (ft_get_next_line(fd, &line) == 1 && line)
				l.u.point.quadratic = ft_atof(line);
			else
				ft_print_error("Point light requires quadratic value :)");
		}
		else if (!ft_strcmp("SPOT", line))
		{
			l.type = SPOT_LIGHT;
			l.u.spot.pos = ft_vec3_read(fd);
			l.u.spot.dir = ft_vec3_read(fd);
			l.u.spot.constant = 1.0f;
			if (ft_get_next_line(fd, &line) == 1 && line)
				l.u.spot.linear = ft_atof(line);
			else
				ft_print_error("Spot light requires linear value :)");
			if (ft_get_next_line(fd, &line) == 1 && line)
				l.u.spot.quadratic = ft_atof(line);
			else
				ft_print_error("Spot light requires quadratic value :)");
			if (ft_get_next_line(fd, &line) == 1 && line)
				l.u.spot.cut_off = cos(DEG_TO_RAD(ft_atof(line)));
			else
				ft_print_error("Spot light requires cut_off value :)");
			if (ft_get_next_line(fd, &line) == 1 && line)
				l.u.spot.outer_cut_off = cos(DEG_TO_RAD(ft_atof(line)));
			else
				ft_print_error("Spot light requires outer_cutt_off value :)");
		}
	}
	else
		ft_print_error("light invalid :)");
	l.diffuse = ft_col3_read(fd);
	l.specular = (t_col3){1.0, 1.0, 1.0};
	l.ambient = (t_col3){0.1f, 0.1f, 0.1f};
	l.intensity = 1.5;
	return (ft_light_new(l.type, &l));
}
