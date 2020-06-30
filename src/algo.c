#include "doom_nukem.h"

void		update_render(t_var *info, t_render *render)
{
	render->scalar = scalar(info->player->dx, info->player->dy,
	render->ray->x2 - render->ray->x, render->ray->y2 - render->ray->y);
	render->y2 = render->scalar * info->player->dy;
	render->x2 = render->scalar * info->player->dx;
	render->wall_sqdist = norm2(render->x2, render->y2);
	render->wall_dist = sqrt(render->wall_sqdist);
	render->wall_height = WALL_H * (double)render->wall->height
	/ (double)render->wall_dist;
	render->wall_y0 = WINDOW_H / 2 - render->wall_height / 2;
	render->wall_y1 = WINDOW_H / 2 + render->wall_height / 2;
	if (info->player->posz != render->wall->a.z)
	{
		render->wall_y0 += DECALLAGE * (render->wall->a.z - info->player->posz)
		/ render->wall_dist;
		render->wall_y1 += DECALLAGE * (render->wall->a.z - info->player->posz)
		/ render->wall_dist;
	}
}

void		go_to_sector(t_sector *sec_0, int id, t_render *render)
{
	if (sec_0->sector_id < id)
		go_to_sector(sec_0->next_sector, id, render);
	else
		render->s = sec_0;
}

void		calc_item_wall(t_render *render, t_var *info)
{
	if (!(render->wall_item = (t_wall *)ft_memalloc(sizeof(t_wall))))
		return ;
	render->wall_item->a.x = 0.3 * info->player->planex + render->item->x;
	render->wall_item->a.y = 0.3 * info->player->planey + render->item->y;
	render->wall_item->b.x = 0.3 * info->player->planex - render->item->x;
	render->wall_item->b.y = 0.3 * info->player->planey - render->item->y;
}

void		draw_column(t_var *info, t_render *render, int *tab)
{
	int		id_sec;
	int		i;
	int		k;
	int		j;
	t_itab	itab[5];

	render->n = -1;
	while (++render->n < render->s->nbr_walls)
	{
		render->wall = render->s->walls + render->n;
		if (intersect(render->ray, render->wall) == 1)
		{
			if (render->wall->is_portal &&
				tab[render->wall->sector_id_it_leads_to] == 0)
			{
				tab[render->wall->sector_id_it_leads_to] = 1;
				id_sec = render->wall->sector_id_it_leads_to;
				go_to_sector(render->sec_0, id_sec, render);
				draw_column(info, render, tab);
			}
			update_render(info, render);
			draw_textures(info, render);
			return ;
		}
	}
}

/*void	draw_item(t_render *render, t_var *info)
{
	float	pig;
	int		y;
	double	tx;
	double	ty;
	double	tmp;
	double	tmp2;
	t_point	p;
	Uint32	color;

	p.x = render->ray->x2;
	p.y = render->ray->y2;
	tx = calc_dist(p, render->wall_item->b);
	tmp = (double)render->tab_sdl_item[render->item->text_id]->h
	/ (double)(render->item->h / 2);
	tx *= tmp;
	tmp2 = (int)tx;
	tx -= tmp2;
	tx *= render->tab_sdl_item[render->item->text_id]->w;
	render->wall_sqdist =
	((render->ray->y2 - render->ray->y) * (render->ray->y2 - render->ray->y))
	+ ((render->ray->x2 - render->ray->x) * (render->ray->x2 - render->ray->x));
	render->wall_dist = sqrt(render->wall_sqdist);
	render->wall_height = render->tab_sdl_item[render->item->text_id]->h * 1
		/ (double)render->wall_dist;
	pig = render->wall_height / render->item->h;
	ty = 0;
	y = WINDOW_H / 2 - render->wall_height / 2 - 1;
	if (y >= (int)(render->item->h * pig))
		while (--y >= (int)(render->item->h * pig))
		{
			ty += pig;
			color = get_pixel(render->tab_sdl_item[render->item->text_id],
			(int)tx, (int)ty);
			put_pixel_to_suface(color, render->x, y,
			info->image);
		}
	else
		while (++y <= (int)(render->item->h * pig))
		{
			ty += pig;
			color = get_pixel(render->tab_sdl_item[render->item->text_id],
			(int)tx, (int)ty);
			put_pixel_to_suface(color, render->x, y, info->image);
		}
}*/

int			raycasting(t_var *info, t_render *render)
{
	t_ray	ray;
	int		*tab;

	init_cast(info, render, &ray);
	if (!(tab = (int *)ft_memalloc((sizeof(int) * render->nb_sec + 1))))
		return (0);
	info->player->sector_id = player_sec(render->sec_0, info);
	if (info->player->sector_id)
		go_to_sector(render->sec_0, info->player->sector_id, render);
	tex_floor_ciel(info, render);
	while (render->x < WINDOW_W)
	{
		go_to_sector(render->sec_0, info->player->sector_id, render);
		init_tab(tab, render->nb_sec);
		update_ray(info, render);
		draw_column(info, render, tab);
		render->x++;
	}
	hud(info, info->player, info->map);
	free(tab);
	return (1);
}
