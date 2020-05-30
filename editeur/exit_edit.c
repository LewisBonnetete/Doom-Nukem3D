/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewis <lewis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/05/30 11:52:59 by lewis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem_edit.h"

void	destroy_map(t_var *info, t_map *map)
{
	while(map->sectors)
		del_sector(info, map);
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