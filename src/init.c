/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewis <lewis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/04/17 15:10:46 by lewis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"


void	init_box(t_map *map)
{
	int i;

	i = -1;
	map->box.nbr_walls = 4;
	while(++i < 4)
		map->box.walls[i].is_portal = 0;
	i = -1;
	while(++i < 4)
		map->box.walls[i].is_textured = 1;
	i = -1;
	while(++i < 4)
		map->box.walls[i].is_transparent = 0;
	i = -1;
	while(++i < 4)
		map->box.walls[i].text_id = 0;
	i = -1;
	while(++i < 4)
		map->box.walls[i].sector_id = 0;
	i = -1;
	while(++i < 4)
		map->box.walls[i].wall_id = i;
	//premier mur a:
	map->box.walls[0].a.x = 0;
	map->box.walls[0].a.y = 0;
	map->box.walls[0].a.z = 0;
	//premier mur b:
	map->box.walls[0].b.x = map->box.size;
	map->box.walls[0].b.y = 0;
	map->box.walls[0].b.z = 0;
	//premier mur c:
	map->box.walls[0].c.x = map->box.size;
	map->box.walls[0].c.y = 0;
	map->box.walls[0].c.z = map->box.size;
	//premier mur d:
	map->box.walls[0].d.x = 0;
	map->box.walls[0].d.y = 0;
	map->box.walls[0].d.z = map->box.size;

	//troisieme mur b:
	map->box.walls[2].b.x = 0;
	map->box.walls[2].b.y = map->box.size;
	map->box.walls[2].b.z = 0;
	//troisieme mur a:
	map->box.walls[2].a.x = map->box.size;
	map->box.walls[2].a.y = map->box.size;
	map->box.walls[2].a.z = 0;
	//troisieme mur c:
	map->box.walls[2].c.x = 0;
	map->box.walls[2].c.y = map->box.size;
	map->box.walls[2].c.z = map->box.size;
	//troisieme mur d:
	map->box.walls[2].d.x = map->box.size;
	map->box.walls[2].d.y = map->box.size;
	map->box.walls[2].d.z = map->box.size;

	//deuxieme mur
	map->box.walls[1].a = map->box.walls[0].b;
	map->box.walls[1].b = map->box.walls[2].a;
	map->box.walls[1].c = map->box.walls[2].d;
	map->box.walls[1].d = map->box.walls[0].c;

	//quatrieme mur:
	map->box.walls[3].a = map->box.walls[2].b;
	map->box.walls[3].b = map->box.walls[0].a;
	map->box.walls[3].c = map->box.walls[0].d;
	map->box.walls[3].d = map->box.walls[2].c;

	//floor:
	map->box.floor.a = map->box.walls[0].d;
	map->box.floor.b = map->box.walls[1].d;
	map->box.floor.c = map->box.walls[2].d;
	map->box.floor.d = map->box.walls[3].d;

	//ceilling:
	map->box.celling.a = map->box.walls[0].a;
	map->box.celling.b = map->box.walls[1].a;
	map->box.celling.c = map->box.walls[2].a;
	map->box.celling.d = map->box.walls[3].a;
}

void	init_map(t_map *map)
{
	map->spawn.x = -1;
	map->spawn.y = -1;
	map->spawn.z = -1;
	map->sectors = NULL;
}

void	init_var(t_var *info)
{
	(void)info;
}

void	init_artificial_map(t_map *map)
{
	t_sector	*sector2;

	map->spawn.x = 2;
	map->spawn.y = 2;
	map->spawn.z = 1;
	map->sectors = malloc(sizeof(t_sector));

	map->sectors->nbr_walls = 4;
	map->sectors->light = 0;
	map->sectors->sector_id = 1;
	map->sectors->walls = malloc(sizeof(t_wall) * map->sectors->nbr_walls);
	map->sectors->next_sector = malloc(sizeof(t_sector));

	sector2 = map->sectors->next_sector;
	sector2->nbr_walls = 4;
	sector2->light = 0;
	sector2->sector_id = 2;
	sector2->walls = malloc(sizeof(t_wall) * sector2->nbr_walls);
	sector2->next_sector = NULL;

	map->sectors->walls[0].a.x = 1;
	map->sectors->walls[0].a.y = 1;
	map->sectors->walls[0].a.z = 4;
	map->sectors->walls[0].b.x = 4;
	map->sectors->walls[0].b.y = 1;
	map->sectors->walls[0].b.z = 4;
	map->sectors->walls[0].c.x = 4;
	map->sectors->walls[0].c.y = 1;
	map->sectors->walls[0].c.z = 1;
	map->sectors->walls[0].d.x = 1;
	map->sectors->walls[0].d.y = 1;
	map->sectors->walls[0].d.z = 1;
	map->sectors->walls[0].text_id = 1;
	map->sectors->walls[0].wall_id = 0;
	map->sectors->walls[0].is_portal = 0;
	map->sectors->walls[0].is_transparent = 0;
	map->sectors->walls[0].is_textured = 1;
	map->sectors->walls[0].fill_up = 0;
	map->sectors->walls[0].fill_down = 0;
	map->sectors->walls[0].sector_id = 1;
	map->sectors->walls[0].sector_id_it_leads_to = 0;

	map->sectors->walls[1].a.x = 4;
	map->sectors->walls[1].a.y = 1;
	map->sectors->walls[1].a.z = 4;
	map->sectors->walls[1].b.x = 4;
	map->sectors->walls[1].b.y = 4;
	map->sectors->walls[1].b.z = 4;
	map->sectors->walls[1].c.x = 4;
	map->sectors->walls[1].c.y = 4;
	map->sectors->walls[1].c.z = 1;
	map->sectors->walls[1].d.x = 4;
	map->sectors->walls[1].d.y = 1;
	map->sectors->walls[1].d.z = 1;
	map->sectors->walls[1].text_id = 1;
	map->sectors->walls[1].wall_id = 1;
	map->sectors->walls[1].is_portal = 0;
	map->sectors->walls[1].is_transparent = 0;
	map->sectors->walls[1].is_textured = 1;
	map->sectors->walls[1].fill_up = 0;
	map->sectors->walls[1].fill_down = 0;
	map->sectors->walls[1].sector_id = 1;
	map->sectors->walls[1].sector_id_it_leads_to = 0;

	map->sectors->walls[2].a.x = 4;
	map->sectors->walls[2].a.y = 4;
	map->sectors->walls[2].a.z = 4;
	map->sectors->walls[2].b.x = 1;
	map->sectors->walls[2].b.y = 4;
	map->sectors->walls[2].b.z = 4;
	map->sectors->walls[2].c.x = 4;
	map->sectors->walls[2].c.y = 4;
	map->sectors->walls[2].c.z = 1;
	map->sectors->walls[2].d.x = 4;
	map->sectors->walls[2].d.y = 4;
	map->sectors->walls[2].d.z = 1;
	map->sectors->walls[2].text_id = 1;
	map->sectors->walls[2].wall_id = 2;
	map->sectors->walls[2].is_portal = 0;
	map->sectors->walls[2].is_transparent = 0;
	map->sectors->walls[2].is_textured = 1;
	map->sectors->walls[2].fill_up = 0;
	map->sectors->walls[2].fill_down = 0;
	map->sectors->walls[2].sector_id = 1;
	map->sectors->walls[2].sector_id_it_leads_to = 0;
	
	map->sectors->walls[3].a.x = 1;
	map->sectors->walls[3].a.y = 4;
	map->sectors->walls[3].a.z = 4;
	map->sectors->walls[3].b.x = 1;
	map->sectors->walls[3].b.y = 1;
	map->sectors->walls[3].b.z = 4;
	map->sectors->walls[3].c.x = 1;
	map->sectors->walls[3].c.y = 1;
	map->sectors->walls[3].c.z = 1;
	map->sectors->walls[3].d.x = 1;
	map->sectors->walls[3].d.y = 4;
	map->sectors->walls[3].d.z = 1;
	map->sectors->walls[3].text_id = 1;
	map->sectors->walls[3].wall_id = 3;
	map->sectors->walls[3].is_portal = 0;
	map->sectors->walls[3].is_transparent = 0;
	map->sectors->walls[3].is_textured = 1;
	map->sectors->walls[3].fill_up = 0;
	map->sectors->walls[3].fill_down = 0;
	map->sectors->walls[3].sector_id = 1;
	map->sectors->walls[3].sector_id_it_leads_to = 0;

	map->box.floor.a = map->sectors->walls[0].d;
	map->box.floor.b = map->sectors->walls[1].d;
	map->box.floor.c = map->sectors->walls[2].d;
	map->box.floor.d = map->sectors->walls[3].d;

	map->box.celling.a = map->sectors->walls[0].a;
	map->box.celling.b = map->sectors->walls[1].a;
	map->box.celling.c = map->sectors->walls[2].a;
	map->box.celling.d = map->sectors->walls[3].a;

	//2 sector
	
	sector2->walls[0].a.x = 5;
	sector2->walls[0].a.y = 5;
	sector2->walls[0].a.z = 6;
	sector2->walls[0].b.x = 8;
	sector2->walls[0].b.y = 5;
	sector2->walls[0].b.z = 6;
	sector2->walls[0].c.x = 8;
	sector2->walls[0].c.y = 5;
	sector2->walls[0].c.z = 2;
	sector2->walls[0].d.x = 5;
	sector2->walls[0].d.y = 5;
	sector2->walls[0].d.z = 2;
	sector2->walls[0].text_id = 1;
	sector2->walls[0].wall_id = 0;
	sector2->walls[0].is_portal = 0;
	sector2->walls[0].is_transparent = 0;
	sector2->walls[0].is_textured = 1;
	sector2->walls[0].fill_up = 0;
	sector2->walls[0].fill_down = 0;
	sector2->walls[0].sector_id = 2;
	sector2->walls[0].sector_id_it_leads_to = 0;

	sector2->walls[1].a.x = 8;
	sector2->walls[1].a.y = 5;
	sector2->walls[1].a.z = 6;
	sector2->walls[1].b.x = 8;
	sector2->walls[1].b.y = 8;
	sector2->walls[1].b.z = 6;
	sector2->walls[1].c.x = 8;
	sector2->walls[1].c.y = 8;
	sector2->walls[1].c.z = 2;
	sector2->walls[1].d.x = 8;
	sector2->walls[1].d.y = 5;
	sector2->walls[1].d.z = 2;
	sector2->walls[1].text_id = 1;
	sector2->walls[1].wall_id = 1;
	sector2->walls[1].is_portal = 0;
	sector2->walls[1].is_transparent = 0;
	sector2->walls[1].is_textured = 1;
	sector2->walls[1].fill_up = 0;
	sector2->walls[1].fill_down = 0;
	sector2->walls[1].sector_id = 2;
	sector2->walls[1].sector_id_it_leads_to = 0;

	sector2->walls[2].a.x = 8;
	sector2->walls[2].a.y = 8;
	sector2->walls[2].a.z = 6;
	sector2->walls[2].b.x = 5;
	sector2->walls[2].b.y = 8;
	sector2->walls[2].b.z = 6;
	sector2->walls[2].c.x = 8;
	sector2->walls[2].c.y = 8;
	sector2->walls[2].c.z = 2;
	sector2->walls[2].d.x = 8;
	sector2->walls[2].d.y = 8;
	sector2->walls[2].d.z = 2;
	sector2->walls[2].text_id = 1;
	sector2->walls[2].wall_id = 2;
	sector2->walls[2].is_portal = 1;
	sector2->walls[2].is_transparent = 0;
	sector2->walls[2].is_textured = 1;
	sector2->walls[2].fill_up = 0;
	sector2->walls[2].fill_down = 0;
	sector2->walls[2].sector_id = 2;
	sector2->walls[2].sector_id_it_leads_to = 0;
	
	sector2->walls[3].a.x = 5;
	sector2->walls[3].a.y = 8;
	sector2->walls[3].a.z = 6;
	sector2->walls[3].b.x = 5;
	sector2->walls[3].b.y = 5;
	sector2->walls[3].b.z = 6;
	sector2->walls[3].c.x = 5;
	sector2->walls[3].c.y = 5;
	sector2->walls[3].c.z = 2;
	sector2->walls[3].d.x = 5;
	sector2->walls[3].d.y = 8;
	sector2->walls[3].d.z = 2;
	sector2->walls[3].text_id = 1;
	sector2->walls[3].wall_id = 3;
	sector2->walls[3].is_portal = 0;
	sector2->walls[3].is_transparent = 0;
	sector2->walls[3].is_textured = 1;
	sector2->walls[3].fill_up = 0;
	sector2->walls[3].fill_down = 0;
	sector2->walls[3].sector_id = 2;
	sector2->walls[3].sector_id_it_leads_to = 0;
}