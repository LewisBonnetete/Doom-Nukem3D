/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:04:28 by lewis             #+#    #+#             */
/*   Updated: 2020/07/09 15:10:13 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void			free_map(t_map *map)
{
	free(&map);
}

void			free_player(t_player *player)
{
	if (player->weapon)
		free_item(player->weapon);
	free(&player);
}

void			free_info(t_var *info)
{
	if (info->image)
		SDL_FreeSurface(info->image);
	if (info->texture)
		SDL_DestroyTexture(info->texture);
	if (info->window)
		SDL_DestroyWindow(info->window);
	if (info->render)
		free_render(info->render);
	if (info->map)
		free_map(info->map);
	if (info->player)
		free_player(info->player);
	free(&info);
}

void			ft_exit(t_var *info, t_render *render)
{
	if (info)
		free_info(info);
	(void)render;
	SDL_Quit();
	exit(0);
}