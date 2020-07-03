/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygon_checks2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/03 14:39:31 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem_edit.h"

int		check_convexity(t_sector *sector)
{
	t_wall		*walls;
	t_convex	convex;
	float		produit;

	walls = sector->walls;
	convex.a = 0;
	convex.got_negative = 0;
	convex.got_positive = 0;
	while (convex.a < sector->nbr_walls)
	{
		convex.b = (convex.a + 1) % sector->nbr_walls;
		convex.c = (convex.b + 1) % sector->nbr_walls;
		produit = cross_product(walls[convex.a].a,
		walls[convex.b].a, walls[convex.c].a);
		if (produit < 0)
		{
			convex.got_negative = 1;
		}
		else if (produit > 0)
			convex.got_positive = 1;
		if (convex.got_negative && convex.got_positive)
			return (0);
		convex.a++;
	}
	return (1);
}

int		check_surrounding(t_sector *sector)
{
	t_sector	*current_sector;
	int			i;

	i = 0;
	current_sector = sector->map->sectors;
	while (current_sector)
	{
		if (current_sector->sector_id != sector->sector_id)
		{
			while (i < current_sector->nbr_walls)
			{
				if (!is_in_sector(current_sector->walls[i].a, sector))
					return (0);
				i++;
			}
			i = 0;
		}
		current_sector = current_sector->next_sector;
	}
	return (1);
}

int		check_self_intersection(t_sector *sector)
{
	int i;
	int	j;

	i = 0;
	while (i < sector->nbr_walls)
	{
		j = 0;
		while (j < sector->nbr_walls)
		{
			if (j != i && sector->walls[i].a.x > 0 && sector->walls[i].b.x > 0
			&& sector->walls[j].a.x > 0 && sector->walls[j].b.x > 0)
			{
				if (!check_wall_intersections(sector->walls[i].a,
				sector->walls[i].b, sector->walls[j]))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int		pnpoly(int nbr_walls, t_wall *walls, t_point first)
{
	int i;
	int j;
	int c;

	i = 0;
	j = nbr_walls - 1;
	c = 0;
	while (i < nbr_walls)
	{
		if (!is_new_point_in_sector(first, walls))
			return (0);
		if (((walls[i].a.y > first.y) != (walls[j].a.y > first.y))
		&& (first.x < (walls[j].a.x - walls[i].a.x) * (first.y - walls[i].a.y)
		/ (walls[j].a.y - walls[i].a.y) + walls[i].a.x))
			c = !c;
		j = i++;
	}
	return (c);
}

int		is_in_sector(t_point first, t_sector *sector)
{
	if (pnpoly(sector->nbr_walls, sector->walls, first))
	{
		return (0);
	}
	return (1);
}
