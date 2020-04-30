/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 15:01:16 by trabut            #+#    #+#             */
/*   Updated: 2020/01/29 14:02:02 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/doom-nukem.h"

int		init_win1(t_var *info)
{
	if (0 != SDL_Init(SDL_INIT_VIDEO
	| SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_EVENTS))
	{
		ft_putstr("Erreur SDL_Init\n");
		ft_putendl(SDL_GetError());
		return (0);
	}
	if (!(info->window = SDL_CreateWindow("doom_nukem",
	SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
	WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN)))
	{
		ft_putstr("Erreur SDL_CreateWindow :\n");
		ft_putendl(SDL_GetError());
		SDL_Quit();
		return (0);
	}
	return (1);
}

int		init_win2(t_var *info)
{
	if (!(info->renderer = SDL_CreateRenderer(info->window,
	-1, SDL_RENDERER_ACCELERATED)))
	{
		ft_putstr("Erreur SDL_CreateRenderer :\n");
		ft_putendl(SDL_GetError());
		SDL_DestroyWindow(info->window);
		SDL_Quit();
		return (0);
	}
	if (!(info->image = SDL_CreateRGBSurface(0, WINDOW_W,
	WINDOW_H, 32, RMASK, GMASK, BMASK, AMASK)))
	{
		ft_putstr("Erreur SDL_CreateRGBSurface :\n");
		ft_putendl(SDL_GetError());
		SDL_DestroyWindow(info->window);
		SDL_Quit();
		return (0);
	}
	return (1);
}
