/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewis <lewis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/05/08 18:32:38 by lewis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem_edit.h"

int		main()
{
	t_map	map;
	t_var	info;

	map = info.map;
	init_var(&info);
	if (!(init_win1(&info)))
		exit_edit(&info, &map);
	else if (!(init_win2(&info)))
		exit_edit(&info, &map);
	else if (!(init_win3(&info)))
		exit_edit(&info, &map);
	else if (!editer(&info, &map))
		exit_edit(&info, &map);
	return (exit_edit(&info, &map));
}