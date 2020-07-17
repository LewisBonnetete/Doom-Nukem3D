/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/16 17:09:02 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem_edit.h"

char	*little_strjoin(char *src, char c)
{
	int		i;
	char	*dest;

	i = ft_strlen(src);
	if (!((dest) = (char *)malloc(sizeof(char) * i + 2)))
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

int		do_map2(t_map *map, int fd)
{
	if (do_point(map->spawn, fd) == 0)
		return (0);
	if (map->items)
		if (do_item(map->items, fd) == 0)
			return (0);
	if (map->props)
		if (do_prop(map->props, fd) == 0)
			return (0);
	if (map->enemys)
		if (do_enemy(map->enemys, fd) == 0)
			return (0);
	return (1);
}

t_item	*do_map_help(t_map *map)
{
	t_item *items;

	if (!(items = (t_item *)ft_memalloc(sizeof(t_item))))
		return (0);
	if (!(items->name = ft_strdup("portal")))
		return (0);
	items->x = map->end.x;
	items->y = map->end.y;
	items->next_item = NULL;
	return (items);
}

int		do_map(t_map *map, int fd)
{
	char	c;
	t_item	*items;

	items = NULL;
	if ((items = do_map_help(map)) == 0)
		return (0);
	c = 'm';
	if (write(fd, &c, 1) == -1)
		return (0);
	if (do_box(map->box, fd) == 0)
		return (0);
	if (map->sectors)
		if (do_sectors(map->sectors, fd) == 0)
			return (0);
	if (do_int(map->size, fd) == 0 || do_int(map->cid, fd) == 0
		|| do_int(map->fid, fd) == 0)
		return (0);
	if (do_map2(map, fd) == 0)
		return (0);
	if (do_item(items, fd) == 0)
		return (0);
	free(items->name);
	free(items);
	return (1);
}

int		do_enemy(t_enemy *enemy, int fd)
{
	char	c;

	c = 't';
	if (write(fd, &c, 1) == -1)
		return (0);
	if (enemy->name)
		if (do_x_char(enemy->name, fd) == 0)
			return (0);
	if (do_int(enemy->x, fd) == 0)
		return (0);
	if (do_int(enemy->y, fd) == 0)
		return (0);
	if (enemy->next_enemy)
		do_enemy(enemy->next_enemy, fd);
	return (1);
}
