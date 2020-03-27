/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_sector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewis <lewis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/03/27 14:59:14 by lewis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem_edit.h"

void	del_sector(t_var *info, t_map *map)
{
	t_sector	*sector;
	t_sector	*previous_sector;
	int			sector_id;

	if(map->sectors)
	{
		sector_id = nbr_of_sectors(map);
		sector = get_to_last_sector(map->sectors);
		if (sector_id > 1)
		{
			previous_sector = get_a_sector_by_id(map, sector_id - 1);
			free(sector->walls);
			free(sector);
			previous_sector->next_sector = NULL;
			ft_putendl("Sector ");
			ft_putnbr(sector_id);
			ft_putendl(" Destroyed");
		}
		else if (sector_id == 1)
		{
			free(map->sectors->walls);
			free(map->sectors);
			map->sectors = NULL;
			ft_putendl("Sector 1 Destroyed");
		}
		draw_grid(info, map);
	}
}