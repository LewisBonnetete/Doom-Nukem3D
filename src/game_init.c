/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:04:28 by lewis             #+#    #+#             */
/*   Updated: 2020/07/09 15:36:44 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void			ft_init_pour_linstant(t_var *info)
{
	info->frametime = 0.03;
	info->rotspeed = info->frametime * 1.5;
	info->d_gun = 0;
	info->d_gunb = 0;
	info->clock = 0;
}

void			init_player(t_player *player, t_map *map)
{
	player->sector_id = 1;
	player->posx = (double)map->spawn.x;
	player->posy = (double)map->spawn.y;
	player->posz = (double)map->spawn.z;
	player->dx = 1.0;
	player->dy = 0.0;
	player->dz = 0.0;
	player->planex = 0.0;
	player->planey = 0.6;
	player->frametime = 0.03;
	player->movespeed = player->frametime * 2.5;
	player->weapon = NULL;
	player->hp = 100;
	player->ammo = 0;
}

void			init_render(t_var *info, t_render *render,
				int x0, int sector_id)
{
	render->sector_id = sector_id;
	render->s = get_a_sector_by_id(info->map, 1);
	render->wall = NULL;
	render->sec_0 = render->s;
	render->nb_sec = 0;
	render->nbr_items = 0;
	(void)x0;
	if (info->map->items && info->map->items->name[0] != 0)
	{
		render->item = init_item(render, info->map->items, 0);
		render->item_0 = render->item;
	}
	init_nb_sec(render->sec_0, render);
}
