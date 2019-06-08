/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:57:06 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/31 10:51:27 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

t_object		*ft_sphere_read(int fd)
{
	char		*line;
	t_object	item;

	item.name = "SPHERE";
	item.pos = ft_vec3_read(fd);
	item.translate = ft_vec3_read(fd);
	item.rotate = ft_vec3_read(fd);
	item.translate = ft_translate_vec3(item.translate, item.pos, 0);
	item.pos = (t_vec3){0.0, 0.0, 0.0};
	if (ft_get_next_line(fd, &line) == 1 && line)
		item.e.sphere.radius = ft_atof(line);
	else
		ft_print_error("sphere radius :)");
	item.e.sphere.radius2 = item.e.sphere.radius * item.e.sphere.radius;
	item.material = ft_material_read(fd);
	return (ft_object_new(SPHERE, &item));
}

t_object		*ft_cone_read(int fd)
{
	char		*line;
	t_object	item;

	item.pos = ft_vec3_read(fd);
	item.name = "CONE";
	item.translate = ft_vec3_read(fd);
	item.rotate = ft_vec3_read(fd);
	item.translate = ft_translate_vec3(item.translate, item.pos, 0);
	item.pos = (t_vec3){0.0, 0.0, 0.0};
	if (ft_get_next_line(fd, &line) == 1 && line)
		item.e.cone.angle = DEG_TO_RAD(ft_clamp(1.0, 79.0, ft_atof(line)));
	else
		ft_print_error("cone angle :)");
	if (ft_get_next_line(fd, &line) == 1 && line)
		item.e.cone.height = ft_atof(line);
	else
		ft_print_error("cone height :)");
	item.e.cone.v = ft_vec3_normalized(ft_vec3_read(fd));
	item.material = ft_material_read(fd);
	return (ft_object_new(CONE, &item));
}

t_object		*ft_cylindre_read(int fd)
{
	char		*line;
	t_object	item;

	item.name = "CYLINDRE";
	item.pos = ft_vec3_read(fd);
	item.translate = ft_vec3_read(fd);
	item.rotate = ft_vec3_read(fd);
	item.translate = ft_translate_vec3(item.translate, item.pos, 0);
	item.pos = (t_vec3){0.0, 0.0, 0.0};
	if (ft_get_next_line(fd, &line) == 1 && line)
		item.e.cylinder.radius = ft_atof(line);
	else
		ft_print_error("cylinder radius :)");
	item.e.cylinder.radius2 = item.e.cylinder.radius * item.e.cylinder.radius;
	if (ft_get_next_line(fd, &line) == 1 && line)
		item.e.cylinder.height = ft_atof(line);
	else
		ft_print_error("cylinder height :)");
	item.e.cylinder.v = ft_vec3_normalized(ft_vec3_read(fd));
	item.material = ft_material_read(fd);
	return (ft_object_new(CYLINDRE, &item));
}

t_object		*ft_plane_read(int fd)
{
	t_object	item;

	item.pos = ft_vec3_read(fd);
	item.name = "PLANE";
	item.translate = ft_vec3_read(fd);
	item.rotate = ft_vec3_read(fd);
	item.translate = ft_translate_vec3(item.translate, item.pos, 0);
	item.pos = (t_vec3){0.0, 0.0, 0.0};
	item.e.plane.normal = ft_vec3_read(fd);
	item.material = ft_material_read(fd);
	return (ft_object_new(PLANE, &item));
}

t_object		*ft_ring_read(int fd)
{
	char		*line;
	t_object	item;

	item.name = "RING";
	item.pos = ft_vec3_read(fd);
	item.translate = ft_vec3_read(fd);
	item.rotate = ft_vec3_read(fd);
	item.translate = ft_translate_vec3(item.translate, item.pos, 0);
	item.pos = (t_vec3){0.0, 0.0, 0.0};
	if (ft_get_next_line(fd, &line) == 1 && line)
		item.e.ring.radius = ft_atof(line);
	else
		ft_print_error("ring radius :)");
	item.e.ring.radius2 = item.e.ring.radius * item.e.ring.radius;
	if (ft_get_next_line(fd, &line) == 1 && line)
		item.e.ring.height = ft_atof(line);
	else
		ft_print_error("ring height :)");
	item.e.ring.v = ft_vec3_normalized(ft_vec3_read(fd));
	item.material = ft_material_read(fd);
	return (ft_object_new(RING, &item));
}


t_object		*ft_disk_read(int fd)
{
	t_object	item;
	char		*line;

	item.name = "DISQUE";
	item.pos = ft_vec3_read(fd);
	item.translate = ft_vec3_read(fd);
	item.translate = ft_translate_vec3(item.translate, item.pos, 0);
	item.pos = (t_vec3){0.0, 0.0, 0.0};
	item.rotate = ft_vec3_read(fd);
	if (ft_get_next_line(fd, &line) == 1 && line)
		item.e.disk.radius = ft_atof(line);
	else
		ft_print_error("disk radius :)");
	item.e.disk.radius = item.e.disk.radius * item.e.disk.radius;
	item.e.disk.normal = ft_vec3_read(fd);
	item.material = ft_material_read(fd);
	return (ft_object_new(DISK, &item));
}
