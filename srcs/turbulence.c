/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turbulence.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 17:33:02 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/17 17:45:52 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/rtv1.h"


float	ft_perlin_turbulance(t_col3 p, int depth)
{
	float	accum;
	t_col3	tmp;
	float	weight;

	weight = 1.0;
	for (int i = 0; i < depth; i++)
	{
		accum += weight * ft_perlin_noise(tmp);
		weight *= 0.5;
		tmp = ft_col3_kmult(2.0, tmp);
	}
	return (fabs(accum));
}

float	ft_perlin_marble(t_col3 p, float scale)
{
	return (0.5 * (1 + sin(scale * p.z + 10.0 * ft_perlin_turbulance(p, 7))));
}
