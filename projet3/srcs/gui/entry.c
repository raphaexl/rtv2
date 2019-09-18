/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 21:13:11 by ebatchas          #+#    #+#             */
/*   Updated: 2019/08/02 19:09:15 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

t_entry	ft_entry_new(t_ptr *ptr, Uint32 c, Uint32 c2, const char *m)
{
	t_entry	 w;
	SDL_Surface *surf;

	w.color = c;
	w.color2 = c2;
	w.mes = ft_strdup(m);
	w.focus = SDL_FALSE;
	w.x = SCR_WIDTH / 2;
	w.y = SCR_HEIGHT / 2;
	w.ft_mouse_on_entry = &ft_mouse_on_entry;
	w.pos[0] = (SDL_Rect){0, 0, DEFAULT_W, DEFAULT_H};
	w.pos[1] = (SDL_Rect){0, 0, DEFAULT_W - 10, DEFAULT_H - 10};
	if (!(surf = SDL_CreateRGBSurface(0, DEFAULT_W, DEFAULT_H, 32, RMASK, GMASK, BMASK, AMASK)))
		ft_print_error("Creating entry 's Surface");
	if (SDL_FillRect(surf, &w.pos[0], w.color))
		ft_print_error("Error Coloruring the rect surface");
	if (!(w.img = SDL_CreateTextureFromSurface(ptr->renderer, surf)))
		ft_print_error("Creating entry 's Texture");
   SDL_FreeSurface(surf);
   surf = NULL;
	if (!(surf = SDL_CreateRGBSurface(0, DEFAULT_W - 10, DEFAULT_H - 10, 32, RMASK, GMASK, BMASK, AMASK)))
		ft_print_error("Creating entry 's Surface");
	if (SDL_FillRect(surf, &w.pos[1], 0xFFFFFFFF))
		ft_print_error("Error Coloruring the rect surface");
	if (!(w.lab = SDL_CreateTextureFromSurface(ptr->renderer, surf)))
		ft_print_error("Creating entry 's Texture");
   SDL_FreeSurface(surf);
   surf = NULL;
   return (w);
}

t_entry	*ft_entry_create(t_ptr *ptr, Uint32 c, Uint32 c2, const char *m)
{
	t_entry *w;
	SDL_Surface *surf;

	if (!(w = (t_entry *)malloc(sizeof(*w))))
		ft_print_error("Error malloc on creating entry's component !");
	w->focus = SDL_FALSE;
	w->color = c;
	w->color2 = c2;
	w->ft_mouse_on_entry = &ft_mouse_on_entry;
	w->x = SCR_WIDTH / 2;
	w->y = SCR_HEIGHT / 2;
	w->mes = ft_strdup(m);
	w->pos[0] = (SDL_Rect){0, 0, DEFAULT_W, DEFAULT_H};
	w->pos[1] = (SDL_Rect){0, 0, DEFAULT_W - 10, DEFAULT_H - 10};
	if (!(surf = SDL_CreateRGBSurface(0, DEFAULT_W, DEFAULT_H, 32, RMASK, GMASK, BMASK, AMASK)))
		ft_print_error("Creating entry 's Surface");
	if (SDL_FillRect(surf, &w->pos[0], w->color))
		ft_print_error("Error Coloruring the rect surface");
	if (!(w->img = SDL_CreateTextureFromSurface(ptr->renderer, surf)))
		ft_print_error("Creating entry 's Texture");
   SDL_FreeSurface(surf);
   surf = NULL;
	if (!(surf = SDL_CreateRGBSurface(0, DEFAULT_W - 10, DEFAULT_H - 10, 32, RMASK, GMASK, BMASK, AMASK)))
		ft_print_error("Creating entry 's Surface");
	if (SDL_FillRect(surf, &w->pos[1], 0xFFFFFFFF))
		ft_print_error("Error Coloruring the rect surface");
	if (!(w->lab = SDL_CreateTextureFromSurface(ptr->renderer, surf)))
		ft_print_error("Creating entry 's Texture");
   SDL_FreeSurface(surf);
   surf = NULL;
   return (w);
}

void		ft_entry_clean(t_entry *b)
{
	if (b->img)
		SDL_DestroyTexture(b->img);
	if (b->tex)
		SDL_DestroyTexture(b->tex);
	if (b->lab)
		SDL_DestroyTexture(b->lab);
	//free(b);
}

void	ft_entry_process(t_entry *w, t_input *in)
{
	if (ft_mouse_on_entry(w, in->mousex, in->mousey))
		ft_putendl("Yes");
}

void	ft_entry_draw(t_ptr *ptr, t_entry *w, int x, int y)
{
	SDL_Rect 		dest;
	SDL_Rect		pos;

	w->x = x;
	w->y = y;
	dest = (SDL_Rect){x, y, w->pos[0].w, w->pos[0].h};
	pos = (SDL_Rect){0, 0, w->pos[0].w, w->pos[0].h};
	SDL_RenderCopy(ptr->renderer, w->img, NULL, &dest);
	dest = (SDL_Rect){x + w->pos[0].w / 2 - w->pos[1].w / 2,
	y + w->pos[0].h / 2 - w->pos[1].h / 2, w->pos[1].w, w->pos[1].h};
	SDL_RenderCopy(ptr->renderer, w->lab, NULL, &dest);
	if (!ft_strlen(w->mes))
		return ;
	if (!(w->tex = ft_get_render_text(ptr->renderer, ft_font(w->mes, DEFAULT_FONT, DEFAULT_FSIZE),
					ft_sdl_color(w->color2))))
		ft_print_error("Error entry text rendering ");
	if (SDL_QueryTexture(w->tex, NULL, NULL, &pos.w, &pos.h))
		ft_print_error("Error SDL_QueryTexture :");
	dest = (SDL_Rect){dest.x + w->pos[1].w / 2 - pos.w / 2,
	dest.y + w->pos[1].h / 2 - pos.h / 2, pos.w, pos.h};
	SDL_RenderCopy(ptr->renderer, w->tex, &pos, &dest);
	SDL_DestroyTexture(w->tex);
	w->tex = NULL;
}

int		ft_mouse_on_entry(t_entry *w, int x, int y)
{
	if ((x < w->x) || (x > w->x + w->pos[0].w) || (y < w->y) || (y > w->y + w->pos[0].h))
		return (0);
	return (1);
}
