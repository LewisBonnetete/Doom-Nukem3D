/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/27 16:39:07 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	hit_ennemy(t_var *info)
{
	t_item *item;

	item = info->render->item_0;
	while (item)
	{
		if (item->id == info->player->no_scope)
		{
			hitmarker(info);
			item->pv -= 5;
		}
		item = item->next_item;
	}
}

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
	t_item	*item;
	int		i;

	i = 0;
	item = info->render->item_0;
	while (item)
	{
		if (item->name[0] == 'c' && same_sector(info, item, player->sector_id)
			&& item->cap != 3 && item->pv > 5)
			i += 2;
		if (item->name[0] == 's' && same_sector(info, item, player->sector_id)
			&& item->cap != 3 && item->pv > 5)
			i += 1;
		item = item->next_item;
	}
	return (i);
}

int		gameplay(t_var *info)
{
	crosshair(info);
	info->clock++;
	if (info->clock > 100)
		info->clock = 0;
	if (info->clock == 50)
		info->player->hp -= DMG * enemys_in_sector(info, info->player);
	if (info->player->hp <= 0)
	{
		ft_putendl("t mor.");
		ft_exit(info, info->render);
	}
	return (1);
}
