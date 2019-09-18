/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubemap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 12:29:51 by ebatchas          #+#    #+#             */
/*   Updated: 2019/09/17 19:40:05 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

static void	ft_fill_cube(t_cubemap *cube, int  *index, t_texture *s)
{
	t_col3	c;
	int		i;
	int		j;
	Uint32	col;

	j = -1;
	while (++j < s->h)
	{
		i = -1;
		while (++i < s->w)
		{
			//col = s->data[j * s->w + i];
			col = s->data[(s->h - 1 - j) * s->w + i];
			c.red = (float)((col >> 16) & 0xFF) / 255.0;
			c.green = (float)((col >> 8) & 0xFF) / 255.0;
			c.blue = (float)(col & 0xFF) / 255.0;
			cube->texture[*index] = c;
			(*index)++;
		}
	}
}

t_cubemap		ft_cubemap_init(char	*m[6])
{
	t_cubemap		cube;
	t_texture		*s;
	int				number;
	int				i;

	ft_memset(&cube, 0, sizeof(t_cubemap));
	cube.exposure = 1.0f;
	cube.srgb = 1;
	cube.exposed = 1;
	if (!(s = ft_texture_new(m[0])))
		ft_print_error("Something went wrong with cubemap loading");
	cube.w = s->w;
	cube.h = s->h;
	if (!(cube.texture = ft_memalloc(sizeof(t_col3) * 6 * cube.w * cube.h)))
		ft_print_error("memalloc error");
	i = CUBE_UP;
	number = i * cube.w * cube.h;
	ft_fill_cube(&cube, &number, s);
	free(s);
	while (++i <= CUBE_BACKWARD)
	{
		number = i * cube.w * cube.h;
		if (!(s = ft_texture_new(m[i])))
			ft_print_error("Something went wrong with cubemap loading");
		ft_fill_cube(&cube, &number, s);
		free(s);
	}
	ft_printf("i\' FINISH LOADING YOUR BIG ENV MAP DEBUG");
	return (cube);
}

t_col3	ft_read_texture(t_col3* tab, float u, float v, int sizeU, int sizeV)
{
	u = fabsf(u);
	v = fabsf(v);
	int umin = (int)sizeU * u;
	int vmin = (int)sizeV * v;
	int umax = (int)sizeU * u + 1;
	int vmax = (int)sizeV * v + 1;
	float ucoef = fabsf(sizeU * u - umin);
	float vcoef = fabsf(sizeV * v - vmin);

	umin = MIN(MAX(umin, 0), sizeU - 1);
	umax = MIN(MAX(umax, 0), sizeU - 1);
	vmin = MIN(MAX(vmin, 0), sizeV - 1);
	vmax = MIN(MAX(vmax, 0), sizeV - 1);
	t_col3	c[2];

	c[0] = ft_col3_sum(ft_col3_kmult((1.0f - ucoef) , tab[umin  + sizeU * vmin]), ft_col3_kmult(ucoef, tab[umax + sizeU * vmin]));
	c[0] = ft_col3_kmult(1.0f - vcoef, c[0]);
	c[1] = ft_col3_sum(ft_col3_kmult((1.0f - ucoef), tab[umin  + sizeU * vmax]), ft_col3_kmult(ucoef, tab[umax + sizeU * vmax]));
	c[1] = ft_col3_kmult(vcoef, c[1]);
	t_col3  output = ft_col3_sum(c[0], c[1]);
	return output;
}

t_col3 ft_read_cubemap(t_cubemap *cm, t_ray r)
{
	t_col3	*c ;
	t_col3	out = {0.0f,0.0f,0.0f};
	if(!cm->texture)
		return out;
	if ((fabsf(r.dir.x) >= fabsf(r.dir.y)) && (fabsf(r.dir.x) >= fabsf(r.dir.z)))
	{
		if (r.dir.x > 0.0f)
		{
			c = cm->texture + CUBE_RIGHT * cm->w * cm->h;
			out = ft_read_texture(c,
					1.0f - (r.dir.z / r.dir.x+ 1.0f) * 0.5f,
					(r.dir.y / r.dir.x+ 1.0f) * 0.5f, cm->w, cm->h);
		}
		else if (r.dir.x < 0.0f)
		{
			c = cm->texture + CUBE_LEFT * cm->w * cm->h;
			out = ft_read_texture(c,
					1.0f - (r.dir.z / r.dir.x+ 1.0f) * 0.5f,
					1.0f - ( r.dir.y / r.dir.x + 1.0f) * 0.5f,
					cm->w, cm->h);
		}
	}
	else if ((fabsf(r.dir.y) >= fabsf(r.dir.x)) && (fabsf(r.dir.y) >= fabsf(r.dir.z)))
	{
		if (r.dir.y > 0.0f)
		{
			c = cm->texture + CUBE_UP * cm->w * cm->h;
			out = ft_read_texture(c,
					(r.dir.x / r.dir.y + 1.0f) * 0.5f,
					1.0f - (r.dir.z/ r.dir.y + 1.0f) * 0.5f, cm->w, cm->h);
		}
		else if (r.dir.y < 0.0f)
		{
			c = cm->texture + CUBE_DOWN * cm->w * cm->h;
			out = ft_read_texture(c,
					1.0f - (r.dir.x / r.dir.y + 1.0f) * 0.5f,
					(r.dir.z/r.dir.y + 1.0f) * 0.5f, cm->w, cm->h);
		}
	}
	else if ((fabsf(r.dir.z) >= fabsf(r.dir.x)) && (fabsf(r.dir.z) >= fabsf(r.dir.y)))
	{
		if (r.dir.z > 0.0f)
		{
			c = cm->texture + CUBE_FORWARD * cm->w * cm->h;
			out = ft_read_texture(c,
					(r.dir.x / r.dir.z + 1.0f) * 0.5f,
					(r.dir.y/r.dir.z + 1.0f) * 0.5f, cm->w, cm->h);
		}
		else if (r.dir.z < 0.0f)
		{
			c = cm->texture + CUBE_BACKWARD * cm->w * cm->h;
			out = ft_read_texture(c,
					(r.dir.x / r.dir.z + 1.0f) * 0.5f,
					1.0f - (r.dir.y /r.dir.z+1) * 0.5f, cm->w, cm->h);
		}
	}
	if (cm->srgb)
	{
		out.blue   = powf(out.blue, 2.2f);
		out.red    = powf(out.red, 2.2f);
		out.green  = powf(out.green, 2.2f);
	}
	if (cm->exposed)
	{
		out.blue  = -logf(1.0f - out.blue);
		out.red   = -logf(1.0f - out.red);
		out.green = -logf(1.0f - out.green);
	}
	out.blue  /= cm->exposure;
	out.red   /= cm->exposure;
	out.green /= cm->exposure;
	return (out);
}
