/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   col3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 19:26:28 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/27 19:27:04 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COL3_H
# define COL3_H

typedef struct	s_col
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
