/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:53:03 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/02 21:27:10 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

static int	ft_camera_rotate(t_camera *cam, t_input *in)
{
	int		ret;

	ret = 0;
	if (in->keys[SDL_SCANCODE_W] && (ret = 1))
		cam->rot.x += 5.212;
	else if (in->keys[SDL_SCANCODE_S] && (ret = 1))
		cam->rot.x -= 5.212;
	else if (in->keys[SDL_SCANCODE_Q] && (ret = 1))
		cam->rot.z += 5.212;
	else if (in->keys[SDL_SCANCODE_E] && (ret = 1))
		cam->rot.z -= 5.212;
	else if (in->keys[SDL_SCANCODE_LEFT] && (ret = 1))
		cam->rot.y += 5.212;
	else if (in->keys[SDL_SCANCODE_RIGHT] && (ret = 1))
		cam->rot.y -= 5.212;
	return (ret);
}

int			ft_env_update_camera(t_camera *cam, t_input *in)
{
	int		ret;

	ret = 0;
	ret = ft_camera_rotate(cam, in);
	if (in->keys[SDL_SCANCODE_Z] && (ret = 1))
		cam->trans = ft_vec3_sum(cam->trans, ft_vec3_kmult(-2.5, cam->v));
	if (in->keys[SDL_SCANCODE_X] && (ret = 1))
		cam->trans = ft_vec3_sum(cam->trans, ft_vec3_kmult(2.5, cam->v));
	if (in->keys[SDL_SCANCODE_A] && (ret = 1))
		cam->trans = ft_vec3_sum(cam->trans, ft_vec3_kmult(-2.5, cam->u));
	if (in->keys[SDL_SCANCODE_D] && (ret = 1))
		cam->trans = ft_vec3_sum(cam->trans, ft_vec3_kmult(2.5, cam->u));
	if (in->keys[SDL_SCANCODE_UP] && (ret = 1))
		cam->trans = ft_vec3_sum(cam->trans, ft_vec3_kmult(2.5, cam->dir));
	if (in->keys[SDL_SCANCODE_DOWN] && (ret = 1))
		cam->trans = ft_vec3_sum(cam->trans, ft_vec3_kmult(-2.5, cam->dir));
	ft_camera_transform(cam);
	return (ret);
}

void		ft_object_resize(t_object **s, float rev)
{
	if ((*s) && ((*s)->type == SPHERE))
	{
		(*s)->e.sphere.radius = ft_clamp(0.5, 1000.0, rev * (*s)->e.sphere.radius);
		(*s)->e.sphere.radius2 = (*s)->e.sphere.radius * (*s)->e.sphere.radius;
	}
		if ((*s) && (*s)->type == DISK)
		{
		(*s)->e.disk.radius = ft_clamp(0.5, 1000.0, rev * (*s)->e.disk.radius);
		(*s)->e.disk.radius2 = (*s)->e.disk.radius * (*s)->e.disk.radius;
		}
			if ((*s) && (*s)->type == CYLINDRE)
		{
		(*s)->e.cylinder.radius = ft_clamp(0.5, 1000.0, rev * (*s)->e.cylinder.radius);
		(*s)->e.cylinder.radius2 = (*s)->e.cylinder.radius * (*s)->e.cylinder.radius;
		}
	else if ((*s) && (*s)->type == CONE)
		(*s)->e.cone.angle = ft_clamp(M_PI / 180.0, M_PI / 2.0 - 0.1,
				rev * (*s)->e.cone.angle);
	else if ((*s) && (*s)->type == BOX)
		(*s)->scale = ft_vec3_kmult(rev, (*s)->scale);
	else if ((*s) && (*s)->type == TORUS)
	{
		(*s)->e.torus.radius1 = ft_clamp(0.5, 1000.0, rev * (*s)->e.torus.radius1);
		(*s)->e.torus.radius2 = ft_clamp(0.1, 10.0, rev * (*s)->e.torus.radius2);
	}
	else if ((*s) && (*s)->type == CUBE)
		(*s)->e.cube.radius = ft_clamp(8.5, 15.0, (*s)->e.cube.radius +
				(rev < 1.01f ? 0.5 : -0.5));
}

void		ft_env_select_object(t_env *e, int x, int y)
{
	t_intersect	inter;
	int			start_x;
	int			start_y;

	start_x = START_X;
	start_y = START_Y;
	e->selected = NULL;
	if (x < START_X || x > END_X)
		return ;
	if (y < START_Y || y > END_Y)
		return ;
	inter.ray = ft_camera_ray(&e->s.cam, x - start_x, W_H - (y - start_y));
	inter.t = INFINITY;
	if (ft_scene_intersect(&e->s, &inter))
		e->selected = inter.current;
}

int			ft_prev_update(t_env *e, t_input *in)
{
	int		r;

	r = 0;
	if (in->mouse[SDL_BUTTON_RIGHT] && in->keys[SDL_SCANCODE_LCTRL] && (r = 1))
		ft_env_select_object(e, in->mousex, in->mousey);
	if (in->keys[SDL_SCANCODE_R] && in->keys[SDL_SCANCODE_KP_MINUS] && (r = 1))
		e->selected->material.diffuse.red -= 0.1;
	else if (in->keys[SDL_SCANCODE_G] && in->keys[86] && (r = 1))
		e->selected->material.diffuse.green -= 0.1;
	else if (in->keys[SDL_SCANCODE_B] && in->keys[86] && (r = 1))
		e->selected->material.diffuse.blue -= 0.1;
	else if (in->keys[SDL_SCANCODE_R] && in->keys[87] && (r = 1))
		e->selected->material.diffuse.red += 0.1;
	else if (in->keys[SDL_SCANCODE_G] && in->keys[87] && (r = 1))
		e->selected->material.diffuse.green += 0.1;
	else if (in->keys[SDL_SCANCODE_B] && in->keys[87] && (r = 1))
		e->selected->material.diffuse.blue += 0.1;
	else if (in->keys[SDL_SCANCODE_KP_MINUS] && (r = 1))
		e->s.nb_samples = (int)ft_clamp(1.0, 100.0, e->s.nb_samples - 4.0);
	else if (in->keys[SDL_SCANCODE_KP_PLUS] && (r = 1))
		e->s.nb_samples = (int)ft_clamp(1.0, 100.0, e->s.nb_samples + 4.0);
	else if (in->keys[SDL_SCANCODE_O] && (r = 1))
		e->optimize = !(e->optimize);
	return (r);
}
