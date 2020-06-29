/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editer_tools3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/06/29 15:43:27 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem_edit.h"

int		x_coo(SDL_Event *event, t_map *map)
{
	float	temp;

	temp = (float)event->button.x / (float)(WINDOW_H - 50) * map->size;
	return (round(temp));
}

int		y_coo(SDL_Event *event, t_map *map)
{
	float	temp;

	temp = (float)event->button.x / (float)(WINDOW_H - 50) * map->size;
	return (round(temp));
}
