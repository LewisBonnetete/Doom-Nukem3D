/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 15:51:41 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/09 12:44:36 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int				rec_x_char_tool(char *the_map, t_map *map)
{
	if ((((the_map[map->i] >= 'a' && the_map[map->i] <= 'z')
		|| (the_map[map->i] >= 'A' && the_map[map->i] <= 'Z'))
		|| (the_map[map->i] >= '0' && the_map[map->i] <= '9'))
		&& (the_map[map->i] != 'i' || (the_map[map->i + 1] < '0'
		|| the_map[map->i + 1] > '9')))
		return (1);
	return (0);
}

char			*rec_x_char(char *the_map, t_map *map)
{
	char	*src;
	char	a;

	src = 0;
	a = 0;
	++map->i;
	while (rec_x_char_tool(the_map, map))
	{
		if (src != 0)
		{
			a = rec_char(the_map, map);
			src = little_strjoin(src, a);
		}
		else
		{
			if (!(src = (char *)ft_memalloc(sizeof(char) + 2)))
				return (0);
			src[0] = rec_char(the_map, map);
			src[1] = 0;
		}
		++map->i;
	}
	if (src != 0)
		src = little_strjoin(src, 0);
	return (src);
}

int				rec_int(char *the_map, t_map *map)
{
	char	*str;
	int		j;
	int		tmp;
	size_t	len;
	int		dest;

	++map->i;
	tmp = map->i;
	while (the_map[map->i] >= '0' && the_map[map->i] <= '9')
		++map->i;
	len = map->i - tmp;
	str = ft_strnew(len);
	map->i = tmp;
	j = -1;
	while (the_map[map->i] >= '0' && the_map[map->i] <= '9')
		str[++j] = the_map[map->i++];
	str[j + 1] = 0;
	dest = ft_atoi(str);
	return (dest);
}

int				recup_map_tool(char *line, int fd)
{
	ft_strdel(&line);
	close(fd);
	return (0);
}

char			*recup_map(char *src)
{
	char	*line;
	int		fd;
	int		error;
	char	*map;

	map = 0;
	if ((fd = open(src, O_RDONLY)) == -1)
		return (0);
	while ((error = get_next_line(fd, &line)) > 0)
	{
		if (map == 0)
			map = ft_strdup(line);
		else if (!line)
		{
			map = ft_strcat(map, line);
			if (!map)
				recup_map_tool(line, fd);
		}
		ft_strdel(&line);
	}
	close(fd);
	return (map);
}
