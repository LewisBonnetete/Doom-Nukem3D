/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editer_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/03 14:32:48 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem_edit.h"

int			nbr_of_sectors(t_map *map)
{
	t_sector	*sector;
	int			i;

	sector = map->sectors;
	i = 1;
	while (sector->next_sector)
	{
		i++;
		sector = sector->next_sector;
	}
	return (i);
}

t_sector	*get_a_sector_by_id(t_map *map, int id)
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

float		cross_product(t_point a, t_point b, t_point c)
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

int			is_between(float x, float a, float b)
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

int			is_same_point(t_point a, t_point b)
{
	if (a.x == b.x && a.y == b.y)
		return (1);
	return (0);
}
