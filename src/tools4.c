/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:04:28 by lewis             #+#    #+#             */
/*   Updated: 2020/07/22 16:56:02 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void			free_map(t_map *map)
{
	free(map->name);
}

void			free_info(t_var *info)
{
	if (info->image)
		SDL_FreeSurface(info->image);
	if (info->texture)
		SDL_DestroyTexture(info->texture);
	if (info->window)
		SDL_DestroyWindow(info->window);
	if (info->map)
		free_map(info->map);
	TTF_CloseFont(info->font);
}

void			ft_exit(t_var *info, t_render *render)
{
	ft_putendl("1");
	if (info)
		free_info(info);
	ft_putendl("2");
	if (render)
		free_render(render);
	ft_putendl("3");
	SDL_Quit();
	exit(0);
}
