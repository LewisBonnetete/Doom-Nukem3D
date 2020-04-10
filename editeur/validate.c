/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewis <lewis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/04/10 16:11:36 by lewis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem_edit.h"

int		verif()
{
	char *line;

	ft_putendl("Are you sure you want to validate this map?(y/n)");
	while(1)
	{
		get_next_line(0, &line);
		if ((line[0] == 'y' || line[0] == 'n') && line[1] == 0)
		{
			if (line[0] == 'y')
				return (1);
			if (line[0] == 'n')
				return (0);
		}
		else
			ft_putendl("What? try something else");
	}
	return (0);
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
	if (map->sectors->next_sector == NULL)
	{
		ft_putendl ("Map is too small, create at least two sectors");
		return (0);
	}
	set_spawn(map);
	return (1);
}