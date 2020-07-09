/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/09 12:41:18 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"


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
