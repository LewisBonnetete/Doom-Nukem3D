/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_weapon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 13:45:04 by atyczyns          #+#    #+#             */
/*   Updated: 2020/07/23 15:04:33 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	change_weapon(t_var *info)
{
	t_item	*weapon;

	if (may_weapon(info->render->item_0))
	{
		weapon = go_to_item(info->render->item_0, 'a');
		while (weapon && weapon->hold != 1)
			weapon = go_to_item(weapon->next_item, 'a');
		if (!weapon)
			weapon = go_to_item(info->render->item_0, 'a');
		else
		{
			weapon->hold = 0;
			weapon = weapon->next_item;
			while (weapon != NULL && (weapon->hold != 0 || weapon->cap != 2))
				weapon = go_to_item(weapon->next_item, 'a');
			if (!weapon)
				weapon = go_to_item(info->render->item_0, 'a');
		}
		weapon->hold = 1;
	}
}
