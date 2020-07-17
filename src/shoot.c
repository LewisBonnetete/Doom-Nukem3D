/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 11:35:50 by atyczyns          #+#    #+#             */
/*   Updated: 2020/07/17 16:29:39 by trabut           ###   ########.fr       */
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

void	shoot_ennemy(t_var *info)
{
	t_item	*weapon;

	if (may_weapon(info->render->item_0))
	{
		weapon = go_to_item(info->render->item_0, 'a');
		while (weapon && weapon->hold != 1)
			weapon = go_to_item(weapon->next_item, 'a');
		if (!weapon)
			weapon = go_to_item(info->render->item_0, 'a');
		if (info->player->no_scope != 0 && weapon->mun > 0)
			hit_ennemy(info);
		weapon->mun -= 1;
		if (weapon->mun <= 0)
			weapon->mun = 0;
	}
}
