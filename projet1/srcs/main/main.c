/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:53:56 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/02 14:38:06 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"
/*
static void	ft_env_draw(t_env *e)
{
	SDL_SetRenderDrawColor(e->ptr.renderer, 0x20, 0x20, 0x20, 255);
	SDL_RenderClear(e->ptr.renderer);
	ft_entry_draw(&e->ptr, e->entry, SCR_WIDTH / 2, SCR_HEIGHT / 2);
	SDL_RenderPresent(e->ptr.renderer);
}
*/
int			main(int argc, char *argv[])
{
	t_env	e;

	if (argc <= 3)
		ft_env_init(&e, argc, argv);
	else
		ft_error();
	ft_memset(&e.in, SDL_FALSE, sizeof(t_input));
	e.in.text = ft_strdup("");
	while (!e.in.quit)
	{
		ft_update_event(&e.in);
		if (ft_process_event(&e, &e.in))
			ft_env_draw(&e);
		SDL_Delay(16);
	}
	ft_env_quit(&e);
	return (0);
}
