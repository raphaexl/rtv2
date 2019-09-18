/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:50:25 by ebatchas          #+#    #+#             */
/*   Updated: 2019/09/17 09:33:57 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

t_vec3		ft_random_unit_disk(void);

t_vec3		ft_random_unit_disk(void)
{
	t_vec3	p;

	p = (t_vec3){1.0, 1.0, 1.0};
	while (p.x * p.x + p.y * p.y + p.z * p.z  >= 1.0)
	{
		p = ft_vec3_sub(ft_vec3_kmult(2.0,
					ft_vec3(ft_rand48(), ft_rand48(), 0.0)),
				ft_vec3(1.0, 1.0, 0.0));
	}
	return (p);
}


t_camera	ft_camera_new(t_vec3 eye, t_vec3 at, t_vec3 up, float a)
{
	t_camera	cam;

	cam.rot = (t_vec3){0.0, 0.0, 0.0};
	cam.trans = (t_vec3){0.0, 0.0, 0.0};
	cam.aperture = 0.20;
	cam.focus_dist = ft_vec3_norm(ft_vec3_sub(at, eye));
	cam.lens_radius = cam.aperture / 2.0;
	cam.ratio = (float)W_W / (float)W_H;
	cam.pos = eye;
	cam.fov = a;
	cam.h = tan((cam.fov * M_PI * (1.0 / 180.0)) / 2.0);
	cam.w = cam.ratio * cam.h;
	cam.dir = ft_vec3_normalized(ft_vec3_sub(eye, at));
	cam.u = ft_vec3_normalized(ft_vec3_cross(up, cam.dir));
	cam.v = ft_vec3_cross(cam.dir, cam.u);
	cam.low_left = ft_vec3_sub(cam.pos, ft_vec3_sum(ft_vec3_kmult(cam.h * cam.focus_dist,
					cam.v), ft_vec3_kmult(cam.w * cam.focus_dist, cam.u)));
	cam.low_left = ft_vec3_sub(cam.low_left, ft_vec3_kmult(cam.focus_dist, cam.dir));
	cam.horiz = ft_vec3_kmult(2.0 * cam.w * cam.focus_dist, cam.u);
	cam.vert = ft_vec3_kmult(2.0 * cam.h * cam.focus_dist, cam.v);
	return (cam);
}

t_ray		ft_camera_ray(t_camera *cam, float x, float y)
{
	t_ray		r;
	t_vec3		tmp;
//	t_vec3		rd;
//	t_vec3		offset;

	tmp = ft_vec3_sum(cam->low_left, ft_vec3_kmult((x + 0.5) / (float)W_W,
				cam->horiz));
	tmp = ft_vec3_sum(tmp, ft_vec3_kmult((y + 0.5) / (float)W_H,
				cam->vert));
	//rd = ft_vec3_kmult(cam->lens_radius, ft_random_unit_disk());
	//offset = ft_vec3_sum(ft_vec3_kmult(rd.x, cam->u), ft_vec3_kmult(rd.y, cam->v));
	//r.start = ft_vec3_sum(offset, cam->pos);
	//r.dir = ft_vec3_normalized(ft_vec3_sub(tmp, ft_vec3_sum(offset, r.start)));
	r.start = cam->pos;
	r.dir = ft_vec3_normalized(ft_vec3_sub(tmp, r.start));
	return (r);
}

void		ft_camera_transform(t_camera *cam)
{
	cam->pos = ft_translate_vec3(cam->pos, cam->trans, -1);
	cam->dir = ft_vec3_normalized(ft_rotate_vec3(cam->dir, cam->rot, -1));
	cam->u = ft_vec3_normalized(ft_vec3_cross(ft_rotate_vec3(ft_vec3(0.0, 1.0, 0.0), 
					cam->rot, -1), cam->dir));
	cam->v = ft_vec3_cross(cam->dir, cam->u);
	cam->low_left = ft_vec3_sub(cam->pos,
			ft_vec3_sum(ft_vec3_kmult(cam->h ,
					cam->v), ft_vec3_kmult(cam->w , cam->u)));
	cam->low_left = ft_vec3_sub(cam->low_left, cam->dir);
	cam->horiz = ft_vec3_kmult(2.0 * cam->w, cam->u);
	cam->vert = ft_vec3_kmult(2.0 * cam->h, cam->v);
	cam->rot = (t_vec3){0.0, 0.0, 0.0};
	cam->trans = (t_vec3){0.0, 0.0, 0.0};
}
