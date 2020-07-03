/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/03 17:00:26 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		same_sector(t_var *info, t_item *item, int sector_id)
{
	t_sector	*sector;
	t_point		pt;
	
	sector = get_a_sector_by_id(info->map, sector_id);
	pt.x = item->x;
	pt.y = item->y;
	if (!is_in_sector(pt, sector))
		return (1);
	return (0);
}

int		enemys_in_sector(t_var *info, t_player *player)
{
	t_item *item;
	int i;
	
	i = 0;
	item = info->render->item_0;
	while (item)
	{
		if (item->name[0] == 'c' && same_sector(info, item, player->sector_id))
			i++;
		item = item->next_item;
	}
	return (i);
	
}

int		gameplay(t_var *info)
{
	info->clock++;
	if (info->clock > 100)
		info->clock = 0;
	if (info->clock == 50)
		info->player->hp -= DMG * enemys_in_sector(info, info->player);
	if (info->player->hp <= 0)
		return (0);
	return (1);
}