/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 10:47:27 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/17 18:41:35 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACE_H
# define RAYTRACE_H

# include "camera.h"
# include "color.h"
# include "defines.h"

typedef enum	e_type
{
	NONE = 0, DISK, SPHERE, PLANE, CYLINDRE, CONE, BOX, TORUS, TRIANGLE
}				t_type;

typedef struct	s_ray
{
	t_vec3	start;
	t_vec3	dir;
}				t_ray;

typedef	struct	s_l
{
	t_vec3	pos;
	t_col3		intensity;
	struct s_l	*next;
}				t_light;

typedef struct	s_texture
{
	int		w;
	int		h;
	Uint32	*data;
}				t_texture;

typedef struct s_perlin
{
	t_vec3		*ranvec;
	int			*perm_x;
	int			*perm_y;
	int			*perm_z;
}				t_perlin;

typedef struct	s_material
{
	t_col3		diffuse;
	t_col3		specular;
	float		spec_pow;
	float		reflection;
	float		refraction;
	int			chess;
}				t_material;

typedef	struct	s_o
{
	t_material	material;
	t_vec3		pos;
	t_vec3		translate;
	t_vec3		rotate;
	t_vec3		normal;
	float		radius;
	float		angle;
	int			id;
	t_type		type;
	char		*name;
	struct s_o	*next;
}				t_object;

typedef struct	s_iterm
{
	t_vec3	pos;
	t_col3		col3;
}				t_iterm;

typedef struct	s_intersect
{
	t_ray		ray;
	t_ray		ray_light;
	t_vec3	n;
	t_vec3	p;
	float		t;
	t_object	*current;
}				t_intersect;

typedef	struct	s_scene
{
	t_camera	cam;
	t_col3		c;
	t_col3		bg_col3;
	t_col3		ambiant;
	int			nb_samples;
	int			a;
	t_texture	*earth;
	t_object	*obj;
	t_light		*light;
	t_col3		(*ft_rtv1)(struct s_scene *, t_intersect *, int);
}				t_scene;
#endif
