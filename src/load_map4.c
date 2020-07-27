/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:04:28 by lewis             #+#    #+#             */
/*   Updated: 2020/07/27 15:44:16 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		load_exit(char *the_map)
{
	ft_strdel(&the_map);
	return (0);
}

void	dealer_iter(t_var *info, t_render *render)
{
	mouse_test(info);
	rotate(info);
	sdl_main(render, info);
	if (raycasting(info, render) == 0)
		ft_exit(info, render);
	main_tool(info, render);
}

int		init_main(int ac, char **av, t_var *info, t_player *player)
{
	if (PARSE)
		png_parse();
	if (!main_check(ac, av, info))
		return (0);
	ft_init_pour_linstant(info);
	init_player(player, info->map);
	info->player = player;
	return (1);
}

int		png_parser_iter(t_render *render, int i, int fd)
{
	char *line;

	ft_putendl("Loading textures...");
	ft_putnbr(i + 1);
	ft_putendl("/12");
	get_next_line(fd, &line);
	if (i < 4)
	{
		if (!(render->tab_sdl[i] = read_text(line)))
			return (0);
	}
	else
	{
		if (!(render->tab_sdl_item[i - 4] = read_text(line)))
			return (0);
	}
	free(line);
	system("clear");
	return (1);
}
