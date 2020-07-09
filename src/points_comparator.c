/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points_comparator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/09 15:37:21 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		is_both_inferior_x(t_point a, t_point b, t_point c, t_point d)
{
	if (a.x <= c.x && b.x <= d.x && a.x <= d.x && b.x <= c.x)
	{
		return (1);
	}
	return (0);
}

int		is_both_superior_x(t_point a, t_point b, t_point c, t_point d)
{
	if (a.x >= c.x && b.x >= d.x && a.x >= d.x && b.x >= d.x)
	{
		return (1);
	}
	return (0);
}

int		is_both_inferior_y(t_point a, t_point b, t_point c, t_point d)
{
	if (a.y <= c.y && b.y <= d.y && a.y <= d.y && b.y <= c.y)
	{
		return (1);
	}
	return (0);
}

int		is_both_superior_y(t_point a, t_point b, t_point c, t_point d)
{
	if (a.y >= c.y && b.y >= d.y && a.y >= d.y && b.y >= d.y)
	{
		return (1);
	}
	return (0);
}

int		player_sec(t_sector *sector, t_var *info)
{
	if (pnpoly_float(sector->nbr_walls, sector->walls,
		info->player->posx, info->player->posy))
	{
		return (sector->sector_id);
	}
	else if (sector->next_sector)
		return (player_sec(sector->next_sector, info));
	return (-1);
}
