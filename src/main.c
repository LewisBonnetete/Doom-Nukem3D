/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewis <lewis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/05/08 19:16:15 by lewis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

/* void			ft_clock(t_var *info)
{
	info->oldtime = info->time;
	info->time = SDL_GetTicks();
	info->frametime = (info->time - info->oldtime) / 1000.0;
}
*/

int                main(int ac, char **av)
{
	t_var info;
	t_map map;
	t_render renderer;
	t_player	player;

	(void)ac;
	(void)av;
	(void)player;
	(void)renderer;
	info.map = &map;
	if (!(init_win1(&info)))
		return (0);
	if (!(init_win2(&info)))
		return (0);
	//init_artificial_map(&(info.map));
	if (ac != 2 || info_map(av[1], info.map) == 0)
		return (0);
	ft_init_pour_linstant(&info);
	init_player(&player, info.map);
	//free_map(info.map);
	info.player = &player;
	tab_path(&renderer);
	if (WALL_H > 1000 || WALL_H <= 0)
		return (0);
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
		raycasting(&info, &renderer);
		SDL_RenderPresent(info.renderer);
		SDL_DestroyTexture(info.texture);
	}
	SDL_DestroyWindow(info.window);
	SDL_Quit();
	return (0);
}
