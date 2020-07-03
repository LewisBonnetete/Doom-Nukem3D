/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/03 14:33:45 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem_edit.h"

int		main(void)
{
	t_map	map;
	t_var	info;

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
