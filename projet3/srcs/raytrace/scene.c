/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:58:12 by ebatchas          #+#    #+#             */
/*   Updated: 2019/09/18 05:50:47 by ebatchas         ###   ########.fr       */
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
	s->earth = ft_texture_new("data/imgs/earth.jpg");
	s->img[0] = ft_texture_new("data/imgs/envmap.jpg");
	s->ft_bg_color = ft_background_image;
	//write(1, "Passed\n", 8);
	s->filter = NOFILTER;
	char	*m[6] = {
		"data/envmaps/cube/massal/alpup.tga",
		"data/envmaps/cube/massal/alpdown.tga",
		"data/envmaps/cube/massal/alpright.tga",
		"data/envmaps/cube/massal/alpleft.tga",
		"data/envmaps/cube/massal/alpforward.tga",
		"data/envmaps/cube/massal/alpback.tga"
	};
	char 	*m1[6] = {
		"data/envmaps/cube/mp_portal/portal_up.tga",
		"data/envmaps/cube/mp_portal/portal_dn.tga",
		"data/envmaps/cube/mp_portal/portal_rt.tga",
		"data/envmaps/cube/mp_portal/portal_lf.tga",
		"data/envmaps/cube/mp_portal/portal_ft.tga",
		"data/envmaps/cube/mp_portal/portal_bk.tga"
	};
	s->cmap = ft_cubemap_init(m);
	s->ft_rtv1 = ft_ray_trace;
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
