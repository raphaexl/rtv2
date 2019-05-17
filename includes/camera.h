/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 06:17:50 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/14 20:10:48 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# define PPD 925
# define FOV 60.0
# define FOV_H 30
# include "vector.h"

typedef	struct	s_camera
{
	t_vec3	pos;
	t_vec3	rot;
	t_vec3	trans;
	t_vec3	look_at;
	t_vec3	dir;
	t_vec3	up;
	t_vec3	u;
	t_vec3	v;
	t_vec3	horiz;
	t_vec3	vert;
	t_vec3	low_left;
	float		ratio;
	float		fov;
	float		h;
	float		w;
}				t_camera;

#endif
