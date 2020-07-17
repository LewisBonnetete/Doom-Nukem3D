/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:04:28 by lewis             #+#    #+#             */
/*   Updated: 2020/07/17 14:59:13 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		draw_col_port(int *tab, t_render *render, t_var *info, int id_sec)
{
	tab[render->wall->n_sec_id] = 1;
	tab[render->s->sector_id] = 1;
	id_sec = render->wall->n_sec_id;
	go_to_sector(render->sec_0, id_sec, render);
	draw_column(info, render, tab);
}

void		draw_column(t_var *info, t_render *render, int *tab)
{
	int		id_sec;

	id_sec = 0;
	if (render->nbr_items > 0)
		check_intersect(info, render, render->item_0);
	render->n = -1;
	while (++render->n < render->s->nbr_walls)
	{
		render->wall = &render->s->walls[render->n];
		if (intersect(render->ray, render->wall) == 1)
		{
			if (render->wall->is_portal == 1
			&& tab[render->wall->n_sec_id] == 0 && render->wall->n_sec_id != 0)
				draw_col_port(tab, render, info, id_sec);
			else if (render->wall->is_portal == 1
			&& tab[render->wall->n_sec_id] == 1)
				break ;
			else
			{
				update_render(info, render);
				draw_texture_wall(info, render);
				break ;
			}
		}
	}
}
