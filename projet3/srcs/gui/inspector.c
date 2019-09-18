/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 17:24:57 by ebatchas          #+#    #+#             */
/*   Updated: 2019/08/02 19:05:57 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

void	ft_inspector_init(t_ptr *ptr, t_inspector *ins)
{
	int		i;

	i = -1;
	ins->v3[0].b = ft_button_new(ptr, 0x000000FF, 0xFFFF00FF, "Position");
	while (++i < 3)
		ins->v3[0].e[i] = ft_entry_new(ptr, 0x2020FFFF, 0x00000FF, "0.00");
	i = -1;
	ins->v3[1].b = ft_button_new(ptr, 0x000000FF, 0xFFFF00FF, "Rotation");
	while (++i < 3)
		ins->v3[1].e[i] = ft_entry_new(ptr, 0x0000FFFF, 0x00000FF, "0.00");
	i = -1;
	ins->v3[2].b = ft_button_new(ptr, 0x000000FF, 0xFFFF00FF, "Scale");
	while (++i < 3)
		ins->v3[2].e[i] = ft_entry_new(ptr, 0x0000FFFF, 0x00000FF, "0.00");
	i = -1;
	ins->v3[3].b = ft_button_new(ptr, 0x000000FF, 0xFFFF00FF, "Direction");
	while (++i < 3)
		ins->v3[3].e[i] = ft_entry_new(ptr, 0x0000FFFF, 0x00000FF, "0.00");
	i = -1;
	ins->v3[4].b = ft_button_new(ptr, 0x000000FF, 0xFFFF00FF, "V1");
	while (++i < 3)
		ins->v3[4].e[i] = ft_entry_new(ptr, 0x0000FFFF, 0x00000FF, "0.00");
	i = -1;
	ins->v3[5].b = ft_button_new(ptr, 0x000000FF, 0xFFFF00FF, "V2");
	while (++i < 3)
		ins->v3[5].e[i] = ft_entry_new(ptr, 0x0000FFFF, 0x00000FF, "0.00");
	i = -1;
	ins->v3[6].b = ft_button_new(ptr, 0x000000FF, 0xFFFF00FF, "V3");
	while (++i < 3)
		ins->v3[6].e[i] = ft_entry_new(ptr, 0x0000FFFF, 0x00000FF, "0.00");
	i = -1;
	ins->v3[7].b = ft_button_new(ptr, 0x000000FF, 0xFFFF00FF, "V4");
	while (++i < 3)
		ins->v3[7].e[i] = ft_entry_new(ptr, 0x0000FFFF, 0x00000FF, "0.00");
	ins->v1[0].b = ft_button_new(ptr, 0x000000FF, 0xFFFF00FF, "Radius 1");
	ins->v1[0].e = ft_entry_new(ptr, 0x0000FFFF, 0x00000FF, "0.00");
	ins->v1[1].b = ft_button_new(ptr, 0x000000FF, 0xFFFF00FF, "Radius 2");
	ins->v1[1].e= ft_entry_new(ptr, 0x0000FFFF, 0x00000FF, "0.00");
	ins->v1[2].b = ft_button_new(ptr, 0x000000FF, 0xFFFF00FF, "Height");
	ins->v1[2].e = ft_entry_new(ptr, 0x0000FFFF, 0x00000FF, "0.00");
	ins->v1[3].b = ft_button_new(ptr, 0x000000FF, 0xFFFF00FF, "Angle");
	ins->v1[3].e = ft_entry_new(ptr, 0x0000FFFF, 0x00000FF, "0.00");
	ins->v1[4].b = ft_button_new(ptr, 0x000000FF, 0xFFFF00FF, "Power");
	ins->v1[4].e = ft_entry_new(ptr, 0x0000FFFF, 0x00000FF, "0.00");
	i = -1;
	ins->v3[8].b = ft_button_new(ptr, 0x000000FF, 0xFFFF00FF, "Diffuse");
	while (++i < 3)
		ins->v3[8].e[i] = ft_entry_new(ptr, 0x0000FFFF, 0x00000FF, "0.00");
	i = -1;
	ins->v3[9].b = ft_button_new(ptr, 0x000000FF, 0xFFFF00FF, "Specular");
	while (++i < 3)
		ins->v3[9].e[i] = ft_entry_new(ptr, 0x0000FFFF, 0x00000FF, "0.00");
	i = -1;
	ins->v4[0].b = ft_button_new(ptr, 0x000000FF, 0xFFFF00FF, "albedo");
	while (++i < 4)
		ins->v4[0].e[i] = ft_entry_new(ptr, 0x0000FFFF, 0x00000FF, "0.00");
}

void	ft_inspector_display(t_ptr *ptr, t_inspector *ins)
{
	ft_button_draw(ptr, &ins->v3[0].b, 40, START_Y);
	ft_entry_draw(ptr, &ins->v3[0].e[0], 5, START_Y + DEFAULT_H);
	ft_entry_draw(ptr, &ins->v3[0].e[1], DEFAULT_W + 10, START_Y + DEFAULT_H);
	ft_entry_draw(ptr, &ins->v3[0].e[2], 2 * DEFAULT_W + 15, START_Y + DEFAULT_H);
	ft_button_draw(ptr, &ins->v3[1].b, 40, START_Y + 2 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v3[1].e[0], 5, START_Y + 3 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v3[1].e[1], DEFAULT_W + 10, START_Y + 3 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v3[1].e[2], 2 * DEFAULT_W + 15, START_Y + 3 * DEFAULT_H);
	ft_button_draw(ptr, &ins->v3[2].b, 40, START_Y + 4 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v3[2].e[0], 5, START_Y  + 5 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v3[2].e[1], DEFAULT_W + 10, START_Y + 5 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v3[2].e[2], 2 * DEFAULT_W + 15, START_Y + 5 * DEFAULT_H);
	ft_button_draw(ptr, &ins->v3[3].b, 40, START_Y + 6 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v3[3].e[0], 5, START_Y + 7 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v3[3].e[1], DEFAULT_W + 10, START_Y + 7 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v3[3].e[2], 2 * DEFAULT_W + 15, START_Y + 7 * DEFAULT_H);
	ft_button_draw(ptr, &ins->v3[4].b, 40, START_Y + 8 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v3[4].e[0], 5, START_Y + 9 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v3[4].e[1], DEFAULT_W + 10, START_Y + 9 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v3[4].e[2], 2 * DEFAULT_W + 15, START_Y + 9 * DEFAULT_H);
	ft_button_draw(ptr, &ins->v3[5].b, 40, START_Y + 10 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v3[5].e[0], 5, START_Y + 11 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v3[5].e[1], DEFAULT_W + 10, START_Y + 11 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v3[5].e[2], 2 * DEFAULT_W + 15, START_Y + 11 * DEFAULT_H);
	ft_button_draw(ptr, &ins->v3[6].b, 40, START_Y + 12 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v3[6].e[0], 5, START_Y + 13 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v3[6].e[1], DEFAULT_W + 10, START_Y + 13 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v3[6].e[2], 2 * DEFAULT_W + 15, START_Y + 13 * DEFAULT_H);
	ft_button_draw(ptr, &ins->v3[7].b, 40, START_Y + 14 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v3[7].e[0], 5, START_Y + 15 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v3[7].e[1], DEFAULT_W + 10, START_Y + 15 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v3[7].e[2], 2 * DEFAULT_W + 15, START_Y + 15 * DEFAULT_H);
	ft_button_draw(ptr, &ins->v1[0].b, 5, START_Y + 16 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v1[0].e, 2 * DEFAULT_W + 15, START_Y + 16 * DEFAULT_H);
	ft_button_draw(ptr, &ins->v1[1].b, 5, START_Y + 17 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v1[1].e, 2 * DEFAULT_W + 15, START_Y + 17 * DEFAULT_H);
	ft_button_draw(ptr, &ins->v1[2].b, 5, START_Y + 18 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v1[2].e, 2 * DEFAULT_W + 15, START_Y + 18 * DEFAULT_H);
	ft_button_draw(ptr, &ins->v1[3].b, 5, START_Y + 19 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v1[3].e, 2 * DEFAULT_W + 15, START_Y + 19 * DEFAULT_H);
	ft_button_draw(ptr, &ins->v1[4].b, 5, START_Y + 20 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v1[4].e, 2 * DEFAULT_W + 15, START_Y + 20 * DEFAULT_H);
	ft_button_draw(ptr, &ins->v3[8].b, 40, START_Y + 21 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v3[8].e[0],  5, START_Y + 22 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v3[8].e[1],  DEFAULT_W + 10, START_Y + 22 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v3[8].e[2],  2 * DEFAULT_W + 15, START_Y + 22 * DEFAULT_H);
	ft_button_draw(ptr, &ins->v3[9].b, 40, START_Y + 23 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v3[9].e[0],  5, START_Y + 24 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v3[9].e[1],  DEFAULT_W + 10, START_Y + 24 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v3[9].e[2],  2 * DEFAULT_W + 15, START_Y + 24 * DEFAULT_H);
	ft_button_draw(ptr, &ins->v4[0].b, 40, START_Y + 25 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v4[0].e[0], 5, START_Y + 26 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v4[0].e[1], DEFAULT_W + 10, START_Y + 26 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v4[0].e[2], 2 * DEFAULT_W + 15, START_Y + 26 * DEFAULT_H);
	ft_entry_draw(ptr, &ins->v4[0].e[3], 3 * DEFAULT_W + 20, START_Y + 26 * DEFAULT_H);
}


int		ft_inspector_update_event(t_inspector *ins, t_input *in)
{
	static	int initialized = 0;
	int		i;
	int		j;

	if (!initialized && (initialized = 1))
		return (1);
	i = -1;
	while (++i < N_PROPERTIES)
	{
		j = -1;
		while (++j < 3)
		{
			if (ft_gui_event(&ins->v3[i].e[j], in))
				return (1);
		}
	}
	i = -1;
	while (++i < N_VIEW1)
		if (ft_gui_event(&ins->v1[i].e, in))
			return (1);
	i = -1;
	while (++i < N_VIEW4)
	{
		j = -1;
		while (++j < 4)
		{
			if (ft_gui_event(&ins->v4[i].e[j], in))
				return (1);
		}
	}
	return (0);
}

void	ft_inspector_clean(t_inspector *ins)
{
	int		i;
	int		j;

		i = -1;
	while (++i < N_PROPERTIES)
	{
		j = -1;
		ft_button_clean(&ins->v3[i].b);
		while (++j < 3)
			ft_entry_clean(&ins->v3[i].e[j]);
	}
	j = -1;
	while (++j < N_VIEW1)
	{
		ft_button_clean(&ins->v1[j].b);
		ft_entry_clean(&ins->v1[j].e);
	}
	i = -1;
	while (++i < N_VIEW4)
	{
		j = -1;
		ft_button_clean(&ins->v4[i].b);
		while (++j < 4)
			ft_entry_clean(&ins->v4[i].e[j]);
	}
}
