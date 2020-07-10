/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/10 15:36:25 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem_edit.h"

int		verif(void)
{
	char *line;

	ft_putendl("Are you sure you want to validate this map?(y/n)");
	while (1)
	{
		get_next_line(0, &line);
		if ((line[0] == 'y' || line[0] == 'n') && line[1] == 0)
		{
			if (line[0] == 'y')
			{
				free(line);
				return (1);
			}
			if (line[0] == 'n')
			{
				free(line);
				return (0);
			}
		}
		else
			ft_putendl("What? try something else");
		free(line);
	}
	return (0);
}

int		save(t_map *map)
{
	char	*line;
	int		size;

	ft_putendl("What is your map's name?");
	size = 0;
	while (size < 3 || size > 15)
	{
		get_next_line(0, &line);
		size = ft_strlen(line);
		if (size < 3 || size > 15 || ft_strrchr(line, ';'))
		{
			ft_putendl("Invalid name");
			free(line);
		}
	}
	if (!creat_fichier(map, line))
	{
		ft_putendl("save_map failed");
		return (0);
	}
	return (1);
}

int		validate(t_map *map)
{
	if (!verif())
		return (0);
	if (map->sectors == NULL)
	{
		ft_putendl("Map is empty");
		return (0);
	}
	if (set_end(map) && set_spawn(map) && portals(map) && save(map))
		return (1);
	return (0);
}
