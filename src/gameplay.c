/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/15 17:26:12 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void 	crosshair(t_var *info)
{
	t_line line;
	Uint32 color;
	int a;

	a = 8;
	color = WHITE;
	line.x1 = WINDOW_W / 2 + a - 1;
	line.x2 = WINDOW_W / 2 - a;
	line.y1 = WINDOW_H / 2;
	line.y2 = WINDOW_H / 2;
	draw_line(info, &line, color);
	line.x1 = WINDOW_W / 2;
	line.x2 = WINDOW_W / 2;
	line.y1 = WINDOW_H / 2 + a - 1;
	line.y2 = WINDOW_H / 2 - a;
	draw_line(info, &line, color);
}

void	hitmarker(t_var *info)
{
	t_line line;
	Uint32 color;
	int a;
	int b;

	a = 5;
	b = 15;
	color = WHITE;
	line.x1 = WINDOW_W / 2 + a;
	line.x2 = WINDOW_W / 2 + b;
	line.y1 = WINDOW_H / 2 + a;
	line.y2 = WINDOW_H / 2 + b;
	draw_line(info, &line, color);
	line.x1 = WINDOW_W / 2 - a;
	line.x2 = WINDOW_W / 2 - b;
	line.y1 = WINDOW_H / 2 - a;
	line.y2 = WINDOW_H / 2 - b;
	draw_line(info, &line, color);
	line.x1 = WINDOW_W / 2 + a;
	line.x2 = WINDOW_W / 2 + b;
	line.y1 = WINDOW_H / 2 - a;
	line.y2 = WINDOW_H / 2 - b;
	draw_line(info, &line, color);
	line.x1 = WINDOW_W / 2 - a;
	line.x2 = WINDOW_W / 2 - b;
	line.y1 = WINDOW_H / 2 + a;
	line.y2 = WINDOW_H / 2 + b;
	draw_line(info, &line, color);
}

void	hit_ennemy(t_var *info)
{
	t_item *item;

	item = info->render->item_0;
	while (item)
	{
		if (item->x == info->player->no_scopex && item->y == info->player->no_scopey)
		{
			printf("x = %i | y = %i\n", item->x, item->y);
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
			&& item->cap != 3)
			i += 2;
		if (item->name[0] == 's' && same_sector(info, item, player->sector_id)
			&& item->cap != 3)
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
