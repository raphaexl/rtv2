/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lview.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 16:15:43 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/13 19:19:06 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void	ft_lview_init(t_ptr *ptr, t_lview *lv)
{
	int		i;

	lv->b = ft_button_new(ptr, 0x000000FF, 0xFFFF00FF, "LIGHT");
	lv->e = ft_entry_new(ptr, 0x2020FFFF, 0x00000FF, "NONE");
	i = -1;
	lv->v[0].b = ft_button_new(ptr, 0x000000FF, 0xFFFF00FF, "POSITION");
	while (++i < 3)
		lv->v[0].e[i] = ft_entry_new(ptr, 0x2020FFFF, 0x00000FF, "0.00");
	i = -1;
	lv->v[1].b = ft_button_new(ptr, 0x000000FF, 0xFFFF00FF, "DIRECTION");
	while (++i < 3)
		lv->v[1].e[i] = ft_entry_new(ptr, 0x2020FFFF, 0x00000FF, "0.00");
	i = -1;
	lv->v[2].b = ft_button_new(ptr, 0x000000FF, 0xFFFF00FF, "INTENSITY");
	while (++i < 3)
		lv->v[2].e[i] = ft_entry_new(ptr, 0x2020FFFF, 0x00000FF, "0.00");
}

void	ft_lview_display(t_ptr *ptr, t_lview *lv)
{
	ft_button_draw(ptr, &lv->b, END_X + DEFAULT_W, START_Y + 5);
	ft_entry_draw(ptr, &lv->e, END_X + DEFAULT_W + 20, START_Y + DEFAULT_H + 5);
	ft_button_draw(ptr, &lv->v[0].b, END_X + DEFAULT_W, START_Y + 2 * DEFAULT_H + 5);
	ft_entry_draw(ptr, &lv->v[0].e[0], END_X + 20, START_Y + 3 * DEFAULT_H + 5);
	ft_entry_draw(ptr, &lv->v[0].e[1], END_X + DEFAULT_W + 20, START_Y + 3 * DEFAULT_H + 5);
	ft_entry_draw(ptr, &lv->v[0].e[2], END_X + DEFAULT_W * 2 + 20, START_Y + 3 * DEFAULT_H + 5);
	ft_button_draw(ptr, &lv->v[1].b, END_X + DEFAULT_W, START_Y + 4 * DEFAULT_H + 5);
	ft_entry_draw(ptr, &lv->v[1].e[0], END_X + 20, START_Y + 5 * DEFAULT_H + 5);
	ft_entry_draw(ptr, &lv->v[1].e[1], END_X + DEFAULT_W + 20, START_Y + 5 * DEFAULT_H + 5);
	ft_entry_draw(ptr, &lv->v[1].e[2], END_X + DEFAULT_W * 2 + 20, START_Y + 5 * DEFAULT_H + 5);
	ft_button_draw(ptr, &lv->v[2].b, END_X + DEFAULT_W, START_Y + 6 * DEFAULT_H + 5);
	ft_entry_draw(ptr, &lv->v[2].e[0], END_X + 20, START_Y + 7 * DEFAULT_H + 5);
	ft_entry_draw(ptr, &lv->v[2].e[1], END_X + DEFAULT_W + 20, START_Y + 7 * DEFAULT_H + 5);
	ft_entry_draw(ptr, &lv->v[2].e[2], END_X + DEFAULT_W * 2 + 20, START_Y + 7 * DEFAULT_H + 5);
}

int		ft_lview_update_event(t_lview *lv, t_input *in)
{
	static	int initialized = 0;
	int		i;
	int		j;

	if (!initialized && (initialized = 1))
		return (1);
	if (ft_gui_event(&lv->e, in))
		return (1);
	j = -1;
	while (++j < 3)
	{
		i = -1;
		while (++i < 3)
			if (ft_gui_event(&lv->v[j].e[i], in))
				return (1);
	}
	return (0);
}

void	ft_lview_clean(t_lview *lv)
{
	int		j;
	int		i;

	ft_button_clean(&lv->b);
	j = -1;
	while (++j < 3)
	{
		i = -1;
		ft_button_clean(&lv->v[j].b);
		while (++i < 3)
			ft_entry_clean(&lv->v[j].e[i]);
	}
}
