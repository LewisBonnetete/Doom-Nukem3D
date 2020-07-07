/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyczyns <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 11:35:50 by atyczyns          #+#    #+#             */
/*   Updated: 2020/07/07 15:47:22 by atyczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_item	*go_to_item(t_item *item, char c)
{
	if (item->name[0] == c)
		return (item);
	else if (item->next_item)
		return	(go_to_item(item->next_item, c));
	return (NULL);
}

t_item	*check_monster(t_item *item, t_var *info, t_item *item_2)
{
	int		dist;
	int		dist_2;
	t_point	p;
	t_point	w;

	if (item->name[0] == 'c' || item->name[0] == 's')
	{
		return (item);
		/*info->render->x = WINDOW_W / 2;
		update_ray(info, info->render);
		calc_item_wall(info->render, item, info);
		if (intersect(info->render->ray, info->render->wall_item) == 1)
		{
			if (item_2 == NULL)
				item_2 = item;
			else
			{
				p.x = info->player->posx;
				p.y = info->player->posy;
				w.x = item->x;
				w.y = item->y;
				dist = calc_dist(p, w);
				w.x = item_2->x;
				w.y = item_2->y;
				dist_2 = calc_dist(p, w);
				if (dist < dist_2)
					item_2 = item;
			}
		}*/
	}
	if (item->next_item)
		return (check_monster(item->next_item, info, item_2));
	return (item_2);
}

void	shoot_ennemy(t_var *info)
{
	t_item	*weapon;
	t_item	*monster;

	if (may_weapon(info->render->item_0))
	{
		weapon = go_to_item(info->render->item_0, 'a');
		while (weapon && weapon->hold != 1)
			weapon = go_to_item(weapon->next_item, 'a');
		if (!weapon)
			weapon = go_to_item(info->render->item_0, 'a');
		weapon->mun -= 1;
		if (weapon->mun <= 0)
			weapon->mun = 0;
		else
		{
			monster = check_monster(info->render->item_0, info, NULL);
			if (monster != NULL)
				monster->pv -= 5;
		}
	}
}
