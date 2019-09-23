/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 22:29:42 by ebatchas          #+#    #+#             */
/*   Updated: 2019/09/22 20:07:58 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

t_object		*ft_parse_parallelogram(t_object *o, char **str)
{
	int		i;

	o->name = "PARALLELOGRAM";
	o->e.para.a = (t_vec3){-1.0, -1.0, 0.0};
	o->e.para.b = (t_vec3){1.0, -1.0, 0.0};
	o->e.para.c = (t_vec3){1.0, 1.0, 0.0};
	o->e.para.d = (t_vec3){-1.0, 1.0, 0.0};
	i = -1;
	while (str[++i])
	{
		if (ft_rtstrequal("POINTA", str[i]) || ft_rtstrequal("V1", str[i]))
			o->e.para.a = ft_vec3_read(str[i]);
		else if (ft_rtstrequal("POINTB", str[i]) ||
				ft_rtstrequal("V2", str[i]))
			o->e.para.b = ft_vec3_read(str[i]);
		else if (ft_rtstrequal("POINTC", str[i]) ||
				ft_rtstrequal("V3", str[i]))
			o->e.para.c = ft_vec3_read(str[i]);
		else if (ft_rtstrequal("POINTD", str[i]) ||
				ft_rtstrequal("V4", str[i]))
			o->e.para.d = ft_vec3_read(str[i]);
	}
	o->material = ft_material_read(str);
	return (ft_object_new(PARALLELOGRAM, o));
}

t_object		*ft_parse_mesh(t_object *o, char **str)
{
	int		i;

	o->name = "MESH";
	o->pos = ft_vec3(0.0, 0.0, 0.0);
	i = -1;
	o->e.mesh = ft_default_mesh();
	while (str[++i])
	{
		if (ft_rtstrequal("NAME", str[i]) || ft_rtstrequal("FILE", str[i]))
			ft_mesh_load(&o->e.mesh, ft_strlwr(ft_str_read(str[i])));
	}
	o->material = ft_material_read(str);
	return (ft_object_new(MESH, o));
}
