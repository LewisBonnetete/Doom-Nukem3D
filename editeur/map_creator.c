/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/23 17:13:34 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem_edit.h"

int			create_wall_edit(t_sector *sector, int *height,
int i, SDL_Event event)
{
	float temp;

	sector->walls[i].sector_id = sector->sector_id;
	sector->walls[i].wall_id = i;
	temp = (float)event.button.x / (float)(WINDOW_H - 50) * sector->map->size;
	temp = round(temp);
	sector->walls[i].a.x = temp;
	sector->walls[i].d.x = temp;
	temp = (float)event.button.y / (float)(WINDOW_H - 50) * sector->map->size;
	temp = round(temp);
	sector->walls[i].a.y = temp;
	sector->walls[i].d.y = temp;
	sector->walls[i].d.z = height[0];
	sector->walls[i].a.z = height[1];
	wall_fusion(sector, i);
	get_portal_info(&sector->walls[i - 1]);
	get_textures(&sector->walls[i - 1]);
	return (1);
}

void		close_sector(t_sector *sector, int i)
{
	sector->walls[i].b.x = sector->walls[0].a.x;
	sector->walls[i].c.x = sector->walls[0].d.x;
	sector->walls[i].b.y = sector->walls[0].a.y;
	sector->walls[i].c.y = sector->walls[0].d.y;
	sector->walls[i].c.z = sector->walls[0].d.z;
	sector->walls[i].b.z = sector->walls[0].a.z;
	get_portal_info(&sector->walls[i]);
	get_textures(&sector->walls[i]);
}

int			init_first_sector(t_var *info, t_sector *sector, t_map *map)
{
	int height[2];

	init_sector(sector);
	sector->sector_id = 1;
	get_height_sector(height);
	get_nbr_walls_sector_textures(sector);
	sector->map = map;
	sector->info = info;
	sector->next_sector = NULL;
	if (!(sector->walls = (t_wall*)malloc(sizeof(t_wall) * sector->nbr_walls)))
		return (0);
	init_walls(sector->walls, sector->nbr_walls);
	if (!get_walls_sector(map, sector, height))
		return (0);
	return (1);
}

int			init_new_sector(t_var *info, t_sector *sector, t_map *map)
{
	int height[2];

	init_sector(sector->next_sector);
	sector->next_sector->sector_id = sector->sector_id + 1;
	sector = sector->next_sector;
	get_height_sector(height);
	get_nbr_walls_sector_textures(sector);
	sector->map = map;
	sector->info = info;
	sector->floor.text_id = map->fid;
	sector->celling.text_id = map->cid;
	sector->next_sector = NULL;
	sector->sector_id = sector->sector_id;
	if (!(sector->walls = (t_wall*)malloc(sizeof(t_wall) * sector->nbr_walls)))
		return (0);
	init_walls(sector->walls, sector->nbr_walls);
	if (!get_walls_sector(map, sector, height))
		return (0);
	return (1);
}

int			create_sector(t_var *info, t_map *map)
{
	t_sector *sector;

	sector = map->sectors;
	if (sector)
	{
		sector = get_to_last_sector(map->sectors);
		if (sector->sector_id >= 10)
		{
			ft_putendl("map cannot have more than 10 sectors");
			return (0);
		}
		if (!(sector->next_sector = (t_sector*)malloc(sizeof(t_sector)))
		|| (!init_new_sector(info, sector, map)))
			return (exit_edit(info, map));
	}
	else
	{
		if (!(map->sectors = (t_sector*)malloc(sizeof(t_sector)))
		|| (!init_first_sector(info, map->sectors, map)))
			return (exit_edit(info, map));
	}
	return (1);
}
