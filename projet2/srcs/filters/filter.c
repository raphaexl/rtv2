/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 20:10:38 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/27 09:39:44 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

static Uint32	ft_rgb_to_int(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
	return (a + (b << 8) + (g << 16) + (r << 24));
}

t_filter	*ft_filter_new(int w, int h, t_ftype type)
{
	t_filter	*new;
	int			i;

	if (!(new = (t_filter *)malloc(sizeof(t_filter))))
		ft_print_error("malloc error\n");
	new->w = w;
	new->h = h;
	if (!(new->filter = (float **)malloc(sizeof(float *) * new->h)))
		ft_print_error("malloc error\n");
	i = -1;
	while (++i < new->h)
		if (!(new->filter[i] = (float *)malloc(sizeof(float) * new->w)))
			ft_print_error("malloc error\n");
	new->type = type;
	if (new->type == CONVOLUTION)
		ft_filter_convolution(new);
	else if (new->type == BLUR)
		ft_filter_blur(new);
	else if (new->type == BLUR2)
		ft_filter_blur2(new);
	else if (new->type == GAUSSIAN_BLUR)
		ft_filter_gaussian_blur(new);
	else if (new->type == GAUSSIAN_BLUR2)
		ft_filter_gaussian_blur2(new);
	else if (new->type == MOTION_BLUR)
		ft_filter_motion_blur(new);
	else if (new->type == EDGE)
		ft_filter_edge(new);
	else if (new->type == EDGE2)
		ft_filter_edge2(new);
	else if (new->type == EDGE3)
		ft_filter_edge3(new);
	else if (new->type == SHARPEN)
		ft_filter_sharpen(new);
	else if (new->type == EMBOSS)
		ft_filter_emboss(new);
	else if (new->type == EMBOSS2)
		ft_filter_emboss2(new);
	else
		ft_print_error("error filtre !");
	return (new);
}

void		ft_filter_convolution(t_filter *f)
{
	f->filter[0][0] = 0.0;
	f->filter[0][1] = 0.0;
	f->filter[0][2] = 0.0;

	f->filter[1][0] = 0.0;
	f->filter[1][1] = 1.0;
	f->filter[1][2] = 0.0;

	f->filter[2][0] = 0.0;
	f->filter[2][1] = 0.0;
	f->filter[2][2] = 0.0;
	f->factor = 1.0;
	f->bias = 0.0;
	f->h = 3;
	f->w = 3;
}

t_col3		ft_convolute(t_filter *f, int x, int y, Uint32 *pixels)
{
	int		i;
	int		j;
	int		offset = f->w / 2;
	t_col3	c = (t_col3){0.0, 0.0, 0.0};

	i = -1;
	while (++i < f->h)
	{
		j = -1;
		while (++j < f->w)
		{
			int		xloc = y + i - offset;
			int		yloc = x + j - offset;
			int		loc = (int)ft_clamp(0, W_W * W_H, yloc + W_W * xloc);
			c.red += (((pixels[loc] >> 24) & 0xFF) * f->filter[i][j]);	
			c.green += (((pixels[loc] >> 16) & 0xFF) * f->filter[i][j]);	
			c.blue += (((pixels[loc] >> 8) & 0xFF) * f->filter[i][j]);
		}
	}
	/*c.red = ft_clamp(c.red, 0.0, 255.0);
	c.green = ft_clamp(c.green, 0.0, 255.0);
	c.blue = ft_clamp(c.blue, 0.0, 255.0);*/
//	return (ft_rgb_to_int(c.red, c.green, c.blue, 255));
	return (c);
}

void		ft_filter_apply(t_filter *f, Uint32	*pixels)
{
	int		x;
	int		y;
	t_col3	c;
	float	a;
	int		mousex, mousey;

	SDL_GetMouseState(&mousex, &mousey);
	mousex -= START_X;
	mousey -= START_Y;
	printf("x = %d\t y = %d\n", mousex, mousey);
	mousex = mousex > 0 ? mousex : 1;
	mousey = mousey > 0 ? mousey : 1;
	y = mousey - 1;
	c = (t_col3){0.0, 0.0, 0.0};
	while (++y < W_H / 4)
	{
		x = mousex - 1;
		while (++x < W_W / 4)
		{
			c = ft_convolute(f, x, y, pixels);
			a = (pixels[y * W_W + x] & 0xFF);
			pixels[y * W_W + x] = ft_rgb_to_int(ft_clamp(c.red * f->factor + f->bias, 0, 255),
					ft_clamp(c.green * f->factor + f->bias, 0, 255),
					ft_clamp(c.blue * f->factor + f->bias, 0, 255),
					ft_clamp(a * f->factor + f->bias, 0, 255));
		}
	}
	ft_putendl("Fine");
}
