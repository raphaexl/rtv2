/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:58:12 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/26 09:53:00 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

void				ft_scene_init(t_scene *s, char *const input_file)
{
	int		fd;

	s->obj = NULL;
	s->light = NULL;
	if ((fd = open(input_file, O_RDONLY)) && fd > 0)
	{
		s->cam = ft_camera_new(ft_vec3(0.0f, 0.0f, 0.0f),
				ft_vec3(0.0f, 0.0f, -1.0f), ft_vec3(0.0, 1.0, 0.0),
				60.0);
		s->nb_samples = 1.0;
		s->bg_color = (t_col3){0.0, 0.0, 0.0};
		s->ambiant = (t_col3){0.02, 0.02, 0.02};
		ft_parse_file(s, fd);
		close(fd);
		if (!s->obj)
			ft_print_error("missing  objects :)");
	}
	else
		ft_error();
	s->c = (t_col3){.0, .0, .0};
	s->a = 0;
	//s->earth = ft_texture_new("/Users/ebatchas/Desktop/brick1.png");
	s->earth = ft_texture_new("data/imgs/earth.jpg");
	s->img[0] = ft_texture_new("data/imgs/envmap.jpg");
	s->ft_bg_color = ft_background_image;
	write(1, "Passed\n", 8);
	s->filter = ft_filter_new(5, 5, EMBOSS2);
	s->ft_rtv1 = ft_edit_trace;
}

void				ft_scene_clear(t_scene *s)
{
	ft_texture_clean(&s->earth);
	ft_object_clean(&s->obj);
	s->obj = NULL;
	ft_light_clean(&s->light);
	s->light = NULL;
	s = NULL;
}
