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
	info->dirx = -1;
	info->diry = 0;
	info->planex = 0;
	info->planey = 0.66;
	info->movespeed = info->frametime * 2.5;
	info->rotspeed = info->frametime * 0.5;
	info->y_dec = 0;
	info->texture_cap = 0;
	info->mouse_in = 0;
	info->weapon_cap = 0;
}

void			ft_clock(t_var *info)
{
	info->oldtime = info->time;
	info->time = SDL_GetTicks();
	info->frametime = (info->time - info->oldtime) / 1000.0;
}

int                main(int ac, char **av)
{
	t_var info;

	(void)ac;
	(void)av;
	if (!(init_win1(&info)))
		return (0);
	if (!(init_win2(&info)))
		return (0);
	ft_init_pour_linstant(&info);
	//start_doom(&info);
	t_render renderer;

	renderer.wall_y0 = 200;
	renderer.wall_y1 = 700;
	renderer.x		= 13;
	for (renderer.x = 13; renderer.x < 500; renderer.x++)
		draw_tex(&info, &renderer);
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
	SDL_Event e;
	int quit = 0;
	while (!quit)
	{
			SDL_RenderPresent(info.renderer);

		while(SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quit = 1;
			if (e.type == SDL_KEYDOWN)
				quit = 1;
			if (e.type == SDL_MOUSEBUTTONDOWN)
				quit = 1;
		}
			
	}
	SDL_RenderPresent(info.renderer);
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
