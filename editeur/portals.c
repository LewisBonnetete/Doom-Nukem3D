/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewis <lewis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/04/17 15:09:28 by lewis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem_edit.h"

int		similar_height(t_wall *w1, t_wall *w2)
{
	if ((w1->a.z == w2->a.z) || (w1->d.z == w2->d.z))
		return (1);
	if (is_between((float)w2->a.z, w1->a.z, w1->d.z) || is_between((float)w2->d.z, w1->a.z, w1->d.z))
		return (1);
	return (0);
}

int		is_same_wall(t_wall *w1, t_wall *w2)
{
	if (is_same_point(w1->a, w2->a) && is_same_point(w1->b, w2->b))
		return (1);
	if (is_same_point(w1->a, w2->b) && is_same_point(w1->b, w2->a))
		return (1);
	return (0);
}

int		find_otherside(t_map *map, t_wall *portal)
{
	t_sector	*sector;
	int			i;

	sector = map->sectors;
	while(sector)
	{
		i = 0;
		while (i < sector->nbr_walls)
		{
			if (portal->sector_id != sector->sector_id && is_same_wall(portal, &sector->walls[i]) && similar_height(portal, &sector->walls[i]))
			{
				if (sector->walls[i].is_portal == 0)
				{
					sector->walls[i].is_portal = 1;
					sector->walls[i].fill_down = portal->fill_down;
					sector->walls[i].fill_up = portal->fill_up;
					sector->walls[i].is_textured = portal->is_textured;
					sector->walls[i].is_transparent = portal->is_transparent;
					sector->walls[i].text_id = portal->text_id;
					sector->walls[i].sector_id_it_leads_to = portal->sector_id;
				}
				portal->sector_id_it_leads_to = sector->sector_id;
				return (1);
			}
			i++;
		}
		sector = sector->next_sector;
	}
	portal->sector_id_it_leads_to = 0;
	return (0);
}

void		portal_test(t_map* map)
{
	t_sector	*sector;
	int			i;

	sector = map->sectors;
	while(sector)
	{
		i = 0;
		while (i < sector->nbr_walls)
		{
			if (sector->walls[i].is_portal)
			{
				printf("%i -> %i  (%i:%i | %i:%i) (%i-%i)\n", sector->sector_id, sector->walls[i].sector_id_it_leads_to, sector->walls[i].a.x, sector->walls[i].a.y, sector->walls[i].b.x, sector->walls[i].b.y, sector->walls[i].b.z, sector->walls[i].c.z);
			}
			i++;
		}
		sector = sector->next_sector;
	}
}

int 	portals(t_map *map)
{
	t_sector	*sector;
	int			i;

	sector = map->sectors;
	while(sector)
	{
		i = 0;
		while (i < sector->nbr_walls)
		{
			if (sector->walls[i].is_portal)
			{
				find_otherside(map, &sector->walls[i]);
			}
			i++;
		}
		sector = sector->next_sector;
	}
	portal_test(map);
	return (1);
}