/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 06:57:50 by ebatchas          #+#    #+#             */
/*   Updated: 2019/09/21 21:21:08 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

t_camera	ft_parsed_camera(char **str)
{
	int				i;
	t_camera		cam;

	cam.rot = (t_vec3){.0, .0, .0};
	cam.pos = (t_vec3){.0, .0, 10.0};
	cam.fov = 60.0;
	i = -1;
	while (str[++i])
	{
		if (ft_rtstrequal("POS", str[i]) || ft_rtstrequal("POSITION", str[i]) ||
				ft_rtstrequal("ORIGINE", str[i]) || ft_rtstrequal("LOOK_FROM",
					str[i]))
			cam.pos = ft_vec3_read(str[i]);
		else if (ft_rtstrequal("AT", str[i]) || ft_rtstrequal("LOOK_AT", str[i])
				|| ft_rtstrequal("FRONT", str[i]) || ft_rtstrequal("DIR",
					str[i]))
			cam.rot = ft_vec3_read(str[i]);
		else if (ft_rtstrequal("FOV", str[i]) || ft_rtstrequal("ANGLE", str[i]))
			cam.fov = ft_float_read(str[i]);
	}
	return (ft_camera_new(cam.pos, cam.rot, ft_vec3(0.0, 1.0, 0.0), cam.fov));
}

int			ft_parse_process_camera(t_scene *s, char *str)
{
	t_rtsplit		split;

	if (ft_strstr(ft_strsub(str, 0, CAMERA_NAME), "CAMERA"))
	{
		split = ft_parse_process_split(str, '{', '}', '\n');
		if (!split.tab)
			ft_parsing_error(CAMERA_DESCRIPTION);
		s->cam = ft_parsed_camera(split.tab);
		ft_split_free(&split.tab);
		return (split.max);
	}
	return (0);
}
