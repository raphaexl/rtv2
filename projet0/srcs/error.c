/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:52:50 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/28 15:52:55 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void	ft_print_error(char *str)
{
	ft_putendl(str);
	exit(EXIT_FAILURE);
}

void	ft_sdl_error(void)
{
	ft_putendl(SDL_GetError());
	exit(EXIT_FAILURE);
}

void	ft_error(void)
{
	ft_putendl("error");
	exit(EXIT_FAILURE);
}
