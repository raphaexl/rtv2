/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 13:11:20 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/13 18:27:56 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int		ft_process_entry(t_entry *e, t_input *in)
{
	if (e->ft_mouse_on_entry && in->render_text && ft_strlen(in->text))
	{	
		e->mes = ft_strcpy(e->mes, in->text);
		return (1);
	}
	return (0);
}
