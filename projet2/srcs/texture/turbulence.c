/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turbulence.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:40:40 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/21 15:41:28 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/rt.h"


float	ft_perlin_turbulence(t_perlin perlin, t_col3 p, int depth)
{
	float		accum;
	t_vec3		tmp;
	float		weight;

	weight = 1.0;
	accum = 0.0; 
	tmp = (t_vec3){p.red, p.green, p.blue};
	for (int i = 0; i < depth; i++)
	{
		accum += weight * ft_perlin_noise(&perlin, tmp);
		weight *= 0.5;
		tmp = ft_vec3_kmult(2.0, tmp);
	}
	return (fabs(accum));
}

float	ft_perlin_marble(t_perlin perlin, t_col3 p, float scale)
{
	return (0.5 * (1 + sin(scale * p.blue + 10.0 * ft_perlin_turbulence(perlin, p, 7))));
}
