/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealers3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:04:28 by lewis             #+#    #+#             */
/*   Updated: 2020/07/08 16:16:04 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	get_move1(SDL_Event event, t_input *input)
{
	if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP
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
	if (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN)
	{
		if (event.key.state == SDL_PRESSED)
			input->down = 1;
		else
			input->down = 0;
	}
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

int		move(t_var *info, t_input input, t_render *render)
{
	if (input.up && input.diag == 0)
	{
		if(hitbox(info, info->render, 0))
		{
			info->player->posx += info->player->dx * info->player->movespeed;
			info->player->posy += info->player->dy * info->player->movespeed;
		}
	}
	if (input.down && input.diag == 0)
	{
		if(hitbox(info, info->render, 1))
		{
			info->player->posx -= info->player->dx * info->player->movespeed;
			info->player->posy -= info->player->dy * info->player->movespeed;
		}
	}
	return (1);
}

// void	reset_and_head(t_var *info, SDL_Event event)
// {
// 	if (event.key.keysym.sym == SDLK_DELETE && event.key.state == SDL_PRESSED)
// 	{
// 		info->posx = info->ori_x;
// 		info->posy = info->ori_y;
// 		info->time_reset = info->time;
// 		ft_init_pour_linstant(info);
// 	}
// 	if (event.key.keysym.sym == SDLK_PAGEUP && event.key.state == SDL_PRESSED)
// 		info->y_dec -= 8;
// 	if (event.key.keysym.sym == SDLK_PAGEDOWN && event.key.state == SDL_PRESSED)
// 		info->y_dec += 8;
// }
