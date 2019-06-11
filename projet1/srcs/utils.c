/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:59:58 by ebatchas          #+#    #+#             */
/*   Updated: 2019/06/08 19:37:04 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

float	ft_modulo(float f)
{
	return (f - floor(f));
}

float	ft_clamp(float min, float max, float val)
{
	return (fmax(min, fmin(max, val)));
}

t_vec3	ft_mix(t_vec3 v1, t_vec3 v2, float mix)
{
	return (ft_vec3_sum(ft_vec3_kmult(1.0 - mix, a), ft_vec3_kmult(mix, b)));
}

float	ft_rand48(void)
{
	static int	initialized = 0;

	if (!initialized)
	{
		initialized = 1;
		srand(time(NULL));
	}
	return ((float)(rand() % RAND_MAX) / ((float)(RAND_MAX + 1.0)));
}

int		ft_tab_len(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
