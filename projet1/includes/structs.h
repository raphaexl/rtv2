/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 21:53:37 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/03 16:14:07 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
# define B_ENDIAN 1
# define RMASK 0xFF000000
# define GMASK 0x00FF0000
# define BMASK 0x0000FF00
# define AMASK 0x000000FF
# else
# define B_ENDIAN 0
# define RMASK 0x000000FF
# define GMASK 0x0000FF00
# define BMASK 0x00FF0000
# define AMASK 0xFF000000
# endif
# include <time.h>
# include "SDL2/SDL_image.h"
# include "SDL2/SDL_ttf.h"
# include "SDL2/SDL_thread.h"
# include "raytrace.h"

typedef struct		s_input
{
	t_itype		mode;
	char		*text;
	int			render_text;
	int			quit;
	int			focus;
	int			mousex;
	int			mousey;
	int			mousexrel;
	int			mouseyrel;
	int			ywheel;
	int			mouse[6];
	int			keys[SDL_NUM_SCANCODES];
}					t_input;

typedef struct		s_menu
{
	SDL_Rect		pos[NB_OPTIONS];
	SDL_Texture		*img[NB_OPTIONS];
	int				keys[NB_OPTIONS];
}					t_menu;

typedef	struct		s_ptr
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
}					t_ptr;


typedef struct		s_widget
{
	Uint32			color;
	SDL_Rect		pos;
	SDL_Texture		*img;
	int				(*ft_mouse_on_widget)(struct s_widget *w, int x, int y);
}					t_widget;

typedef struct		s_button
{
	Uint32			color;
	Uint32			color2;
	SDL_Rect		pos[2];
	SDL_Texture		*img;
	SDL_Texture		*tex;
	int				(*ft_mouse_on_button)(struct s_button *b, int x, int y);
}					t_button;

typedef struct		s_entry
{
	int				x;
	int				y;
	int				focus;
	Uint32			color;
	Uint32			color2;
	SDL_Rect		pos[2];
	SDL_Texture		*img;
	SDL_Texture		*lab;
	SDL_Texture		*tex;
	char			*mes;
	int				(*ft_mouse_on_entry)(struct s_entry *e, int x, int y);
}					t_entry;

typedef struct		s_view
{
	t_button		b;
	t_entry			e;
}					t_view;

typedef struct		s_view2
{
	t_button		b;
	t_entry			e[2];
}					t_view2;

typedef struct		s_view3
{
	t_button		b;
	t_entry			e[3];
}					t_view3;

typedef struct		s_view4
{
	t_button		b;
	t_entry			e[4];
}					t_view4;

typedef struct		s_inspector
{
	t_view4			v4[N_VIEW4];
	t_view3			v3[N_PROPERTIES];
	t_view			v1[N_VIEW1];
}					t_inspector;

typedef	struct		s_env
{
	t_scene			s;
	t_menu			menu;
	t_ptr			ptr;
	t_input			in;
	Uint32			*pixels;
	int				optimize;
	int				start;
	t_object		*selected;
	t_inspector		inspector;
}					t_env;
#endif
