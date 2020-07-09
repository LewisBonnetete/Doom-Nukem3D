/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:04:28 by lewis             #+#    #+#             */
/*   Updated: 2020/07/09 15:08:12 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void			init_tab(int *tab, int n)
{
	int i;

	i = 0;
	while (i <= n + 1)
	{
		tab[i] = 0;
		i++;
	}
}

void			free_itab(t_itab *tab)
{
	free(&tab);
}

void			free_ray(t_ray *ray)
{
	free(&ray);
}

void			free_wall(t_wall *wall)
{
	free(&wall);
}

void			free_item(t_item *item)
{
	if (item->name)
		ft_strdel(&item->name);
	ft_memdel((void **)&item);
}
