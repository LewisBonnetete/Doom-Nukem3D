/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/02/06 15:09:32 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void			ft_init_pour_linstant(t_var *info)
{
	info->frametime = 0.03;
//	info->movespeed = info->frametime * 2.5;
	info->rotspeed = info->frametime * 0.5;
//	info->y_dec = 0;
//	info->texture_cap = 0;
//	info->mouse_in = 0;
//	info->weapon_cap = 0;
}

/* void			ft_clock(t_var *info)
{
	info->oldtime = info->time;
	info->time = SDL_GetTicks();
	info->frametime = (info->time - info->oldtime) / 1000.0;
}
*/

void	init_player(t_player *player, t_map *map)
{
	player->sector_id = map->sectors->sector_id;
	player->posx = (double)map->spawn.x;
	player->posy = (double)map->spawn.y;
	player->posz = (double)map->spawn.z;
	player->dx = 1.0;
	player->dy = 0.0;
	player->dz = 0.0;
	player->planex = 0.0;
	player->planey = 0.4;
}

int				main(int ac, char **av)
{
	t_var		info;
	t_render	renderer;
	t_player	player;

	(void)ac;
	(void)av;
	if (!(init_win1(&info)))
		return (0);
	if (!(init_win2(&info)))
		return (0);
	//start_doom(&info);
	ft_init_pour_linstant(&info);
	init_artificial_map(&(info.map));
	init_player(&player, &info.map);
	info.player = &player;
	while (dealer(&info, &renderer))
	{
		if (!(info.texture = SDL_CreateTextureFromSurface(info.renderer, info.image)))
		{
			ft_putstr("Erreur CreateTextureFromSurface :\n");
			ft_putendl(SDL_GetError());
			SDL_DestroyWindow(info.window);
			SDL_Quit();
			return (0);
		}
		if (SDL_RenderCopy(info.renderer, info.texture, NULL, NULL))
		{
			ft_putstr("Erreur RenderCopy :\n");
			ft_putendl(SDL_GetError());
			SDL_DestroyWindow(info.window);
			SDL_Quit();
			return (0);
		}
		SDL_RenderPresent(info.renderer);
		SDL_DestroyTexture(info.texture);
	}
	SDL_DestroyWindow(info.window);
	SDL_Quit();
	return (0);
}

/* int            start_doom(t_var *info)
{
	if (1)
		editeur(info);
	if (2)
		play(info, str);
	if (3);
		leave(info);
}*/
