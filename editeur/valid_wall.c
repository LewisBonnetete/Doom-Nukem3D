/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewis <lewis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/04/01 16:23:08 by lewis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem_edit.h"

int		is_between(float x, float a, float b)
{
	if (a > b)
	{
		if (x > b && x < a)
			return (1);
	}
	else
	{
		if (x > a && x < b)
			return (1);
	}
	return (0);
}

int		check_wall_intersections(t_point new, t_point old, t_wall wall)
{
	t_point w1;
	t_point w2;
	float	a1;
	float	a2;
	float	b1;
	float	b2;
	float	x;
	float	y;

	x = 0.0;
	y = 0.0;
	w1 = wall.a;
	w2 = wall.b;
	if (new.x == old.x && w1.x != w2.x)
	{
		a2 = (w2.y - w1.y) / (w2.x - w1.x);
		b2 = w1.y - (a2 * w1.x);
		y = a2 * new.x + b2;
		if (is_between(y, (float)old.y, (float)new.y) && is_between(y, (float)w1.y, (float)w2.y))
			return(0);
		return (1);
	}
	else if (w1.x == w2.x && new.x != old.x)
	{
		a1 = (new.y - old.y) / (new.x - old.x);
		b1 = old.y - (a1 * old.x);
		y = a1 * w1.x + b1;
		if (is_between(y, (float)old.y, (float)new.y) && is_between(y, (float)w1.y, (float)w2.y))
			return(0);
		return (1);
	}
	else if (w1.x == w2.x && new.x == old.x)
	{
		if(w1.x == new.x && w2.x == old.x && w1.y == new.y && w2.y == old.y)
			return (1);
		if(w2.x == new.x && w1.x == old.x && w2.y == new.y && w1.y == old.y)
			return (1);
		if (w1.x != new.x)
			return (1);
		return (0);
	}
	else if (w1.y == w2.y && new.y == old.y)
	{
		if(w1.x == new.x && w2.x == old.x && w1.y == new.y && w2.y == old.y)
			return (1);
		if(w2.x == new.x && w1.x == old.x && w2.y == new.y && w1.y == old.y)
			return (1);
		if (w1.y != new.y)
			return (1);
		return (0);
	}
	else
	{
		a1 = (float)(new.y - old.y) / (float)(new.x - old.x);
		a2 = (float)(w2.y - w1.y) / (float)(w2.x - w1.x);
		b1 = (float)old.y - (a1 * (float)old.x);
		b2 = (float)w1.y - (a2 * (float)w1.x);
		if (a1 == a2)
			return (1);
		x = (b2-b1)/(a1-a2);
		if (is_between(x, (float)old.x, (float)new.x) && is_between(x, (float)w1.x, (float)w2.x))
			return(0);
	}
	return (1);
}

int		verify_crossing(t_point new, t_point old, t_sector *sector)
{
	t_sector *current_sector;
	int i;
	
	current_sector = sector->map->sectors;
	while (current_sector != sector && current_sector->next_sector != NULL)
	{
		i = 0;
		while (i < current_sector->nbr_walls)
		{
			if(!check_wall_intersections(new, old, current_sector->walls[i]))
				return (0);
			i++;
		}
		current_sector = current_sector->next_sector;
	}
	return(1);
}

int		is_valid_wall(SDL_Event *event, t_sector *sector, int i)
{
	
	float		temp;
	t_point		new;
	t_point		old;

	temp = (float)event->button.x / (float)WINDOW_H * sector->map->size;
	new.x = round(temp);
	temp = (float)event->button.y / (float)WINDOW_H * sector->map->size;
	new.y = round(temp);
	old.x = sector->walls[i - 1].a.x;
	old.y = sector->walls[i - 1].a.y;
	if (event->button.x <= 0 || event->button.x >= WINDOW_H)
		return (0);
	if (event->button.y <= 0 || event->button.y >= WINDOW_H)
		return (0);
	if (!verify_crossing(new, old, sector))
		return(0);
	return (1);
}

int		is_valid_last_wall(SDL_Event *event, t_sector *sector, int i)
{
	
	float		temp;
	t_point		new;
	t_point		old;

	temp = (float)event->button.x / (float)WINDOW_H * sector->map->size;
	new.x = round(temp);
	temp = (float)event->button.y / (float)WINDOW_H * sector->map->size;
	new.y = round(temp);
	old.x = sector->walls[i - 1].a.x;
	old.y = sector->walls[i - 1].a.y;
	if (event->button.x <= 0 || event->button.x >= WINDOW_H)
		return (0);
	if (event->button.y <= 0 || event->button.y >= WINDOW_H)
		return (0);
	if (!verify_crossing(new, old, sector))
		return(0);
	old.x = sector->walls[0].a.x;
	old.y = sector->walls[0].a.y;
	if (!verify_crossing(new, old, sector))
		return(0);
	return (1);
}

int		is_in_core_rectangle(t_point first,t_sector *sector)
{
	int minx;
	int maxx;
	int miny;
	int maxy;
	int i;

	i = 0;
	minx = WINDOW_H + 1;
	miny = WINDOW_H + 1;
	maxx = -1;
	maxy = -1;
	while(i < sector->nbr_walls)
	{
		if(sector->walls[i].a.x > maxx)
			maxx = sector->walls[i].a.x;
		if(sector->walls[i].a.y > maxy)
			maxy = sector->walls[i].a.y;
		if(sector->walls[i].a.x < minx)
			minx = sector->walls[i].a.x;
		if(sector->walls[i].a.y < miny)
			miny = sector->walls[i].a.y;
		if(sector->walls[i].b.x > maxx)
			maxx = sector->walls[i].b.x;
		if(sector->walls[i].b.y > maxy)
			maxy = sector->walls[i].b.y;
		if(sector->walls[i].b.x < minx)
			minx = sector->walls[i].b.x;
		if(sector->walls[i].b.y < miny)
			miny = sector->walls[i].b.y;
		i++;
	}
	if (first.x < minx || first.x > maxx || first.y < miny || first.y > maxy)
		return (0);
	return (1);
	
}

int 	pnpoly(int nbr_walls, t_wall *walls, t_point first)
{
	int i;
	int j;
	int c;

	i = 0;
	j = nbr_walls - 1;
	c = 0;
	while (i < nbr_walls)
	{
		if (((walls[i].a.y > first.y) != (walls[j].a.y > first.y)) && (first.x < (walls[j].a.x - walls[i].a.x) * (first.y - walls[i].a.y) / (walls[j].a.y - walls[i].a.y) + walls[i].a.x))
			c = !c;
		j = i++;
	}
	return (c);
}
int		is_in_sector(t_point first,t_sector *sector)
{
	if(!is_in_core_rectangle(first, sector))
		return (1);
	if (pnpoly(sector->nbr_walls, sector->walls, first))
		return(0);
	return (1);
}

int		is_in_sectors(t_point first,t_map *map)
{
	t_sector *current_sector;

	current_sector = map->sectors;
	while (current_sector->next_sector)
	{
		if(!is_in_sector(first, current_sector))
			return(0);
		current_sector = current_sector->next_sector;
	}
	return (1);
}

int		is_valid_first_wall(SDL_Event *event,t_map *map)
{
	t_point first;
	float	temp;
	if (event->button.x <= 0 || event->button.x >= WINDOW_H)
		return (0);
	if (event->button.y <= 0 || event->button.y >= WINDOW_H)
		return (0);
	temp = (float)event->button.x / (float)WINDOW_H * map->size;
	first.x = round(temp);
	temp = (float)event->button.y / (float)WINDOW_H * map->size;
	first.y = round(temp);
	if (!is_in_sectors(first, map))
		return (0);
	return (1);
}
