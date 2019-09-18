/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:59:30 by ebatchas          #+#    #+#             */
/*   Updated: 2019/09/17 09:23:52 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

t_vec3	ft_scale_vec3(t_vec3 r, t_vec3 v, int invert)
{
	if (invert)
	{
		r.x /= v.x;
		r.y /= v.y;
		r.z /= v.z;
	}
	else
	{
		r.x *= v.x;
		r.y *= v.y;
		r.z *= v.z;
	}
	return (r);
}

t_vec3	ft_translate_vec3(t_vec3 r, t_vec3 v, int invert)
{
	if (invert)
	{
		r.x -= v.x;
		r.y -= v.y;
		r.z -= v.z;
	}
	else
	{
		r.x += v.x;
		r.y += v.y;
		r.z += v.z;
	}
	return (r);
}

float rotationMatrix[4][4];
float inputMatrix[4][1] = {0.0, 0.0, 0.0, 0.0};
float outputMatrix[4][1] = {0.0, 0.0, 0.0, 0.0}; 


void multiplyMatrix()
{
	for(int i = 0; i < 4; i++ ){
		for(int j = 0; j < 1; j++){
			outputMatrix[i][j] = 0;
			for(int k = 0; k < 4; k++){
				outputMatrix[i][j] += rotationMatrix[i][k] * inputMatrix[k][j];
			}
		}
	}
}
void setUpRotationMatrix(float angle, float u, float v, float w)
{
	float L = (u*u + v * v + w * w);
	angle = angle * M_PI / 180.0; //converting to radian value
	float u2 = u * u;
	float v2 = v * v;
	float w2 = w * w; 

	rotationMatrix[0][0] = (u2 + (v2 + w2) * cos(angle)) / L;
	rotationMatrix[0][1] = (u * v * (1 - cos(angle)) - w * sqrt(L) * sin(angle)) / L;
	rotationMatrix[0][2] = (u * w * (1 - cos(angle)) + v * sqrt(L) * sin(angle)) / L;
	rotationMatrix[0][3] = 0.0; 

	rotationMatrix[1][0] = (u * v * (1 - cos(angle)) + w * sqrt(L) * sin(angle)) / L;
	rotationMatrix[1][1] = (v2 + (u2 + w2) * cos(angle)) / L;
	rotationMatrix[1][2] = (v * w * (1 - cos(angle)) - u * sqrt(L) * sin(angle)) / L;
	rotationMatrix[1][3] = 0.0; 

	rotationMatrix[2][0] = (u * w * (1 - cos(angle)) - v * sqrt(L) * sin(angle)) / L;
	rotationMatrix[2][1] = (v * w * (1 - cos(angle)) + u * sqrt(L) * sin(angle)) / L;
	rotationMatrix[2][2] = (w2 + (u2 + v2) * cos(angle)) / L;
	rotationMatrix[2][3] = 0.0; 

	rotationMatrix[3][0] = 0.0;
	rotationMatrix[3][1] = 0.0;
	rotationMatrix[3][2] = 0.0;
	rotationMatrix[3][3] = 1.0;
} 

t_vec3	ft_rotate_axis(t_vec3 r, t_vec3 v, float angle)
{
		//angle = DEG_TO_RAD(angle);
	setUpRotationMatrix(angle, v.x, v.y, v.z);
	multiplyMatrix();
	r.x = outputMatrix[0][0];
	r.x = outputMatrix[1][0];
	r.x = outputMatrix[2][0];
	return (r);
}
