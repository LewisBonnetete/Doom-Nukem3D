/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_interact.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/16 15:05:21 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem_edit.h"

int		get_map_size(void)
{
	char	*line;
	int		size;

	ft_putendl("Map size?");
	size = 0;
	while (size < 10 || size > 31)
	{
		get_next_line(0, &line);
		size = ft_atoi(line);
		if (size < 10 || size > 31)
			ft_putendl("Wrong size, try something else");
		free(line);
	}
	return (size);
}

void	get_map_textures(t_map *map)
{
	char	*line;
	int		size;

	ft_putendl("Texture id of the Floor?");
	size = -1;
	while (size < 1 || size > 3)
	{
		get_next_line(0, &line);
		size = ft_atoi(line);
		if (size < 1 || size > 3)
			ft_putendl("Wrong id, try something else");
		free(line);
	}
	map->fid = size;
	ft_putendl("Texture id of the Ceilling?");
	size = -1;
	while (size < 1 || size > 3)
	{
		get_next_line(0, &line);
		size = ft_atoi(line);
		if (size < 1 || size > 3)
			ft_putendl("Wrong id, try something else");
		free(line);
	}
	map->cid = size;
}
