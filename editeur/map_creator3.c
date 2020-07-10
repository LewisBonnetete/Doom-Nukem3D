/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creator3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/10 15:12:23 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem_edit.h"

void		get_nbr_walls_sector_textures2(t_sector *sector)
{
	char	*line;
	int		size;

	ft_putendl("lighting in this sector (0-100)?");
	size = -1;
	while (size < 0 || size > 100)
	{
		get_next_line(0, &line);
		size = ft_atoi(line);
		if (size < 0 || size > 100)
			ft_putendl("Wrong value, try something else");
		free(line);
	}
	sector->light = size;
}

void		get_nbr_walls_sector_textures(t_sector *sector)
{
	char	*line;
	int		size;

	ft_putendl("How many walls?");
	size = 0;
	while (size < 3 || size > 10)
	{
		get_next_line(0, &line);
		size = ft_atoi(line);
		if (size < 3 || size > 10)
			ft_putendl("Wrong number of walls, try something else");
		free(line);
	}
	sector->nbr_walls = size;
	get_nbr_walls_sector_textures2(sector);
}

void		get_height_sector(int *height)
{
	height[0] = 1;
	height[1] = 3;
}

int			create_first_wall_edit(t_sector *sector, int *height,
int i, SDL_Event event)
{
	float temp;

	sector->walls[i].sector_id = sector->sector_id;
	sector->walls[i].wall_id = i;
	temp = (float)event.button.x / (float)(WINDOW_H - 50) * sector->map->size;
	temp = round(temp);
	sector->walls[i].a.x = temp;
	sector->walls[i].d.x = temp;
	temp = (float)event.button.y / (float)(WINDOW_H - 50) * sector->map->size;
	temp = round(temp);
	sector->walls[i].a.y = temp;
	sector->walls[i].d.y = temp;
	sector->walls[i].d.z = height[0];
	sector->walls[i].a.z = height[1];
	return (1);
}

void		wall_fusion(t_sector *sector, int i)
{
	sector->walls[i - 1].b.x = sector->walls[i].a.x;
	sector->walls[i - 1].c.x = sector->walls[i].d.x;
	sector->walls[i - 1].b.y = sector->walls[i].a.y;
	sector->walls[i - 1].c.y = sector->walls[i].d.y;
	sector->walls[i - 1].c.z = sector->walls[i].d.z;
	sector->walls[i - 1].b.z = sector->walls[i].a.z;
}
