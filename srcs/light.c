/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 18:24:32 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/14 20:05:44 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_light		*ft_light_new(t_vec3 pos, t_col3 col3)
{
	t_light	*new;

	if ((new = malloc(sizeof(*new))))
	{
		new->pos = pos;
		new->intensity = col3;
		new->next = NULL;
	}
	else
		ft_error();
	return (new);
}

void		ft_light_push_back(t_light **lst, t_light *new)
{
	t_light	*p;

	if (!lst || !new)
		return ;
	else if (!*lst)
		*lst = new;
	else
	{
		p = *lst;
		while (p->next)
			p = p->next;
		p->next = new;
	}
}

void		ft_light_clean(t_light **lst)
{
	t_light	*p;

	if (!lst || !*lst)
		return ;
	p = *lst;
	while (p)
	{
		(*lst) = (*lst)->next;
		free(p);
		p = (*lst);
	}
}
