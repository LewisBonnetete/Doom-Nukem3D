/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewis <lewis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/03/18 16:24:06 by lewis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem_edit.h"

void	get_textures(t_wall *wall)
{
	int id;
	char *line;
	
	ft_putendl("Texture id of the wall?");
	id = -1;
	while(id < 0 || id > 10)
	{
		get_next_line(0, &line);
		id = ft_atoi(line);
		if (id < 0 || id > 10)
			ft_putendl("Wrong id, try something else");
	}
	wall->text_id = id;
	if (wall->is_portal)
	{
		ft_putendl("Texture id of fill_up?");
		id = -1;
		while(id < 0 || id > 10)
		{
			get_next_line(0, &line);
			id = ft_atoi(line);
			if (id < 0 || id > 10)
				ft_putendl("Wrong id, try something else");
		}
		wall->fill_up = id;
		ft_putendl("Texture id of fill_down?");
		id = -1;
		while(id < 0 || id > 10)
		{
			get_next_line(0, &line);
			id = ft_atoi(line);
			if (id < 0 || id > 10)
				ft_putendl("Wrong id, try something else");
		}
		wall->fill_down = id;
	}
}

void	get_portal_info(t_wall *wall, t_map *map)
{
	int ok;
	char *line;

	ok = 0;
	ft_putendl("Is your wall a portal?(y/n)");
	while(ok == 0)
	{
		get_next_line(0, &line);
		if ((line[0] == 'y' || line[0] == 'n') && line[1] == 0)
		{
			wall->is_portal = 1;
			ok = 1;
		}
		else
			ft_putendl("What? try something else");
	}
	if (wall->is_portal)
	{
		ok = 0;
		ft_putendl("Is it transparent?(y/n)");
		while(ok == 0)
		{
			get_next_line(0, &line);
			if ((line[0] == 'y' || line[0] == 'n') && line[1] == 0)
			{
				wall->is_transparent = 1;
				ok = 1;
			}
			else
				ft_putendl("What? try something else");
		}
		ok = 0;
		ft_putendl("Is it textured?(y/n)");
		while(ok == 0)
		{
			get_next_line(0, &line);
			if ((line[0] == 'y' || line[0] == 'n') && line[1] == 0)
			{
				wall->is_textured = 1;
				ok = 1;
			}
			else
				ft_putendl("What? try something else");
		}
		ft_putendl("What's the sector it leads to?(y/n)");
		ok = -1;
		while(ok < 0 || ok > nbr_of_sectors(map))
		{
			get_next_line(0, &line);
			ok = ft_atoi(line);
			if (ok < 0 || ok > nbr_of_sectors(map))
				ft_putendl("Wrong id, try something else");
		}
		wall->sector_next = get_a_sector_by_id(map, ok);
	}	
}

int		get_nbr_walls()
{
	char	*line;
	int		size;
	
	ft_putendl("How many walls?");
	size = 0;
	while(size < 3 || size > 25)
	{
		get_next_line(0, &line);
		size = ft_atoi(line);
		if (size < 3 || size > 25)
			ft_putendl("Wrong number of walls, try something else");
	}
	return (size);
}
void		get_height_sector(t_map *map, int *height)
{
	char	*line;
	ft_putendl("How low is you sector?");
	while(height[0] < 1 || height[0] > map->size - 2)
	{
		get_next_line(0, &line);
		height[0] = ft_atoi(line);
		if (height[0] < 1 || height[0] > map->size - 2)
			ft_putendl("Wrong height, try something else");
	}
	ft_putendl("How high is you sector?");
	while(height[1] < height[0] || height[1] > map->size - 1)
	{
		get_next_line(0, &line);
		height[1] = ft_atoi(line);
		if (height[1] < height[0] || height[1] > map->size - 1)
			ft_putendl("Wrong height, try something else");
	}
}

int		is_valid_wall(SDL_Event *event, t_sector *sector)
{
	(void)event;
	(void)sector;
	return (1);
}

int			create_wall_edit(t_sector *sector,int *height, int i, SDL_Event	event)
{
	sector->walls[i].sector_id = sector->sector_id;
	sector->walls[i].wall_id = i;
	sector->walls[i].a.x = event.button.x;
	sector->walls[i].d.x = event.button.x;
	sector->walls[i].a.y = event.button.y;
	sector->walls[i].d.y = event.button.y;
	sector->walls[i].d.z = height[0];
	sector->walls[i].a.z = height[1];
	get_portal_info(&sector->walls[i], sector->map);
	get_textures(&sector->walls[i]);
	return (1);
}

int		get_walls_sector(t_var *info, t_map *map, t_sector *sector,int *height)
{
	SDL_Event	event;
	int			i;
	
	i  = 0;
	(void)info;
	(void)map;
	ft_putendl("place you walls");
	while(i < sector->nbr_walls - 1)
	{
		SDL_WaitEvent(&event);
		if(event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (is_valid_wall(&event, sector))
			{
				if (!create_wall_edit(sector, height, i, event))
					return(0);
				i++;
			}
			else
				ft_putendl("Nope, try something else");
		}
	}
	return (1);
}

int		init_new_sector(t_var *info, t_sector *sector, t_map *map)
{
	int height[2];

	get_height_sector(map, height);
	sector->nbr_walls = get_nbr_walls();
	if(!(sector->walls = (t_wall*)malloc(sizeof(t_wall) * sector->nbr_walls)))
		return (0);
	if (!get_walls_sector(info, map, sector, height))
		return (0);
	sector->next_sector = NULL;
	return (1);
}

int		create_sector(t_var *info, t_map *map)
{
	(void)info;
	(void)map;
	t_sector *sector;

	sector = map->sectors;
	sector->map = map;
	get_to_last_sector(sector);
	if (!(sector = (t_sector*)malloc(sizeof(t_sector))) || (init_new_sector(info, sector, map)))
		return (exit_edit(info, map));
	return (1);
}