/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 11:35:50 by atyczyns          #+#    #+#             */
/*   Updated: 2020/07/09 14:49:03 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_item	*go_to_item(t_item *item, char c)
{
	if (item->name[0] == c)
		return (item);
	else if (item->next_item)
		return (go_to_item(item->next_item, c));
	return (NULL);
}

t_item	*check_monster(t_item *item, t_var *info, t_item *item_2)
{
	int		dist;
	int		dist_2;
	t_point	p;
	t_point	w;

	if ((item->name[0] == 'c' && item->pv > 0) ||
		(item->name[0] == 's' && item->pv > 0))
		return (item);
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
