/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewis <lewis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/04/06 15:08:38 by lewis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem_edit.h"



int				main(int ac, char **av)
{
	t_map	map;
	t_var	info;

	(void)ac;
	(void)av;
	(void)info;
	(void)map;

	init_var(&info);
	if (!(init_win1(&info)))
		return (0);
	if (!(init_win2(&info)))
		return (0);
	editer(&info, &map);
	SDL_DestroyWindow(info.window);
	SDL_Quit();
	return (0);
}