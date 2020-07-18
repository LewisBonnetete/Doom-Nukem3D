/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_weapon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 13:45:04 by atyczyns          #+#    #+#             */
/*   Updated: 2020/07/18 17:56:34 by atyczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	move_item(t_item *weapon)
{
	while (weapon && weapon->hold != 1)
	{
		if (weapon->next_item)
			weapon = go_to_item(weapon->next_item, 'a');
		else
			weapon = NULL;
	}
}

void	change_weapon(t_var *info)
{
	t_item	*weapon;

	if (may_weapon(info->render->item_0))
	{
		weapon = go_to_item(info->render->item_0, 'a');
		printf("debut weapon id = %i\n", weapon->id);
		printf("debut weapon hold = %i\n", weapon->hold);
		move_item(weapon);
		printf("ap weapon id = %i\n", weapon->id);
		printf("ap weapon hold = %i\n", weapon->hold);
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
		printf("after weapon id = %i\n", weapon->id);
		printf("after weapon hold = %i\n\n", weapon->hold);
	}
}
