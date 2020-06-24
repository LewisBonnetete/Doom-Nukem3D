/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/06/24 15:20:19 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem_edit.h"

void	init_wall(t_wall *wall)
{
	wall->fill_down = 0;
	wall->fill_up = 0;
	wall->is_portal = 0;
	wall->is_textured = 0;
	wall->is_transparent = 0;
	wall->sector_id = 0;
	wall->sector_id_it_leads_to = 0;
	wall->text_id = 0;
	wall->wall_id = 0;
	wall->a.x = 0;
	wall->a.y = 0;
	wall->a.z = 0;
	wall->b.x = 0;
	wall->b.y = 0;
	wall->b.z = 0;
	wall->c.x = 0;
	wall->c.y = 0;
	wall->c.z = 0;
	wall->d.x = 0;
	wall->d.y = 0;
	wall->d.z = 0;
}

void	init_map(t_map *map)
{
	map->spawn.x = -1;
	map->spawn.y = -1;
	map->spawn.z = -1;
	map->i = 0;
	map->sectors = NULL;
	map->items = NULL;
	map->props = NULL;
	map->enemys = NULL;
}

void	init_var(t_var *info)
{
	(void)info;
}

void	dealers_init(t_input_edit *input_edit)
{
	input_edit->mouse_x = 0;
	input_edit->mouse_y = 0;
	input_edit->right_click = 0;
	input_edit->left_click = 0;
	input_edit->del = 0;
	input_edit->t_s = 0;
	input_edit->t_n = 0;
	input_edit->t_0 = 0;
	input_edit->t_1 = 0;
	input_edit->t_2 = 0;
	input_edit->t_3 = 0;
	input_edit->t_4 = 0;
	input_edit->t_5 = 0;
	input_edit->t_6 = 0;
	input_edit->t_7 = 0;
	input_edit->t_8 = 0;
	input_edit->t_9 = 0;
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
