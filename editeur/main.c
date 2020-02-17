/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/02/17 16:00:08 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem_edit.h"



int				main(int ac, char **av)
{
	t_map	map;
	t_var	info;

	(void)ac;
	(void)av;
	if (!(init_win1(&info)))
		return (0);
	if (!(init_win2(&info)))
		return (0);
	editer(&info, &map);
	SDL_DestroyWindow(info.window);
	SDL_Quit();
	return (0);
}