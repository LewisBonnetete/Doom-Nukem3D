/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 15:51:41 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/03 16:56:26 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	straff_and_rot2(t_var *info, t_input input)
{
	if (input.straf_left && input.diag == 0)
	{
		input.straffer_x = -info->player->dy;
		input.straffer_y = info->player->dx;
		// if (info->map[(int)(info->posx + input.straffer_x
		// * info->movespeed)][(int)(info->posy)] !=
		// '#' && hitboxx(info, input.straffer_x))
			info->player->posx += input.straffer_x * info->player->movespeed;
		// if (info->map[(int)(info->posx)][(int)(info->posy + input.straffer_y
		// * info->movespeed)] != '#' && hitboxy(info, input.straffer_y))
			info->player->posy += input.straffer_y * info->player->movespeed;
	}
}

void	straff_and_rot(t_var *info, t_input input)
{
	if (input.right)
		rot_right(info);
	else if (input.left)
		rot_left(info);
	if (input.straf_right && input.diag == 0)
	{
		input.straffer_x = info->player->dy;
		input.straffer_y = -info->player->dx;
		// if (info->map[(int)(info->posx + input.straffer_x
		// * info->movespeed)][(int)(info->posy)] !=
		// '#' && hitboxx(info, input.straffer_x))
			info->player->posx += input.straffer_x * info->player->movespeed;
		// if (info->map[(int)(info->posx)][(int)(info->posy + input.straffer_y
		// * info->movespeed)] != '#' && hitboxy(info, input.straffer_y))
			info->player->posy += input.straffer_y * info->player->movespeed;
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
		get_move1(event, &input);
		get_move2(event, &input);
		move_diag(&input);
		sprint(info, event);
	}
	//reset_and_head(info, event);
	get_speed(info);
	diag(info, input);
	straff_and_rot(info, input);
	move(info, input);
	return (0);
}
