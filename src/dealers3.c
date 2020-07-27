/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealers3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:04:28 by lewis             #+#    #+#             */
/*   Updated: 2020/07/27 18:00:04 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	get_move_y(SDL_Event event, t_input *input)
{
	if (event.key.keysym.sym == SDLK_UP)
	{
		if (event.key.state == SDL_PRESSED)
			input->headup = 1;
		else
			input->headup = 0;
	}
	if (event.key.keysym.sym == SDLK_DOWN)
	{
		if (event.key.state == SDL_PRESSED)
			input->headdown = 1;
		else
			input->headdown = 0;
	}
}

void	get_move1(SDL_Event event, t_input *input)
{
	if (event.key.keysym.sym == SDLK_w
	|| event.key.keysym.sym == SDLK_z)
	{
		if (event.key.state == SDL_PRESSED)
			input->up = 1;
		else
			input->up = 0;
	}
	if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_q)
	{
		if (event.key.state == SDL_PRESSED)
			input->straf_left = 1;
		else
			input->straf_left = 0;
	}
	if (event.key.keysym.sym == SDLK_s)
	{
		if (event.key.state == SDL_PRESSED)
			input->down = 1;
		else
			input->down = 0;
	}
	get_move_y(event, input);
}

void	get_move2(SDL_Event event, t_input *input)
{
	if (event.key.keysym.sym == SDLK_a)
	{
		if (event.key.state == SDL_PRESSED)
			input->straf_right = 1;
		else
			input->straf_right = 0;
	}
	if (event.key.keysym.sym == SDLK_RIGHT)
	{
		if (event.key.state == SDL_PRESSED)
			input->left = 1;
		else
			input->left = 0;
	}
	if (event.key.keysym.sym == SDLK_LEFT)
	{
		if (event.key.state == SDL_PRESSED)
			input->right = 1;
		else
			input->right = 0;
	}
}

int		move(t_var *info, t_input input)
{
	if (input.headup && info->y_dec <= 50)
		info->y_dec += 5;
	if (input.headdown && info->y_dec >= -50)
		info->y_dec -= 5;
	if (input.up)
	{
		if (hitbox(info, info->render, 0))
		{
			info->player->posx += info->player->dx * info->player->movespeed;
			info->player->posy += info->player->dy * info->player->movespeed;
		}
	}
	if (input.down)
	{
		if (hitbox(info, info->render, 1))
		{
			info->player->posx -= info->player->dx * info->player->movespeed;
			info->player->posy -= info->player->dy * info->player->movespeed;
		}
	}
	return (1);
}
