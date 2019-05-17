/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   root3and4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 12:10:10 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/17 16:17:56 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		ft_solve_quadric(double c[3], double s[2])
{
	double	p;
	double	q;
	double	d;

	p = c[1] / (2.0 * c[2]);
	q = c[0] / c[2];
	d = p * p - q;
	if (IS_ZERO(d))
	{
		s[0] = -p;
		return (1);
	}
	else if (d < 0)
		return (0);
	else
	{
		d = sqrt(d);
		s[0] = d - p;
		s[1] = -d -p;
		return (2);
	}
}


int		ft_solve_cubic(double w[4], double s[3])
{
	int		i, num;
	double	sub;
	double	a, b, c;
	double	sq_a, p, q;
	double cb_p, d;

	a = w[2] / w[3];
	b = w[1] / w[3];
	c = w[0] / w[3];
	sq_a = a * a;
	p = 1.0 / 3.0 * (-1.0 / 3.0 * sq_a + b);
	q = 1.0 / 2.0 * (2.0 / 27.0 * a * sq_a - 1.0 / 3.0 * a * b + c);
	cb_p = p * p * p;
	d = q * q + cb_p;
	if (IS_ZERO(d))
	{
		if (IS_ZERO(q))
		{
			s[0] = 0;
			num = 1;
		}
		else
		{
			double u = CBRT(-q);
			s[0] = 2.0 * u;
			s[1] = -u;
			num = 2;
		}
	}
	else if (d < 0)
	{
		double phi = 1.0 / 3.0 * acos(-q / sqrt(-cb_p));
		double t = 2.0 * sqrt(-p);

		s[0] = t * cos(phi);
		s[1] = -t * cos(phi + M_PI / 3.0);
		s[2] = -t * cos(phi - M_PI / 3.0);
		num = 3;
	}
	else
	{
		double sqrt_d = sqrt(d);
		double u = CBRT(sqrt_d - q);
		double v = -CBRT(sqrt_d + q);
		
		s[0] = u + v;
		num = 1;
	}
	sub = 1.0 / 3.0 * a;
	i = -1;
	while (++i < num)
		s[i] -= sub;
	return (num);
}

int		ft_solve_quartic(double w[5], double s[4])
{
	double	coeffs[4];
	double	z, u, v, sub;
	double	a, b, c, d;
	double	sq_a, p, q, r;
	int		i, num;

	a = w[3] / w[4];
	b = w[2] / w[4];
	c = w[1] / w[4];
	d = w[0] / w[4];

	sq_a = a * a;
	p = -3.0 / 8.0 * sq_a + b;
	q = 1.0 / 8.0 * sq_a * a - 1.0 / 2.0 * a * b + c;
	r = -3.0 / 256.0 * sq_a * sq_a + 1.0 / 16.0 * sq_a * b - 1.0 / 4.0 * a * c + d;
	if (IS_ZERO(r))
	{
		coeffs[0] = q;
		coeffs[1] = p;
		coeffs[2] = 0.0;
		coeffs[3] = 1.0;
		num = ft_solve_cubic(coeffs, s);
		s[num++] = 0.0;
	}
	else
	{
		coeffs[0] = 1.0 / 2.0 * r * p - 1.0 / 8.0 * q * q;
		coeffs[1] = -r;
		coeffs[2] = -1.0 / 2.0 * p;
		coeffs[3] = 1.0;
		(void)ft_solve_cubic(coeffs, s);
		z = s[0];
		u = z * z - r;
		v = 2.0 * z - p;
		if (IS_ZERO(u))
			u = 0;
		else if (u > 0)
			u = sqrt(u);
		else
			return (0);
		if (IS_ZERO(v))
			v = 0.0;
		else if (v > 0.0)
			v = sqrt(v);
		else
			return (0);
		coeffs[0] = z - u;
		coeffs[1] = q < 0 ? -v : v;
		coeffs[2] = 1;
		num = ft_solve_quadric(coeffs, s);
		coeffs[0] = z + u;
		coeffs[1] = q < 0 ? v : -v;
		coeffs[2] = 1;
		num += ft_solve_quadric(coeffs, s + num);
	}
	sub = 1.0 / 4.0 * a;
	i = -1;
	while (++i < num)
		s[i] -= sub;
	return (num);
}
