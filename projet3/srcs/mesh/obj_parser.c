/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 21:21:45 by ebatchas          #+#    #+#             */
/*   Updated: 2019/09/16 10:44:59 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void	ft_parse_obj_vector(t_vector *v, char *line)
{
	char		**tab;
	t_vec3		vec;
	int			i;

	i = 0;
	vec = (t_vec3){.0, 0.0, 0.0};
	if ((tab = ft_strsplit(line, ' ')) && ft_tab_len(tab) == 4)
	{
		vec.x = ft_atof(tab[1]);
		vec.y = ft_atof(tab[2]);
		vec.z = ft_atof(tab[3]);
	}
	ft_tab_free(tab);
	v->push_back(v, &vec);
}

void	ft_parse_obj_uv(t_vector *v, char *line)
{
	char		**tab;
	t_vec2		vec;
	int			i;

	i = 0;
	vec = (t_vec2){.0, 0.0};
	if ((tab = ft_strsplit(line, ' ')) && ft_tab_len(tab) == 3)
	{
		vec.x = ft_atof(tab[1]);
		vec.y = ft_atof(tab[2]);
	}
	ft_tab_free(tab);
	v->push_back(v, &vec);
}

void	ft_parse_obj_normal(t_vector *v, char *line)
{
	char		**tab;
	t_vec3		vec;
	int			i;

	i = 0;
	vec = (t_vec3){.0, 0.0, .0};
	if ((tab = ft_strsplit(line, ' ')) && ft_tab_len(tab) == 4)
	{
		vec.x = ft_atof(tab[1]);
		vec.y = ft_atof(tab[2]);
		vec.z = ft_atof(tab[3]);
	}
	ft_tab_free(tab);
	v->push_back(v, &vec);
}

void	ft_parse_obj_faces(t_obj *obj, char *line)
{
	char		**tab1;
	char		**tab;
	int			i;

	i = 0;
	if ((tab1 = ft_strsplit(line, ' ')) && ft_tab_len(tab1) == 4)
	{
		while (i < 3 && (tab = ft_strsplit(tab1[i + 1], '/')) && ft_tab_len(tab) == 3)
		{
			ft_bizzare(obj, tab);
			ft_tab_free(tab);
			i = i + 1;
		}
	}
	ft_tab_free(tab1);
}
