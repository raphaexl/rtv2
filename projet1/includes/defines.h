/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 11:55:38 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/03 16:11:31 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <math.h>
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# define MAX_DEPTH 10
# define NB_OPTIONS 22
# define N_PROPERTIES 10
# define N_VIEW1 5
# define N_VIEW4 1
# define DEFAULT_W1 100
# define DEFAULT_W 50
# define DEFAULT_H 25
# define DEFAULT_FSIZE 10
# define DEFAULT_NSIZE 5
# define DEFAULT_FONT ("data/fonts/Roboto-Condensed.ttf")
# define ANGELINA_FONT ("data/fonts/angelina.TTF")
# define BLACK	0x000000FF
# define RED	0xFF0000FF
# define GREEN	0x00FF00FF
# define BLUE   0x0000FFFF
# define YELLOW	0x00FFFF00
# define NB_INSPECT 2
# define DELTA_TRANS 1.5
# define DELTA_SCALE 1.0
# define DELTA_ANGLE 2
# define DEG_TO_RAD(x) ((x) * (M_PI / 180.0))
# define MAX(a, b) ((a) < (b) ? (b) : (a))
# define MIN(a, b) ((a) < (b) ? (a) : (b))
# define EQN_EPS 1e-9
# define IS_ZERO(x) ((x) > -EQN_EPS && (x) < EQN_EPS)
# ifndef CBRT
#  define POW1(x) (pow((double)(x), 1.0 / 3.0))
#  define POW2(x) (pow((double)-(x), 1.0 / 3.0))
#  define CBRT(x) ((x) > 0.0 ? POW1(x) : ((x) < 0.0 ? -POW2(x) : 0.0))
# endif

typedef struct	s_point
{
	int		x;
	int		y;
}				t_point;

typedef struct	s_delta
{
	float	a;
	float	b;
	float	c;
	float	delta;
}				t_delta;

typedef struct	s_cubic
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	sq_a;
	double	p;
	double	q;
	double	cb_p;
}				t_cubic;

typedef struct	s_quartic
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	z;
	double	u;
	double	v;
	double	sub;
	double	sq_a;
	double	p;
	double	q;
	double	r;
}				t_quartic;

typedef	enum	e_opt
{
	NNE = 0, NEW_SPHERE, NEW_CONE, NEW_CYLINDRE, NEW_BOX, NEW_PLANE, NEW_DISK,
	NEW_TORUS, NEW_CUBE, NEW_TRIANGLE, NEW_PARALLELOGRAM, NEW_RING, NEW_ELLIPSOID, 
	NEW_PARABOLOID, NEW_MESH, DELETE, EDIT_TRACE, RAY_TRACE, PATH_TRACE, S_BMP, S_PNG,
	ZOOM
}				t_options;

typedef	struct	s_font
{
	char		*mes;
	char		*file;
	int			size;
}				t_font;
#endif
