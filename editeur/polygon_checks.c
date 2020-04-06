/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygon_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewis <lewis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/04/06 16:25:18 by lewis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem_edit.h"

int		check_convexity(t_sector *sector)
{
	t_wall	*walls;
	int 	a;
	int 	b;
	int 	c;
	float 	produit;
	int		got_negative;
	int		got_positive;

	walls = sector->walls;
	a = 0;
	got_negative = 0;
	got_positive = 0;
	while (a < sector->nbr_walls)
	{
		b = (a + 1) % sector->nbr_walls;
		c = (b + 1) % sector->nbr_walls;
		produit = cross_product(walls[a].a, walls[b].a, walls[c].a);
		if (produit < 0)
        {
            got_negative = 1;
        }
        else if (produit > 0)
            got_positive = 1;
        if (got_negative && got_positive)
			return (0);
		a++;
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
			if (j != i)
			{
				if(!check_wall_intersections(sector->walls[i].a, sector->walls[i].b, sector->walls[j]))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}