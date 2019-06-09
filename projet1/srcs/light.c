/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:53:29 by ebatchas          #+#    #+#             */
/*   Updated: 2019/06/08 22:03:08 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

t_light		*ft_light_new(t_ltype type, t_light *l)
{
	t_light	*new;

	if ((new = malloc(sizeof(*new))))
	{
		new->type = type;
		new->pos = l->pos;
		new->dir = l->dir;
		new->color = l->color;
		new->intensity = l->intensity;
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