/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/08 17:27:29 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem_edit.h"

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
