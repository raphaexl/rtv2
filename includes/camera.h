/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 06:17:50 by ebatchas          #+#    #+#             */
/*   Updated: 2019/09/21 15:57:40 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# define FOV 60.0
# include "vec3.h"

typedef	struct	s_camera
{
	t_vec3		pos;
	t_vec3		rot;
	t_vec3		trans;
	t_vec3		dir;
	t_vec3		u;
	t_vec3		v;
	t_vec3		horiz;
	t_vec3		vert;
	t_vec3		low_left;
	float		ratio;
	float		fov;
	float		h;
	float		w;
}				t_camera;

#endif
