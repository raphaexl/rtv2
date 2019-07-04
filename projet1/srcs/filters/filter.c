/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 20:10:38 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/02 14:43:00 by ebatchas         ###   ########.fr       */
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


void		ft_filter_apply(t_filter *f, Uint32	*pixels)
{
	int		x;
	int		y;
	t_col3	c;
	float	a;

	x = -1;
	c = (t_col3){0.0, 0.0, 0.0};
	while (++x < W_W)
	{
		y = -1;
		while (++y < W_H)
		{
			c.red = 0xFF - ((pixels[y * W_W + x] >> 24) & 0xFF);	
			c.green = 0xFF - ((pixels[y * W_W + x] >> 16) & 0xFF);	
			c.blue = 0xFF - ((pixels[y * W_W + x] >> 8) & 0xFF) ;
			a = (pixels[y * W_W + x] & 0xFF);
			pixels[y * W_W + x] = ft_rgb_to_int(ft_clamp(c.red * f->factor + f->bias, 0, 255),
					ft_clamp(c.green * f->factor + f->bias, 0, 255),
					ft_clamp(c.blue * f->factor + f->bias, 0, 255),
					ft_clamp(a * f->factor + f->bias, 0, 255));
			/*	pixels[y * W_W + x] = ft_rgb_to_int(MIN(MAX((int)(f->factor * c.red + f->bias), 0), 255),
				MIN(MAX( (int)(f->factor * c.green + f->bias), 0), 255),
				MIN(MAX((int)(f->factor * c.blue + f->bias), 0), 255),
				MIN(MAX((int)(f->factor * a + f->bias), 0), 255));*/
		}
	}
}


/*
   void		ft_filter_apply(t_filter *f, Uint32	*pixels)
   {
   int		x;
   int		y;
   t_col3	c;
   float	a;
   int		x1, y1;
   int		imgx, imgy;

   x = -1;
   c = (t_col3){0.0, 0.0, 0.0};
   while (++x < W_W)
   {
   y = -1;
   while (++y < W_H)
   {
   c = (t_col3){0.0, 0.0, 0.0};
   a = 0.0f;
   y1 = -1;
   while (++y1 < f->h)
   {
   x1 = -1;
   while (++x1 < f->w)
   {
   imgx = (x - f->w / 2 + x1 + W_W) % W_W;
   imgy = (y - f->h / 2 + y1 + W_H) % W_H;
   c.red += ((pixels[imgy * W_W + imgx] >> 24) & 0xFF) * f->filter[y1][x1];	
   c.green += ((pixels[imgy * W_W + imgx] >> 16) & 0xFF)  * f->filter[y1][x1];	
   c.blue += ((pixels[imgy * W_W + imgx] >> 8) & 0xFF) * f->filter[y1][x1];
   a += (pixels[imgy * W_W + imgx] & 0xFF) * f->filter[y1][x1];
   }
   }
//printf("red = %.2f\tgreen = %.2f\tblue = %.2f alpha = %.2f\n", c.red, c.green, c.blue, a); 
pixels[y * W_W + x] = ft_rgb_to_int(ft_clamp(c.red * f->factor + f->bias, 0, 255),
ft_clamp(c.green * f->factor + f->bias, 0, 255),
ft_clamp(c.blue * f->factor + f->bias, 0, 255),
ft_clamp(a * f->factor + f->bias, 0, 255));
//pixels[y * W_W + x] = ft_rgb_to_int(fmin(c.red , 255), fmin(255, c.green), fmin(c.blue, 255), fmin(255, a));
	pixels[y * W_W + x] = ft_rgb_to_int(MIN(MAX((int)(f->factor * c.red + f->bias), 0), 255),
MIN(MAX( (int)(f->factor * c.green + f->bias), 0), 255),
MIN(MAX((int)(f->factor * c.blue + f->bias), 0), 255),
MIN(MAX((int)(f->factor * a + f->bias), 0), 255));
}
}
}*/
