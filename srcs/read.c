/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 08:53:45 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/17 14:10:08 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_object		*ft_sphere_read(int fd)
{
	char		*line;
	t_object	iterm;

	iterm.pos = ft_vec3_read(fd);
	iterm.translate = ft_vec3_read(fd);
	iterm.rotate = ft_vec3_read(fd);
	iterm.normal = ft_vec3(0.0, 0.0, 0.0);
	if (ft_get_next_line(fd, &line) == 1 && line)
		iterm.radius = ft_atof(line);
	else
		ft_print_error("sphere radius :)");
	iterm.angle = iterm.radius * iterm.radius;
	iterm.material = ft_material_read(fd);
	return (ft_object_new(SPHERE, &iterm));
}

t_object		*ft_cone_read(int fd)
{
	char		*line;
	t_object	iterm;

	iterm.pos = ft_vec3_read(fd);
	iterm.translate = ft_vec3_read(fd);
	iterm.rotate = ft_vec3_read(fd);
	iterm.normal = ft_vec3(0.0, 0.0, 0.0);
	if (ft_get_next_line(fd, &line) == 1 && line)
		iterm.angle = DEG_TO_RAD(ft_clamp(1.0, 189.0, ft_atof(line)));
	else
		ft_print_error("cone angle :)");
	iterm.material = ft_material_read(fd);
	return (ft_object_new(CONE, &iterm));
}

t_object		*ft_cylindre_read(int fd)
{
	char		*line;
	t_object	iterm;

	iterm.pos = ft_vec3_read(fd);
	iterm.translate = ft_vec3_read(fd);
	iterm.rotate = ft_vec3_read(fd);
	iterm.normal = ft_vec3(0.0, 0.0, 0.0);
	if (ft_get_next_line(fd, &line) == 1 && line)
		iterm.radius = ft_atof(line);
	else
		ft_print_error("cylinder radius :)");
	iterm.angle = iterm.radius * iterm.radius;
	iterm.material = ft_material_read(fd);
	return (ft_object_new(CYLINDRE, &iterm));
}

t_object		*ft_plane_read(int fd)
{
	t_object	iterm;

	iterm.pos = ft_vec3_read(fd);
	iterm.translate = ft_vec3_read(fd);
	iterm.rotate = ft_vec3_read(fd);
	iterm.radius = 0.0;
	iterm.angle = 0.0;
	iterm.normal = ft_vec3_read(fd);
	iterm.material = ft_material_read(fd);
	return (ft_object_new(PLANE, &iterm));
}

t_object		*ft_disk_read(int fd)
{
	t_object	iterm;
	char		*line;

	iterm.pos = ft_vec3_read(fd);
	iterm.translate = ft_vec3_read(fd);
	iterm.rotate = ft_vec3_read(fd);
	if (ft_get_next_line(fd, &line) == 1 && line)
		iterm.radius = ft_atof(line);
	else
		ft_print_error("disk radius :)");
	iterm.angle = iterm.radius * iterm.radius;
	iterm.normal = ft_vec3_read(fd);
	iterm.material = ft_material_read(fd);
	return (ft_object_new(DISK, &iterm));
}

t_object		*ft_box_read(int fd)
{
	t_object	iterm;

	iterm.pos = ft_vec3_read(fd);
	iterm.normal = ft_vec3_read(fd);
	iterm.translate = ft_vec3_read(fd);
	iterm.rotate = ft_vec3_read(fd);
	iterm.radius = 0.0; 
	iterm.angle = 0.0;
	iterm.material = ft_material_read(fd);
	return (ft_object_new(BOX, &iterm));
}

t_object		*ft_torus_read(int fd)
{
	t_object	iterm;
	char		*line;

	iterm.pos = ft_vec3_read(fd);
	iterm.translate = ft_vec3_read(fd);
	iterm.rotate = ft_vec3_read(fd);
	if (ft_get_next_line(fd, &line) == 1 && line)
		iterm.radius = ft_atof(line);
	else
		ft_print_error("torus Radius :)");
	if (ft_get_next_line(fd, &line) == 1 && line)
		iterm.angle = ft_atof(line);
	else
		ft_print_error("torus radius :)");
	iterm.normal = (t_vec3){0.0, 0.0, 0.0}; 
	iterm.material = ft_material_read(fd);
	return (ft_object_new(TORUS, &iterm));
}

t_light			*ft_light_read(int fd)
{
	char		*line;
	char		**tab;
	t_iterm		iterm;
	int			i;

	if (ft_get_next_line(fd, &line) == 1 && line)
	{
		if ((tab = ft_strsplit(line, ' ')) && ft_tab_len(tab) != 6)
			ft_print_error("invalid light paramters");
		iterm.pos.x = ft_atof(tab[0]);
		iterm.pos.y = ft_atof(tab[1]);
		iterm.pos.z = ft_atof(tab[2]);
		iterm.col3.red = ft_atof(tab[3]);
		iterm.col3.green = ft_atof(tab[4]);
		iterm.col3.blue = ft_atof(tab[5]);
		i = -1;
		while (++i < 6)
			free(tab[i]);
		free(tab);
		tab = NULL;
	}
	else
		ft_print_error("light invalid :)");
	return (ft_light_new(iterm.pos, iterm.col3));
}
