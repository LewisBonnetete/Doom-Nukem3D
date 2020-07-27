/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 15:51:41 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/27 17:57:28 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	straff_and_rot2(t_var *info, t_input input)
{
	if (input.straf_left && input.up == 0 && input.down == 0)
	{
		input.straffer_x = -info->player->dy;
		input.straffer_y = info->player->dx;
		if (hitbox(info, info->render, 2))
		{
			info->player->posx += input.straffer_x * info->player->movespeed;
			info->player->posy += input.straffer_y * info->player->movespeed;
		}
	}
}

void	straff_and_rot(t_var *info, t_input input)
{
	if (input.right)
		rot_right(info);
	else if (input.left)
		rot_left(info);
	if (input.straf_right && input.up == 0 && input.down == 0)
	{
		input.straffer_x = info->player->dy;
		input.straffer_y = -info->player->dx;
		if (hitbox(info, info->render, 3))
		{
			info->player->posx += input.straffer_x * info->player->movespeed;
			info->player->posy += input.straffer_y * info->player->movespeed;
		}
	}
	straff_and_rot2(info, input);
}

void	sprint(t_var *info, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_LSHIFT)
	{
		if (event.key.state == SDL_PRESSED)
			info->player->sprint = 1;
		else
			info->player->sprint = 0;
	}
	if ((event.key.keysym.sym == SDLK_SPACE && event.key.state == SDL_PRESSED)
		|| (event.type == SDL_MOUSEBUTTONDOWN))
		shoot_ennemy(info);
}

int		dealer(t_var *info)
{
	SDL_Event		event;
	static t_input	input;

	if (SDL_PollEvent(&event) == 1)
	{
		if (event.type == SDL_QUIT)
			return (0);
		if (event.key.keysym.sym == SDLK_ESCAPE && event.type == SDL_KEYDOWN)
			return (0);
		if (event.key.keysym.sym == SDLK_v && event.key.state == SDL_PRESSED)
			change_weapon(info);
		mouse_cap(info, event);
		get_move1(event, &input);
		get_move2(event, &input);
		sprint(info, event);
	}
	get_speed(info);
	straff_and_rot(info, input);
	move(info, input);
	return (1);
}
