/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 08:53:56 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/26 09:10:24 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

t_img	ft_load_img(SDL_Renderer *rend, const char *file_name)
{
	SDL_Surface		*s;
	int				x;
	int				y;
	t_img			img;

	s = IMG_Load(file_name);
	if (!s)
		ft_sdl_error();
//	SDL_SetColorKey(s, SDL_TRUE, SDL_MapRGB(s->format, 255, 255, 255));
	img.pixels = (Uint32 *)malloc(sizeof(Uint32) * (s->w * s->h));
	SDL_LockSurface(s);
	y = -1;
	while ((++y < s->h) && (x = -1))
		while (++x < s->w)
			img.pixels[y * s->w + x] = ft_get_pixels(s, x, y);
	SDL_UnlockSurface(s);
	img.width = s->w;
	img.height = s->h;
	if (!(img.img = SDL_CreateTextureFromSurface(rend, s)))
		ft_sdl_error();
	SDL_FreeSurface(s);
	return (img);
}

int		ft_env_texture_load(t_env *e)
{
		e->img[0] = ft_load_img(e->ptr.renderer, "data/imgs/lena_color.bmp");
		e->img[1] = ft_load_img(e->ptr.renderer, "data/imgs/nasa.png");
		e->img[2] = ft_load_img(e->ptr.renderer, "data/imgs/photo1.png");
		e->img[3] = ft_load_img(e->ptr.renderer, "data/imgs/photo3.png");
		return (0);
}
