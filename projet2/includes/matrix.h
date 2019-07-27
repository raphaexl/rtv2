/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:36:05 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/29 20:38:38 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H
# include "vec3.h"

#include <stdio.h> //to remove
//'em
typedef struct	s_matrix
{
	float		m[16];
}				t_mat4;

float			ft_cotangent(float angle);
float			ft_degre_to_radian(float angle);
float			ft_radian_to_degre(float angle);
t_mat4			ft_mat4_identity(void);
t_mat4			ft_mat4_raz(void);
t_mat4			ft_mat4_mult_mat4(t_mat4 *m1, t_mat4 *m2);
t_mat4			ft_mat4_mult_vec3(t_mat4 *m1, t_vec3 v);
t_mat4			ft_mat4_scale_vec3(t_mat4 *m1, t_vec3 v);
t_mat4			ft_mat4_translate_vec3(t_mat4 *m1, t_vec3 v);
t_mat4			ft_mat4_rotate_vec3(t_mat4 *m1, t_vec3 v);
t_mat4			ft_mat4_rotate_x(t_mat4	*m1, float angle);
t_mat4			ft_mat4_rotate_y(t_mat4	*m1, float angle);
t_mat4			ft_mat4_rotate_z(t_mat4	*m1, float angle);
t_vec3		ft_get_mat4_vec3(t_mat4 m);
void			ft_print_mat4(t_mat4 m);
void			ft_print_vec3(t_vec3 v);
# endif
