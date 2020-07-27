/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 16:24:51 by lewis             #+#    #+#             */
/*   Updated: 2020/07/27 15:57:33 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	get_speed(t_var *info)
{
	info->player->movespeed = info->frametime * 0.8;
	info->player->rotspeed = info->frametime * 0.9;
	if (info->player->sprint)
	{
		info->player->movespeed = info->frametime * 4;
		info->player->rotspeed = info->frametime * 1.3;
	}
	else
	{
		info->player->movespeed = info->frametime * 2.0;
		info->player->rotspeed = info->frametime * 2.8;
	}
}

void	mouser(t_var *info)
{
	int y;

	SDL_GetRelativeMouseState(&(info->x_dec), &y);
	info->y_dec += -y;
	if (info->y_dec > 50)
		info->y_dec = 50;
	else if (info->y_dec < -50)
		info->y_dec = -50;
}

void	rotate(t_var *info)
{
	if (!info->mouse_in)
		mouser(info);
	if (info->x_dec > 0)
	{
		rot_left(info);
		info->x_dec = 0;
	}
	else if (info->x_dec < 0)
	{
		rot_right(info);
		info->x_dec = 0;
	}
}

void	mouse_cap(t_var *info, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_m && event.key.state == SDL_PRESSED)
	{
		if (info->mouse_in == 0)
			info->mouse_in = 1;
		else
			info->mouse_in = 0;
	}
	if (event.key.keysym.sym == SDLK_p && event.key.state == SDL_PRESSED)
	{
		if (info->rain == 0)
			info->rain = 1;
		else
			info->rain = 0;
	}
}

int		mouse_test(t_var *info)
{
	if (!info->mouse_in)
		SDL_SetRelativeMouseMode(SDL_TRUE);
	else
		SDL_SetRelativeMouseMode(SDL_FALSE);
	return (1);
}
