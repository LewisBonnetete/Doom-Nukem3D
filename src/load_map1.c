/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 15:51:41 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/23 16:02:34 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

char			*little_strjoin(char *src, char c)
{
	int		i;
	char	*dest;

	i = ft_strlen(src);
	if (!((dest) = (char *)malloc(sizeof(char) * i + 1)))
		return (0);
	dest[i + 1] = 0;
	i = -1;
	while (src[++i])
		dest[i] = src[i];
	dest[i] = c;
	if (src)
		ft_strdel(&src);
	return (dest);
}

void			rec_sectors_int(char *the_map, t_sector *sectors, t_map *map)
{
	if (the_map[map->i] == 'i')
		sectors->light = rec_int(the_map, map);
	if (the_map[map->i] == 'i')
		sectors->sector_id = rec_int(the_map, map);
}

int				info_map(char *str, t_map *map)
{
	char	*the_map;
	int		i;

	i = 0;
	map->name = str;
	while (str[i])
		++i;
	map->i = 0;
	if (!(the_map = recup_map(str)))
		return (0);
	if (check_map(the_map) == 0)
		return (load_exit(the_map));
	if (the_map[map->i] == 'm')
	{
		if (rec_map(the_map, map) == 0)
			return (load_exit(the_map));
	}
	else
		return (0);
	ft_strdel(&the_map);
	return (1);
}

int				rec_map(char *the_map, t_map *map)
{
	++map->i;
	if (the_map[map->i] == 'b')
		map->box = rec_box(the_map, map);
	if (the_map[map->i] == 's')
		map->sectors = rec_sectors(the_map, map);
	if (the_map[map->i] == 'i')
		map->size = rec_int(the_map, map);
	if (the_map[map->i] == 'i')
		map->cid = rec_int(the_map, map);
	else
		map->cid = 0;
	if (the_map[map->i] == 'i')
		map->fid = rec_int(the_map, map);
	else
		map->fid = 1;
	if (the_map[map->i] == 'p')
		map->spawn = rec_point(the_map, map);
	if (the_map[map->i] == 't')
		map->items = rec_item(the_map, map);
	else
		map->items = NULL;
	return (1);
}

t_box			rec_box(char *the_map, t_map *map)
{
	int		x;
	t_box	box;

	++map->i;
	x = -1;
	while (++x < 5)
		if (the_map[map->i] == 'w')
			box.walls[x] = rec_wall(the_map, map);
	if (the_map[map->i] == 'i')
		box.nbr_walls = rec_int(the_map, map);
	if (the_map[map->i] == 'i')
		box.size = rec_int(the_map, map);
	if (the_map[map->i] == 'w')
		box.floor = rec_wall(the_map, map);
	if (the_map[map->i] == 'w')
		box.celling = rec_wall(the_map, map);
	return (box);
}
