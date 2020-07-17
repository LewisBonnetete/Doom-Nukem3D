/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 15:51:41 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/17 13:23:22 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void			rec_wall_tool(char *the_map, t_map *map, t_wall *wall)
{
	if (the_map[map->i] == 'i')
		wall->is_textured = rec_int(the_map, map);
	if (the_map[map->i] == 'i')
		wall->fill_up = rec_int(the_map, map);
	if (the_map[map->i] == 'i')
		wall->fill_down = rec_int(the_map, map);
	if (the_map[map->i] == 'i')
		wall->sector_id = rec_int(the_map, map);
	if (the_map[map->i] == 'i')
		wall->n_sec_id = rec_int(the_map, map);
}

double			rec_double(char *the_map, t_map *map)
{
	double	a;
	double	b;
	double	d;

	++map->i;
	a = 0;
	b = 0;
	if (the_map[map->i] == 'i')
		b = rec_int(the_map, map);
	if (the_map[map->i] == 'i')
		a = rec_int(the_map, map);
	b = b / 10;
	d = a + b;
	return (d);
}

t_wall			rec_wall(char *the_map, t_map *map)
{
	t_wall	wall;

	++map->i;
	if (the_map[map->i] == 'p')
		wall.a = rec_point(the_map, map);
	if (the_map[map->i] == 'p')
		wall.b = rec_point(the_map, map);
	if (the_map[map->i] == 'p')
		wall.c = rec_point(the_map, map);
	if (the_map[map->i] == 'p')
		wall.d = rec_point(the_map, map);
	if (the_map[map->i] == 'i')
		wall.text_id = rec_int(the_map, map);
	if (the_map[map->i] == 'i')
		wall.wall_id = rec_int(the_map, map);
	if (the_map[map->i] == 'i')
		wall.is_portal = rec_int(the_map, map);
	if (the_map[map->i] == 'i')
		wall.is_transparent = rec_int(the_map, map);
	rec_wall_tool(the_map, map, &wall);
	return (wall);
}

char			rec_char(char *the_map, t_map *map)
{
	char	a;

	a = the_map[map->i];
	return (a);
}

t_item			*rec_item(char *the_map, t_map *map)
{
	t_item *res;

	++map->i;
	if (!(res = (t_item *)ft_memalloc(sizeof(t_item))))
		return (0);
	if (the_map[map->i] == 'e')
		res->name = rec_x_char(the_map, map);
	if (the_map[map->i] == 'i')
		res->x = rec_int(the_map, map);
	if (the_map[map->i] == 'i')
		res->y = rec_int(the_map, map);
	if (the_map[map->i] == 't')
		res->next_item = rec_item(the_map, map);
	else
		res->next_item = NULL;
	res->cap = 0;
	return (res);
}
