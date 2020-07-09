/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:04:28 by lewis             #+#    #+#             */
/*   Updated: 2020/07/09 14:30:21 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	rot_right(t_var *info)
{
	info->olddirx = info->player->dx;
	info->player->dx = info->player->dx *
	cos(-info->rotspeed) - info->player->dy
	* sin(-info->rotspeed);
	info->player->dy = info->olddirx *
	sin(-info->rotspeed) + info->player->dy
	* cos(-info->rotspeed);
	info->oldplanex = info->player->planex;
	info->player->planex = info->player->planex *
	cos(-info->rotspeed) - info->player->planey
	* sin(-info->rotspeed);
	info->player->planey = info->oldplanex *
	sin(-info->rotspeed) + info->player->planey
	* cos(-info->rotspeed);
}

void	rot_left(t_var *info)
{
	info->olddirx = info->player->dx;
	info->player->dx = info->player->dx *
	cos(info->rotspeed) - info->player->dy
	* sin(info->rotspeed);
	info->player->dy = info->olddirx *
	sin(info->rotspeed) + info->player->dy
	* cos(info->rotspeed);
	info->oldplanex = info->player->planex;
	info->player->planex = info->player->planex *
	cos(info->rotspeed) - info->player->planey
	* sin(info->rotspeed);
	info->player->planey = info->oldplanex *
	sin(info->rotspeed) + info->player->planey
	* cos(info->rotspeed);
}
