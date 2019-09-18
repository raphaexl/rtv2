/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_uv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 10:28:17 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/20 13:06:33 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

t_vec3	ft_compute_primary_tex_dir(t_vec3	normal)
{
	t_vec3	a;
	t_vec3	b;
	t_vec3	max_ab;
	t_vec3	c;

	a = ft_vec3_cross(normal, ft_vec3(1, 0, 0));
	b = ft_vec3_cross(normal, ft_vec3(0, 1, 0));
	max_ab = ft_vec3_dot(a, a) < ft_vec3_dot(b, b) ? b : a;
	c = ft_vec3_cross(normal, ft_vec3(0, 0, 1));
	return (ft_vec3_normalized(ft_vec3_dot(max_ab, max_ab) < ft_vec3_dot(c, c) ? c : max_ab));
}

void	ft_plane_uv(t_plane *plane, t_vec3	n, t_vec3 p, t_uv *uv)
{
	t_vec3	u_axis, v_axis;

	(void)plane;
/*	u_axis = ft_compute_primary_tex_dir(n);
	v_axis = ft_vec3_cross(n, u_axis);*/
	u_axis = ft_vec3(n.y, n.z, -n.x);
	v_axis = ft_vec3_cross(u_axis, n);
	//printf("u : x = %.2f\t y = %.2f\t z = %.2f\n", u_axis.x, u_axis.y, u_axis.z);
	//printf("v : x = %.2f\t y = %.2f\t z = %.2f\n", v_axis.x, v_axis.y, v_axis.z);
	uv->u = ft_vec3_dot(p, u_axis) / 100.0;
	uv->v = ft_vec3_dot(p, v_axis) / 400.0;
	if (uv->u < 0.0f)
		uv->u *= -1.0f;
	if (uv->v < 0.0f)
		uv->v *= -1.0f;
}
