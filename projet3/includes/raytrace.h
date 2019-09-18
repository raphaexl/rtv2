/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 10:47:27 by ebatchas          #+#    #+#             */
/*   Updated: 2019/09/18 16:59:50 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACE_H
# define RAYTRACE_H

# include "camera.h"
# include "col3.h"
# include "defines.h"
# include "libft/libft.h"

typedef enum	e_type
{
	NO_OBJECT = 0, SPHERE, CONE, CYLINDER, BOX, PLANE, DISK, TORUS, CUBE, TRIANGLE,
	PARALLELOGRAM, RING, ELLIPSOID, PARABOLOID, MESH
}				t_type;

typedef enum	e_ltype
{
	DEFAULT_LIGHT, DISTANT_LIGHT, POINT_LIGHT, SPOT_LIGHT
}				t_ltype;

typedef enum	e_ftype
{
	NOFILTER, GAUSSIAN_BLUR,  MOTION_BLUR, 
	SHARPEN, EMBOSS, SOBEL, GREY
}				t_ftype;

typedef	enum	e_ptype
{
	NO_PERTURBATION, NOISE, RIPPLES, WAVES, PERLIN, MARBLE, CHESS
}				t_ptype;

typedef enum	e_mtype
{
	DIFFUSE, SPECULAR, METAL, DIELECTRIC
}				t_mtype;

typedef enum	e_ctype
{
	CUBE_UP, CUBE_DOWN, CUBE_RIGHT, CUBE_LEFT, CUBE_FORWARD, CUBE_BACKWARD
}				t_ctype;

typedef	enum	e_itype
{
	DEFAULT, EDITING
}				t_itype;

typedef struct	s_ray
{
	t_vec3		start;
	t_vec3		dir;
}				t_ray;

typedef struct 		s_d_light
{
	t_vec3 		dir;
}					t_direct_light;

typedef struct 		s_def_light
{
	t_vec3 		pos;
}					t_default_light;


typedef struct 		s_p_light
{
	t_vec3 		pos;
	float   	constant;
	float   	linear;
	float   	quadratic;
}				t_point_light;

typedef struct 		s_s_light
{
	t_vec3    pos;
	t_vec3    dir;

	float   constant;
	float   linear;
	float   quadratic;
	float   cut_off;
	float   outer_cut_off;
}					t_spot_light;

typedef union	u_light
{
	t_default_light	def;
	t_spot_light	spot;
	t_point_light	point;
	t_direct_light	direct;
}				t_union_light;

typedef	struct	s_l
{
	t_union_light	u;
	t_col3 			ambient;
	t_col3 			diffuse;
	t_col3			specular;
	int				id;
	float			intensity;
	t_ltype			type;
	struct s_l		*next;
}				t_light;

typedef struct	s_texture
{
	int		w;
	int		h;
	Uint32	*data;
}				t_texture;

typedef struct	s_cubemap
{
	t_col3		*texture;
	int			w;
	int			h;
	float		exposure;
	int			exposed;
	int			srgb;
}				t_cubemap;

typedef	struct	s_convolution
{
	int		size;
	int		den;
	Uint32	*img;
	Uint32	*aux;
	double *filter;
	t_point	pix;
}				t_convolution;

typedef	struct s_pixel
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	int			  col;
}				t_pixel;

typedef struct	s_material
{
	t_mtype		type;
	float		albedo[4];
	t_col3		diffuse;
	t_col3		diffuse2;
	t_col3		specular;
	float		spec_pow;
	int			chess;
	float		bump;
	t_ptype		pert;
}				t_material;

typedef struct	s_sphere
{
	float		radius;
	float		radius2;
}				t_sphere;

typedef struct	s_cylinder
{
	float		radius;
	float		radius2;
	float		height;
	t_vec3		v;
}				t_cylinder;

typedef struct	s_disk
{
	float		radius;
	float		radius2;
	t_vec3		normal;
}				t_disk;

typedef struct	s_cone
{
	float		angle;
	float		height;
	t_vec3		v;
}				t_cone;

typedef struct	s_plane
{
	t_vec3		normal;
}				t_plane;

typedef struct	s_box
{
	t_vec3		bounds[2];
}				t_box;

typedef struct	s_torus
{
	float		radius1;
	float		radius2;
}				t_torus;

typedef struct	s_cube
{
	float		radius;
}				t_cube;

typedef struct	s_triangle
{
	t_vec3		a;
	t_vec3		b;
	t_vec3		c;
}				t_triangle;

typedef struct	s_parallelogram
{
	t_vec3		a;
	t_vec3		b;
	t_vec3		c;
	t_vec3		d;
}				t_parallelogram;

typedef struct	s_ring
{
	float		radius;
	float		radius2;
	float		height;
	t_vec3		v;
}				t_ring;

typedef struct	s_ellipsoid
{
	float		k;
	float		radius;
	float		radius2;
	t_vec3		v;
	t_vec3		c;
}				t_ellipsoid;

typedef struct	s_paraboloid
{
	float		k;
	t_vec3		v;
	t_vec3		c;
}				t_paraboloid;

typedef struct	s_normal
{
	t_vec3		a;
	t_vec3		b;
	t_vec3		c;
}				t_normal;

typedef struct	s_texel
{
	t_vec2		a;
	t_vec2		b;
	t_vec2		c;
}				t_texel;

typedef struct	s_mesh
{
	char		*name;
	t_triangle	*triangles;
	t_normal	*normals;
	t_texel		*texels;
	int			size;
}				t_mesh;

typedef struct	s_obj
{
	t_vector	vertices;
	t_vector	uvs;
	t_vector	normals;
	t_vector	v_indices;
	t_vector	uv_indices;
	t_vector	n_indices;
}				t_obj;

typedef union	s_union
{
	t_sphere		sphere;
	t_cylinder		cylinder;
	t_disk			disk;
	t_cone			cone;
	t_plane			plane;
	t_box			box;
	t_torus			torus;
	t_cube			cube;
	t_triangle		triangle;
	t_parallelogram	para;
	t_ring			ring;
	t_ellipsoid		ellipse;
	t_paraboloid	parab;
	t_mesh			mesh;
}				t_union;

typedef	struct	s_o
{
	t_material	material;
	t_vec3		pos;
	t_vec3		translate;
	t_vec3		rotate;
	t_vec3		scale;
	t_union		e;
	int			id;
	t_type		type;
	char		*name;
	struct s_o	*next;
}				t_object;

typedef struct	s_iterm
{
	t_vec3		pos;
	t_col3		color;
}				t_iterm;

typedef struct	s_intersect
{
	t_ray		ray;
	t_ray		ray_light;
	t_vec3		n;
	t_vec3		p;
	float		t;
	t_object	*current;
}				t_intersect;

typedef t_intersect t_hit;
typedef	struct	s_scene
{
	t_camera	cam;
	t_cubemap	cmap;
	t_col3		c;
	t_col3		bg_color;
	t_col3		ambiant;
	int			nb_samples;
	int			a;
	t_object	*obj;
	t_light		*light;
	t_texture	*earth;
	t_texture	*img[N_TEXTURES];
	t_ftype		filter;
	t_col3		(*ft_rtv1)(struct s_scene *, t_intersect *, int);
	t_col3		(*ft_bg_color)(struct s_scene *, t_intersect *, int);
}				t_scene;
#endif
