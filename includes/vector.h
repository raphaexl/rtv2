/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 19:56:42 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/14 19:57:02 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "defines.h"

typedef struct	s_vec3
{
	float	x;
	float	y;
	float	z;
}				t_vec3;

t_vec3		ft_vec3(float x, float y, float z);
t_vec3		ft_vec3_sum(t_vec3 a, t_vec3 b);
t_vec3		ft_vec3_sub(t_vec3 a, t_vec3 b);
t_vec3		ft_vec3_mult(t_vec3 a, t_vec3 b);
t_vec3		ft_vec3_cross(t_vec3 a, t_vec3 b);
t_vec3		ft_vec3_kmult(float k, t_vec3 b);
t_vec3		ft_vec3_normalized(t_vec3 a);
float			ft_vec3_norm(t_vec3 a);
float			ft_vec3_dot(t_vec3 a, t_vec3 b);
t_vec3		ft_reflect(t_vec3 v, t_vec3 n);
int				ft_refract(t_vec3 v, t_vec3 n, float ior, t_vec3 *r);
#endif