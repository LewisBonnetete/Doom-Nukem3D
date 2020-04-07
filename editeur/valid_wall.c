/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewis <lewis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/04/07 17:08:29 by lewis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem_edit.h"

int		center_in_poly(t_point a, t_point b, t_sector *sector)
{
	float center_x;
	float center_y;

	center_x = (float)(a.x + b.x) / 2;
	center_y = (float)(a.y + b.y) / 2;
	if (!is_in_sectors_float(center_x, center_y, sector->map))
	{
		ft_putendl("Can't build a sector inside another");
		return (0);
	}
	return (1);
}

int		is_same_point(t_point a, t_point b)
{
	if (a.x == b.x && a.y == b.y)
		return (1);
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
	printf("new.x = %i | new.y = %i\n", new.x, new.y);
	printf("old.x = %i | old.y = %i\n", old.x, old.y);
	printf("w1.x = %i | w1.y = %i\n", w1.x, w1.y);
	printf("w2.x = %i | w2.y = %i\n", w2.x, w2.y);
	if (is_same_point(new, w1) || is_same_point(old, w1) || is_same_point(new, w2) || is_same_point(old, w2))
		return (1);
	if (new.x == old.x && w1.x != w2.x)
	{
		ft_putendl("a");
		a2 = (w2.y - w1.y) / (w2.x - w1.x);
		b2 = w1.y - (a2 * w1.x);
		y = a2 * new.x + b2;
		if (is_between(y, (float)old.y, (float)new.y) && is_between(y, (float)w1.y, (float)w2.y))
			return(0);
		return (1);
	}
	else if (w1.x == w2.x && new.x != old.x)
	{
		ft_putendl("b");
		a1 = (new.y - old.y) / (new.x - old.x);
		b1 = old.y - (a1 * old.x);
		y = a1 * w1.x + b1;
		if (is_between(y, (float)old.y, (float)new.y) && is_between(y, (float)w1.y, (float)w2.y))
			return(0);
		return (1);
	}
	else if (w1.x == w2.x && new.x == old.x)
	{
		ft_putendl("c");
		if(w1.x == new.x && w2.x == old.x && w1.y == new.y && w2.y == old.y)
			return (1);
		if(w2.x == new.x && w1.x == old.x && w2.y == new.y && w1.y == old.y)
			return (1);
		if(w1.y == new.y && w2.y == old.y && w1.x == w2.x && new.x == old.x)
			return (1);
		if(w1.y == old.y && w2.y == new.y && w1.x == w2.x && new.x == old.x)
			return (1);		
		if (is_both_inferior_y(new, old, w1, w2) || is_both_superior_y(new, old, w1, w2))
			return (1);
		return(0);
	}
	else if (w1.y == w2.y && new.y == old.y)
	{
		ft_putendl("d");
		if(w1.x == new.x && w2.x == old.x && w1.y == new.y && w2.y == old.y)
			return (1);
		if(w2.x == new.x && w1.x == old.x && w2.y == new.y && w1.y == old.y)
			return (1);
		if(w1.x == new.x && w2.x == old.x && w1.y == w2.y && new.y == old.y)
			return (1);
		if(w1.x == old.x && w2.x == new.x && w1.y == w2.y && new.y == old.y)
			return (1);	
		if (is_both_inferior_x(new, old, w1, w2) || is_both_superior_x(new, old, w1, w2))
			return (1);
		return(0);
	}
	else
	{
		ft_putendl("e");
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
			{
				ft_putendl("Wall intersection");
				return (0);
			}
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
		return (0);
	if (!center_in_poly(new, old, sector))
		return (0);
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
	{
		ft_putendl("Can't build a sector inside another");
		return (0);
	}
	return (1);
}
