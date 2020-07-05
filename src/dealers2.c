/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 16:24:51 by lewis             #+#    #+#             */
/*   Updated: 2020/07/03 16:36:15 by trabut           ###   ########.fr       */
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
	info->y_dec += y;
	if (info->y_dec > WINDOW_H + 500)
		info->y_dec = WINDOW_H + 500;
	else if (info->y_dec < -500)
		info->y_dec = -500;
}

// void	rot_right(t_var *info)
// {
// 	info->olddirx = info->dirx;
// 	info->dirx = info->dirx * cos(-info->rotspeed) - info->diry
// 	* sin(-info->rotspeed);
// 	info->diry = info->olddirx * sin(-info->rotspeed) + info->diry
// 	* cos(-info->rotspeed);
// 	info->oldplanex = info->planex;
// 	info->planex = info->planex * cos(-info->rotspeed) - info->planey
// 	* sin(-info->rotspeed);
// 	info->planey = info->oldplanex * sin(-info->rotspeed) + info->planey
// 	* cos(-info->rotspeed);
// }

// void	rot_left(t_var *info)
// {
// 	info->olddirx = info->dirx;
// 	info->dirx = info->dirx * cos(info->rotspeed) - info->diry
// 	* sin(info->rotspeed);
// 	info->diry = info->olddirx * sin(info->rotspeed) + info->diry
// 	* cos(info->rotspeed);
// 	info->oldplanex = info->planex;
// 	info->planex = info->planex * cos(info->rotspeed) - info->planey
// 	* sin(info->rotspeed);
// 	info->planey = info->oldplanex * sin(info->rotspeed) + info->planey
// 	* cos(info->rotspeed);
// }

void	rotate(t_var *info)
{
	if (info->mouse_in)
		mouser(info);
	if (info->x_dec > 0)
	{
		rot_right(info);
		info->x_dec = 0;
	}
	else if (info->x_dec < 0)
	{
		rot_left(info);
		info->x_dec = 0;
	}
}