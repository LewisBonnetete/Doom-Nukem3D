/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:04:28 by lewis             #+#    #+#             */
/*   Updated: 2020/07/27 15:44:16 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void			ft_init_pour_linstant(t_var *info)
{
	info->frametime = 0.03;
	info->rotspeed = info->frametime * 1;
	info->d_gun = 0;
	info->d_gunb = 0;
	info->clock = 0;
	info->y_dec = 0;
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
	player->hp_p = 100;
	player->ammo = 0;
	player->no_scope = 0;
}

int				init_render(t_var *info, t_render *render, int sector_id)
{
	render->sector_id = sector_id;
	render->s = get_a_sector_by_id(info->map, 1);
	render->wall = NULL;
	render->sec_0 = render->s;
	render->nb_sec = 0;
	render->nbr_items = 0;
	render->cid = info->map->cid;
	render->fid = info->map->fid;
	if (info->map->items && info->map->items->name[0] != 0)
	{
		render->item = init_item(render, info->map->items, 1);
		render->item_0 = render->item;
	}
	init_nb_sec(render->sec_0, render);
	init_tab(render->tab, render->nb_sec);
	return (1);
}
