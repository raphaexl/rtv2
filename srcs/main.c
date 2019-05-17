/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 18:54:55 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/15 19:30:57 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		main(int argc, char *argv[])
{
	t_input	in;
	t_env	e;

	if (argc <= 3)
		ft_env_init(&e, argc, argv);
	else
		ft_error();
	ft_memset(&in, SDL_FALSE, sizeof(t_input));
	while (!in.quit)
	{
		ft_update_event(&in);
		if (ft_process_event(&e, &in))
			ft_env_draw(&e);
		SDL_Delay(16);
	}
	ft_env_quit(&e);
	return (0);
}
