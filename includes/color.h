/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 20:11:11 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/17 18:16:07 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef struct	s_col3
{
	float		red;
	float		green;
	float		blue;
}				t_col3;

t_col3			ft_col3(float r, float g, float b);
t_col3			ft_col3_sum(t_col3 a, t_col3 b);
t_col3			ft_col3_mult(t_col3 a, t_col3 b);
t_col3			ft_col3_kmult(float k, t_col3 a);
#endif
