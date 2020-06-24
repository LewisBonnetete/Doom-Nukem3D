/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/06/24 15:52:33 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem_edit.h"

void		get_textures(t_wall *wall)
{
	int		id;
	char	*line;

	ft_putendl("Texture id of the wall?");
	id = -1;
	while (id < 0 || id > 10)
	{
		get_next_line(0, &line);
		id = ft_atoi(line);
		if (id < 0 || id > 10)
			ft_putendl("Wrong id, try something else");
		free(line);
	}
	wall->text_id = id;
	if (wall->is_portal)
	{
		ft_putendl("Texture id of fill_up?");
		id = -1;
		while (id < 0 || id > 10)
		{
			get_next_line(0, &line);
			id = ft_atoi(line);
			if (id < 0 || id > 10)
				ft_putendl("Wrong id, try something else");
			free(line);
		}
		wall->fill_up = id;
		ft_putendl("Texture id of fill_down?");
		id = -1;
		while (id < 0 || id > 10)
		{
			get_next_line(0, &line);
			id = ft_atoi(line);
			if (id < 0 || id > 10)
				ft_putendl("Wrong id, try something else");
			free(line);
		}
		wall->fill_down = id;
	}
}

void		get_portal_info(t_wall *wall)
{
	int		ok;
	char	*line;

	ok = 0;
	ft_putendl("Is your wall a portal?(y/n)");
	while (ok == 0)
	{
		get_next_line(0, &line);
		if ((line[0] == 'y' || line[0] == 'n') && line[1] == 0)
		{
			if (line[0] == 'y')
				wall->is_portal = 1;
			if (line[0] == 'n')
				wall->is_portal = 0;
			ok = 1;
		}
		else
			ft_putendl("What? try something else");
		free(line);
	}
	if (wall->is_portal)
	{
		ok = 0;
		ft_putendl("Is it transparent?(y/n)");
		while (ok == 0)
		{
			get_next_line(0, &line);
			if ((line[0] == 'y' || line[0] == 'n') && line[1] == 0)
			{
				if (line[0] == 'y')
					wall->is_transparent = 1;
				if (line[0] == 'n')
					wall->is_transparent = 0;
				ok = 1;
			}
			else
				ft_putendl("What? try something else");
			free(line);
		}
		ok = 0;
		ft_putendl("Is it textured?(y/n)");
		while (ok == 0)
		{
			get_next_line(0, &line);
			if ((line[0] == 'y' || line[0] == 'n') && line[1] == 0)
			{
				if (line[0] == 'y')
					wall->is_textured = 1;
				if (line[0] == 'n')
					wall->is_textured = 0;
				ok = 1;
			}
			else
				ft_putendl("What? try something else");
			free(line);
		}
	}
}

void		get_nbr_walls_sector_textures(t_sector *sector)
{
	char	*line;
	int		size;

	ft_putendl("How many walls?");
	size = 0;
	while (size < 3 || size > 25)
	{
		get_next_line(0, &line);
		size = ft_atoi(line);
		if (size < 3 || size > 25)
			ft_putendl("Wrong number of walls, try something else");
		free(line);
	}
	sector->nbr_walls = size;
	ft_putendl("Texture id of the Floor?");
	size = -1;
	while (size < 0 || size > 10)
	{
		get_next_line(0, &line);
		size = ft_atoi(line);
		if (size < 0 || size > 10)
			ft_putendl("Wrong id, try something else");
		free(line);
	}
	sector->floor.text_id = size;
	ft_putendl("Texture id of the Ceilling?");
	size = -1;
	while (size < 0 || size > 10)
	{
		get_next_line(0, &line);
		size = ft_atoi(line);
		if (size < 0 || size > 10)
			ft_putendl("Wrong id, try something else");
		free(line);
	}
	sector->celling.text_id = size;
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

void		get_height_sector(t_map *map, int *height)
{
	char	*line;

	ft_putendl("How low is you sector?");
	while (height[0] < 1 || height[0] > map->size - 2)
	{
		get_next_line(0, &line);
		height[0] = ft_atoi(line);
		if (height[0] < 1 || height[0] > map->size - 2)
			ft_putendl("Wrong height, try something else");
		free(line);
	}
	ft_putendl("How high is you sector?");
	while (height[1] <= height[0] || height[1] > map->size - 1)
	{
		get_next_line(0, &line);
		height[1] = ft_atoi(line);
		if (height[1] <= height[0] || height[1] > map->size - 1)
			ft_putendl("Wrong height, try something else");
		free(line);
	}
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

int			create_wall_edit(t_sector *sector, int *height,
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
	wall_fusion(sector, i);
	get_portal_info(&sector->walls[i - 1]);
	get_textures(&sector->walls[i - 1]);
	return (1);
}

void		close_sector(t_sector *sector, int i)
{
	sector->walls[i].b.x = sector->walls[0].a.x;
	sector->walls[i].c.x = sector->walls[0].d.x;
	sector->walls[i].b.y = sector->walls[0].a.y;
	sector->walls[i].c.y = sector->walls[0].d.y;
	sector->walls[i].c.z = sector->walls[0].d.z;
	sector->walls[i].b.z = sector->walls[0].a.z;
	get_portal_info(&sector->walls[i]);
	get_textures(&sector->walls[i]);
}

int			get_walls_sector(t_map *map, t_sector *sector, int *height)
{
	SDL_Event	event;
	int			i;

	i = 0;
	ft_putstr("Place you walls, you'll have to put two vertex ");
	ft_putendl("for your first wall");
	ft_putendl("Press 'd' to delete your sector :)");
	while (i < sector->nbr_walls)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (i == 0)
			{
				if (is_valid_first_wall(&event, map))
				{
					create_first_wall_edit(sector, height, i, event);
					i++;
				}
				else
					ft_putendl("Nope, try something else");
			}
			else if (i < sector->nbr_walls - 1 && i > 0)
			{
				if (is_valid_wall(&event, sector, i))
				{
					create_wall_edit(sector, height, i, event);
					draw_state(sector);
					i++;
				}
				else
					ft_putendl("Nope, try something else");
			}
			else if (i == sector->nbr_walls - 1)
			{
				if (is_valid_last_wall(&event, sector, i))
				{
					create_wall_edit(sector, height, i, event);
					draw_state(sector);
					i++;
				}
				else
					ft_putendl("Nope, try something else");
			}
		}
		else if (event.key.keysym.sym == SDLK_d
		&& event.key.state == SDL_PRESSED)
		{
			ft_putendl("Sector deleted");
			del_sector(sector->info, map);
			draw_state(sector);
			return (1);
		}
		if (i == sector->nbr_walls && !check_convexity(sector))
		{
			ft_putendl("Sorry but your sector is not convex :(");
			ft_putendl("Sector deleted");
			del_sector(sector->info, map);
			draw_state(sector);
			return (1);
		}
		if (i == sector->nbr_walls && !check_self_intersection(sector))
		{
			ft_putendl("Sorry but your sector crosses itself :(");
			ft_putendl("Sector deleted");
			del_sector(sector->info, map);
			draw_state(sector);
			return (1);
		}
		if (i == sector->nbr_walls && !check_surrounding(sector))
		{
			ft_putendl("Sorry but your sector surrounds another :(");
			ft_putendl("Sector deleted");
			del_sector(sector->info, map);
			draw_state(sector);
			return (1);
		}
		if (event.type == SDL_QUIT || (event.key.keysym.sym == SDLK_ESCAPE
		&& event.type == SDL_KEYDOWN))
		{
			exit_edit(sector->info, map);
			return (1);
		}
	}
	close_sector(sector, sector->nbr_walls - 1);
	return (1);
}

int			init_first_sector(t_var *info, t_sector *sector, t_map *map)
{
	int height[2];

	init_sector(sector);
	sector->sector_id = 1;
	get_height_sector(map, height);
	get_nbr_walls_sector_textures(sector);
	sector->map = map;
	sector->info = info;
	sector->next_sector = NULL;
	if (!(sector->walls = (t_wall*)malloc(sizeof(t_wall) * sector->nbr_walls)))
		return (0);
	init_walls(sector->walls, sector->nbr_walls);
	if (!get_walls_sector(map, sector, height))
		return (0);
	return (1);
}

int			init_new_sector(t_var *info, t_sector *sector, t_map *map)
{
	int height[2];

	init_sector(sector->next_sector);
	sector->next_sector->sector_id = sector->sector_id + 1;
	sector = sector->next_sector;
	get_height_sector(map, height);
	get_nbr_walls_sector_textures(sector);
	sector->map = map;
	sector->info = info;
	sector->next_sector = NULL;
	sector->sector_id = sector->sector_id;
	if (!(sector->walls = (t_wall*)malloc(sizeof(t_wall) * sector->nbr_walls)))
		return (0);
	init_walls(sector->walls, sector->nbr_walls);
	if (!get_walls_sector(map, sector, height))
		return (0);
	return (1);
}

int			create_sector(t_var *info, t_map *map)
{
	t_sector *sector;

	sector = map->sectors;
	if (sector)
	{
		sector = get_to_last_sector(map->sectors);
		if (!(sector->next_sector = (t_sector*)malloc(sizeof(t_sector)))
		|| (!init_new_sector(info, sector, map)))
			return (exit_edit(info, map));
	}
	else
	{
		if (!(map->sectors = (t_sector*)malloc(sizeof(t_sector)))
		|| (!init_first_sector(info, map->sectors, map)))
			return (exit_edit(info, map));
	}
	return (1);
}
