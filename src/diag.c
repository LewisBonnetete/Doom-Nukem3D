/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:04:28 by lewis             #+#    #+#             */
/*   Updated: 2020/03/05 15:20:23 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/wolf3d.h"

void	diag1(t_var *info, t_input input)
{
	input.diag_x = info->dirx * (0.707) - info->diry * (-0.707);
	input.diag_y = info->dirx * (-0.707) + info->diry * (0.707);
	if (info->map[(int)(info->posx + input.diag_x
	* info->movespeed)][(int)(info->posy)] !=
	'#' && hitboxx(info, input.diag_x))
		info->posx += input.diag_x * info->movespeed;
	if (info->map[(int)(info->posx)][(int)(info->posy + input.diag_y
	* info->movespeed)] != '#' && hitboxy(info, input.diag_y))
		info->posy += input.diag_y * info->movespeed;	
}

void	diag2(t_var *info, t_input input)
{
	input.diag_x = info->dirx * (0.707) - info->diry * (0.707);
	input.diag_y = info->dirx * (0.707) + info->diry * (0.707);
	if (info->map[(int)(info->posx + input.diag_x
	* info->movespeed)][(int)(info->posy)] !=
	'#' && hitboxx(info, input.diag_x))
		info->posx += input.diag_x * info->movespeed;
	if (info->map[(int)(info->posx)][(int)(info->posy + input.diag_y
	* info->movespeed)] != '#' && hitboxy(info, input.diag_y))
		info->posy += input.diag_y * info->movespeed;
	
}

void	diag3(t_var *info, t_input input)
{
	input.diag_x = info->dirx * (-0.707) - info->diry * (0.707);
	input.diag_y = info->dirx * (0.707) + info->diry * (-0.707);
	if (info->map[(int)(info->posx + input.diag_x
	* info->movespeed)][(int)(info->posy)] !=
	'#' && hitboxx(info, input.diag_x))
		info->posx += input.diag_x * info->movespeed;
	if (info->map[(int)(info->posx)][(int)(info->posy + input.diag_y
	* info->movespeed)] != '#' && hitboxy(info, input.diag_y))
		info->posy += input.diag_y * info->movespeed;	
}

void	diag4(t_var *info, t_input input)
{
	input.diag_x = info->dirx * (-0.707) - info->diry * (-0.707);
	input.diag_y = info->dirx * (-0.707) + info->diry * (-0.707);
	if (info->map[(int)(info->posx + input.diag_x
	* info->movespeed)][(int)(info->posy)] !=
	'#' && hitboxx(info, input.diag_x))
		info->posx += input.diag_x * info->movespeed;
	if (info->map[(int)(info->posx)][(int)(info->posy + input.diag_y
	* info->movespeed)] != '#' && hitboxy(info, input.diag_y))
		info->posy += input.diag_y * info->movespeed;
}