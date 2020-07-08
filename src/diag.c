/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:04:28 by lewis             #+#    #+#             */
/*   Updated: 2020/07/08 16:20:13 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	diag1(t_var *info, t_input input)
{
	input.diag_x = info->player->dx * (0.707) - info->player->dy * (-0.707);
	input.diag_y = info->player->dx * (-0.707) + info->player->dy * (0.707);
	// if (info->map[(int)(info->posx + input.diag_x
	// * info->movespeed)][(int)(info->posy)] !=
	// '#' && hitboxx(info, input.diag_x))
		info->player->posx += input.diag_x * info->player->movespeed;
	// if (info->map[(int)(info->posx)][(int)(info->posy + input.diag_y
	// * info->movespeed)] != '#' && hitboxy(info, input.diag_y))
		info->player->posy += input.diag_y * info->player->movespeed;	
}

void	diag2(t_var *info, t_input input)
{
	input.diag_x = info->player->dx * (0.707) - info->player->dy * (0.707);
	input.diag_y = info->player->dx * (0.707) + info->player->dy * (0.707);
	// if (info->map[(int)(info->posx + input.diag_x
	// * info->movespeed)][(int)(info->posy)] !=
	// '#' && hitboxx(info, input.diag_x))
		info->player->posx += input.diag_x * info->player->movespeed;
	// if (info->map[(int)(info->posx)][(int)(info->posy + input.diag_y
	// * info->movespeed)] != '#' && hitboxy(info, input.diag_y))
		info->player->posy += input.diag_y * info->player->movespeed;
	
}

void	diag3(t_var *info, t_input input)
{
	input.diag_x = info->player->dx * (-0.707) - info->player->dy * (0.707);
	input.diag_y = info->player->dx * (0.707) + info->player->dy * (-0.707);
	// if (info->map[(int)(info->posx + input.diag_x
	// * info->movespeed)][(int)(info->posy)] !=
	// '#' && hitboxx(info, input.diag_x))
		info->player->posx += input.diag_x * info->player->movespeed;
	// if (info->map[(int)(info->posx)][(int)(info->posy + input.diag_y
	// * info->movespeed)] != '#' && hitboxy(info, input.diag_y))
	 	info->player->posy += input.diag_y * info->player->movespeed;
}

void	diag4(t_var *info, t_input input)
{
	input.diag_x = info->player->dx * (-0.707) - info->player->dy * (-0.707);
	input.diag_y = info->player->dx * (-0.707) + info->player->dy * (-0.707);
	// if (info->map[(int)(info->posx + input.diag_x
	// * info->movespeed)][(int)(info->posy)] !=
	// '#' && hitboxx(info, input.diag_x))
		info->player->posx += input.diag_x * info->player->movespeed;
	// if (info->map[(int)(info->posx)][(int)(info->posy + input.diag_y
	// * info->movespeed)] != '#' && hitboxy(info, input.diag_y))
		info->player->posy += input.diag_y * info->player->movespeed;
}