/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/08 13:15:24 by atyczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

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
	if (ac != 2 || info_map(av[1], info.map) == 0)
	{
		free_map(info.map);
		return (0);
	}
	if (!(init_win1(&info)) || !(init_win2(&info)) || !(init_win3(&info)))
	{
		free_info(&info);
		return (0);
	}
	//init_artificial_map(&(info.map));
	ft_init_pour_linstant(&info);
	init_player(&player, info.map);
	//free_map(info.map);
	info.player = &player;
	init_render(&info, &renderer, 0, info.player->sector_id);
	info.render = &renderer;
	if (tab_path(&renderer) == 0 || tab_path_text(&renderer) == 0)
		ft_exit(&info, &renderer);
	if (WALL_H > 1000 || WALL_H <= 0)
		ft_exit(&info, &renderer);
	while (dealer(&info))
	{
		if (!(info.texture = SDL_CreateTextureFromSurface(info.renderer, info.image)))
		{
			ft_putstr("Erreur CreateTextureFromSurface :\n");
			ft_putendl(SDL_GetError());
			SDL_DestroyWindow(info.window);
			SDL_Quit();
			ft_exit(&info, &renderer);
		}
		if (SDL_RenderCopy(info.renderer, info.texture, NULL, NULL))
		{
			ft_putstr("Erreur RenderCopy :\n");
			ft_putendl(SDL_GetError());
			SDL_DestroyWindow(info.window);
			SDL_Quit();
			ft_exit(&info, &renderer);
		}
		if (raycasting(&info, &renderer) == 0)
			ft_exit(&info, &renderer);
		SDL_RenderPresent(info.renderer);
		SDL_DestroyTexture(info.texture);
		if (!gameplay(&info))
			ft_exit(&info, &renderer);
	}
	SDL_DestroyWindow(info.window);
	SDL_Quit();
	ft_exit(&info, &renderer);
	return (0);
}
