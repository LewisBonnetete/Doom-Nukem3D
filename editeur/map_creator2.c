/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creator2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/03 14:33:52 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem_edit.h"

void		get_textures2(t_wall *wall)
{
	int		id;
	char	*line;

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
		get_textures2(wall);
}

void		get_portal_info2(t_wall *wall)
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
}

void		get_portal_info3(t_wall *wall)
{
	int		ok;
	char	*line;

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

void		get_portal_info(t_wall *wall)
{
	int		ok;
	char	*line;

	get_portal_info2(wall);
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
		get_portal_info3(wall);
	}
}
