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
			break;
		}
	}
	if (render->nbr_items <= 0)
		return;
	i = -1;
	if (!render->itab)
	{
		if (!(render->itab = (t_itab *)ft_memalloc(sizeof(t_itab) * 5)))
			return;
		while (++i < 5)
		{
			render->itab[i].name = 0;
			render->itab[i].dist = 0;
		}
	}
	render->n = -1;
	while (++render->n < render->nbr_items)
	{
		render->item = render->s->item + render->n;
		calc_item_wall(render, info);
		if (intersect(render->ray, render->wall_item) == 1
		&& render->item->cap == 0)
		{
			render->itab[render->n].dist = render->wall_dist;
			render->itab[render->n].name = render->item->name;
			render->itab[render->n].item_x = render->item->x;
			render->itab[render->n].item_y = render->item->y;
			render->itab[render->n].start = render->x;
			render->itab[render->n].h = render->item->h;
			render->itab[render->n].w = render->item->w;
			render->itab[render->n].text_id = render->item->text_id;
			render->item->cap = 1;
			render->x++;
			while (intersect(render->ray, render->wall_item) == 1 && render->x <= WINDOW_W)
			{
				++render->x;
				update_ray(info, render);
			}
			render->itab[render->n].end = render->x;
			render->x = render->itab[render->n].start;
		}
	}
}

void	draw_item_2(t_render *render, t_var *info, int k)
{
	t_point	p;
	t_point	w;
	float	ty;
	int		y;
	int		i;
	Uint32	color;

	p.x = info->player->posx;
	p.y = info->player->posy;
	w.x = render->itab[k].item_x;
	w.y = render->itab[k].item_y;
	render->distance = calc_dist(p, w);
	if (render->distance < 0.5)
	{
		//rajouter ici la fonvtion qui met l'arme dans la main !
		render->item->cap = 2;
	}
	render->height_item = render->itab[k].h / render->distance;
	render->widht_item = render->itab[k].w / render->distance;
	render->step_height = render->tab_sdl_item[render->itab[k].text_id]->h / render->height_item;
	render->step_width = render->tab_sdl_item[render->itab[k].text_id]->w / render->widht_item;
	render->tx = 0;
	render->itab[k].end /= render->distance;
//	if (render->itab[k].start == 0 && render->widht_item > render->itab[k].end)
//	{
//		render->tx = (render->widht_item - render->itab[k].end) * render->step_width;
//		render->widht_item -= (render->widht_item - render->itab[k].end);
//	}
	if (render->itab[k].end > render->itab[k].h)
		render->itab[k].start -= (render->widht_item - render->itab[k].h) / 2;
	else
		render->itab[k].start += (render->widht_item - render->itab[k].end) / 2;
	render->x = render->itab[k].start - 1;
	render->p_0 = render->x + 1;
	while (++render->x <= render->widht_item + render->p_0)
	{
		ty = 0;
		y = WINDOW_H / 2 + WINDOW_H / 2 / render->distance;
		i = -1;
		while (++i <= render->height_item)
		{
			color = get_pixel(render->tab_sdl_item[render->item->text_id], render->tab_sdl_item[render->itab[k].text_id]->h - (int)ty, (int)render->tx);
			ty += render->step_height;
			put_pixel(darken_wall(info, color, render, y), render->x, y, info->image);
			--y;
		}
		render->tx += render->step_width;
	}
}

void	draw_item(t_render *render, t_var *info)
{
	int		j;
	int		k;
	int		i;

	if (!render->itab)
		return;
	j = -1;
	while (render->itab[++j].name)
	{
		k = 0;
		i = -1;
		while (render->itab[++i].name)
		{
			if (render->itab[k].dist < render->itab[i].dist
				&& render->itab[k].name[0] != '-' && render->itab[k].name[1] != '1')
				k = i;
		}
		render->item = render->s->item + k;
		render->itab[k].name = "-1";
		render->itab[k].dist = -1;
		draw_item_2(render, info, k);
	}
	i = -1;
	while (render->itab[++i].name)
		render->itab[i].name = 0;
}

static	void	ft_put_weapon(t_var *info, t_render *render)
{
	double		x;
	double		y;
	Uint32		color;

	x = 0;
	while (x < render->tab_sdl[3]->w)
	{
		y = 0;
		while (y < render->tab_sdl[3]->h)
		{
			color = get_pixel(render->tab_sdl[3], y, x);
			if (color != 0)
				put_pixel(color, (int)x + WINDOW_W / 2 - 45,
				WINDOW_H + (int)y - 125 + info->d_gun, info->image);
			y++;
		}
		x++;
	}
}

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
	printf("seg1\n");
	draw_item(render, info);
	printf("seg2\n");
	ft_put_weapon(info, render);
	hud(info, info->player, info->map);
	free(tab);
	return (1);
}
