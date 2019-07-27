/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:53:03 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/04 22:03:11 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

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
	ft_inspector_object(&e->inspector, e->selected);
}

int			ft_prev_update(t_env *e, t_input *in)
{
	int		r;

	r = 0;
	if (in->mouse[SDL_BUTTON_RIGHT] && in->keys[SDL_SCANCODE_LCTRL] && (r = 1))
		ft_env_select_object(e, in->mousex, in->mousey);
	else if (ft_inspector_update_event(&e->inspector, in))
		r = 1;
	else if (ft_lview_update_event(&e->lview, in))
		r = 1;
	else if (ft_cview_update_event(&e->cview, in))
		r = 1;
	else if (in->keys[SDL_SCANCODE_R] && in->keys[SDL_SCANCODE_KP_MINUS] && (r = 1))
		e->s.bg_color.red = ft_clamp(0, 1.0, e->s.bg_color.red - 0.1);
	else if (in->keys[SDL_SCANCODE_G] && in->keys[SDL_SCANCODE_KP_MINUS] && (r = 1))
		e->s.bg_color.green = ft_clamp(0, 1.0, e->s.bg_color.green - 0.1);
	else if (in->keys[SDL_SCANCODE_B] && in->keys[SDL_SCANCODE_KP_MINUS] && (r = 1))
		e->s.bg_color.blue = ft_clamp(0, 1.0, e->s.bg_color.blue - 0.1);
	else if (in->keys[SDL_SCANCODE_R] && in->keys[SDL_SCANCODE_KP_PLUS] && (r = 1))
		e->s.bg_color.red = ft_clamp(0, 1.0, e->s.bg_color.red + 0.1);
	else if (in->keys[SDL_SCANCODE_G] && in->keys[SDL_SCANCODE_KP_PLUS] && (r = 1))
		e->s.bg_color.green = ft_clamp(0, 1.0, e->s.bg_color.green + 0.1);
	else if (in->keys[SDL_SCANCODE_B] && in->keys[SDL_SCANCODE_KP_PLUS] && (r = 1))
		e->s.bg_color.blue = ft_clamp(0, 1.0, e->s.bg_color.blue + 0.1);
	else if (in->keys[SDL_SCANCODE_KP_MINUS] && (r = 1))
		e->s.nb_samples = (int)ft_clamp(1.0, 100.0, e->s.nb_samples - 4.0);
	else if (in->keys[SDL_SCANCODE_KP_PLUS] && (r = 1))
		e->s.nb_samples = (int)ft_clamp(1.0, 100.0, e->s.nb_samples + 4.0);
	else if (in->keys[SDL_SCANCODE_O] && (r = 1))
		e->optimize = !(e->optimize);
	return (r);
}
