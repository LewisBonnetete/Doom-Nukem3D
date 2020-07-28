/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/28 13:27:07 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem_edit.h"

void	del_objects(t_map *map)
{
	t_enemy		*enemy;
	t_item		*item;
	t_prop		*prop;

	enemy = map->enemys;
	item = map->items;
	prop = map->props;
	if (prop)
	{
		map->props = map->props->next_prop;
		free(prop->name);
		free(prop);
	}
	if (item)
	{
		map->items = map->items->next_item;
		free(item->name);
		free(item);
	}
	if (enemy)
	{
		map->enemys = map->enemys->next_enemy;
		free(enemy->name);
		free(enemy);
	}
}

void	destroy_map(t_var *info, t_map *map)
{
	while (map->sectors)
		del_sector(info, map);
	while (map->items || map->enemys || map->props)
		del_objects(map);
	ft_putendl("Objects Deleted");
}

int		exit_edit(t_var *info, t_map *map)
{
	destroy_map(info, map);
	TTF_CloseFont(info->font);
	TTF_Quit();
	SDL_DestroyRenderer(info->renderer);
	SDL_DestroyWindow(info->window);
	SDL_Quit();
	ft_putendl("Exiting editor properly.");
	exit(0);
	return (0);
}
