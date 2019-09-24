/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:53:03 by ebatchas          #+#    #+#             */
/*   Updated: 2019/09/24 12:50:47 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

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
	e->in.mode = EDITING;
}

static int	ft_pprev_update(t_env *e, t_input *in)
{
	if (in->mouse[SDL_BUTTON_RIGHT] && in->keys[SDL_SCANCODE_LCTRL])
	{
		ft_env_select_object(e, in->mousex, in->mousey);
		return (1);
	}
	else if (ft_inspector_update_event(&e->inspector, in))
		return (1);
	else if (ft_cview_update_event(&e->cview, in))
		return (1);
	return (0);
}

int			ft_prev_update(t_env *e, t_input *in)
{
	int		r;

	if ((r = ft_pprev_update(e, in)))
		return (1);
	else if (in->keys[SDL_R] && in->keys[SDL_SCANCODE_KP_MINUS] && (r = 1))
		e->s.bg_color.red = ft_clamp(0, 1.0, e->s.bg_color.red - 0.1);
	else if (in->keys[SDL_G] && in->keys[SDL_SCANCODE_KP_MINUS] && (r = 1))
		e->s.bg_color.green = ft_clamp(0, 1.0, e->s.bg_color.green - 0.1);
	else if (in->keys[SDL_B] && in->keys[SDL_SCANCODE_KP_MINUS] && (r = 1))
		e->s.bg_color.blue = ft_clamp(0, 1.0, e->s.bg_color.blue - 0.1);
	else if (in->keys[SDL_R] && in->keys[SDL_SCANCODE_KP_PLUS] && (r = 1))
		e->s.bg_color.red = ft_clamp(0, 1.0, e->s.bg_color.red + 0.1);
	else if (in->keys[SDL_G] && in->keys[SDL_SCANCODE_KP_PLUS] && (r = 1))
		e->s.bg_color.green = ft_clamp(0, 1.0, e->s.bg_color.green + 0.1);
	else if (in->keys[SDL_B] && in->keys[SDL_SCANCODE_KP_PLUS] && (r = 1))
		e->s.bg_color.blue = ft_clamp(0, 1.0, e->s.bg_color.blue + 0.1);
	else if (in->keys[SDL_SCANCODE_KP_MINUS] && (r = 1))
		e->s.nb_samples = (int)ft_clamp(1.0, 100.0, e->s.nb_samples - 4.0);
	else if (in->keys[SDL_SCANCODE_KP_PLUS] && (r = 1))
		e->s.nb_samples = (int)ft_clamp(1.0, 100.0, e->s.nb_samples + 4.0);
	else if (in->keys[SDL_SCANCODE_O] && (r = 1))
		e->optimize = !(e->optimize) ? 1 : 1;
	return (r);
}
