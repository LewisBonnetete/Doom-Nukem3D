/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:04:28 by lewis             #+#    #+#             */
/*   Updated: 2020/07/27 14:02:01 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

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
		return (0);
	}
	if (!(info->image = SDL_CreateRGBSurface(0, WINDOW_W,
	WINDOW_H, 32, RMASK, GMASK, BMASK, AMASK)))
	{
		ft_putstr("Erreur SDL_CreateRGBSurface :\n");
		ft_putendl(SDL_GetError());
		return (0);
	}
	return (1);
}

int		init_win3(t_var *info)
{
	if (TTF_Init() == -1)
	{
		ft_putstr("Erreur TTF_init :\n");
		return (0);
	}
	info->font = TTF_OpenFont("./frameworks/arial.ttf", 22);
	return (1);
}
