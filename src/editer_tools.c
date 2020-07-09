/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editer_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/09 11:24:25 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_sector		*get_a_sector_by_id(t_map *map, int id)
{
	t_sector	*sector;
	int			i;

	i = 1;
	sector = map->sectors;
	while (i < id)
	{
		i++;
		sector = sector->next_sector;
	}
	if (id == 0)
		return (NULL);
	return (sector);
}

float			cross_product(t_point a, t_point b, t_point c)
{
	float bax;
	float bay;
	float bcx;
	float bcy;

	bax = a.x - b.x;
	bay = a.y - b.y;
	bcx = c.x - b.x;
	bcy = c.y - b.y;
	return (bax * bcy - bay * bcx);
}

int				is_between(float x, float a, float b)
{
	if (a > b)
	{
		if (x > b && x < a)
			return (1);
	}
	else
	{
		if (x > a && x < b)
			return (1);
	}
	return (0);
}

int				is_same_point(t_point a, t_point b)
{
	if (a.x == b.x && a.y == b.y)
		return (1);
	return (0);
}
