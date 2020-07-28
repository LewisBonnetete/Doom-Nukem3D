/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/28 13:35:02 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem_edit.h"

void	del_items_if_in_sector(t_item *items, t_sector *sector)
{
	t_item	*item;
	t_point	new;

	item = items;
	while (item)
	{
		new.x = item->x;
		new.y = item->y;
		if (is_in_sector_spawn(new, sector))
			del_item(sector->map, item->x, item->y);
		item = item->next_item;
	}
}

int		main(void)
{
	t_map	map;
	t_var	info;

	if (!(init_win1(&info)))
		exit_edit(&info, &map);
	else if (!(init_win2(&info)))
		exit_edit(&info, &map);
	else if (!(init_win3(&info)))
		exit_edit(&info, &map);
	else if (!editer(&info, &map))
		exit_edit(&info, &map);
	return (exit_edit(&info, &map));
}
