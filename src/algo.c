#include "doom-nukem.h"


void	update_ray(t_var *info, t_render *render)
{
	render->ray->cam_x = 2 * render->x / (double)(WINDOW_W) - 1;
	render->ray->dx = info->player->dx + info->player->planex * render->ray->cam_x;
	render->ray->dy = info->player->dy + info->player->planey * render->ray->cam_x;
	if (render->ray->dx != 0.0)
	{
		render->ray->eq_slope = render->ray->dy / render->ray->dx;
		render->ray->eq_cste =  render->ray->y - render->ray->eq_slope * render->ray->x;
	}
	else
	{
		render->ray->eq_slope = 1111;
		render->ray->eq_cste = render->ray->x;
	}
}

void	update_render(t_var *info, t_render *render)
{
	//printf("wallID in render = %i\n",render->wall->wall_id);
	render->wall_sqdist =
		((render->ray->y2 - render->ray->y) * (render->ray->y2 - render->ray->y))
		+ ((render->ray->x2 - render->ray->x) * (render->ray->x2 - render->ray->x))
		+ (render->wall->c.z - render->ray->z) * (render->wall->c.z - render->ray->z); //fish eye ici car distance euclidienne 
	render->wall_dist = sqrt(render->wall_sqdist);
	render->wall_height = WALL_H * (double)render->wall->height / (double)render->wall_dist;
	/* optimisation : possible d'éviter la fnc sqrt ?
	render->wall_height = WALL_H * render->wall->height / render->wall_sqdist;
	https://www.codeproject.com/Articles/69941/Best-Square-Root-Method-Algorithm-Function-Precisi
	*/
	render->wall_y0 = WINDOW_H / 2 - render->wall_height / 2;
	render->wall_y1 = WINDOW_H / 2 + render->wall_height / 2;
	//if (info->player.sector_id != render->sector_id && info->player.posz != render->wall->a.z)
	if (info->player->posz != render->wall->a.z)
	{
		render->wall_y0 += DECALLAGE * (render->wall->a.z - info->player->posz) /  render->wall_dist;
		render->wall_y1 += DECALLAGE * (render->wall->a.z - info->player->posz) /  render->wall_dist;
	}
	// printf("WALL_H = %d\n", WALL_H);
	// printf("wall_sqdist = %f\n",render->wall_sqdist);
	// printf("wall_dist = %f\n",render->wall_dist);
	// printf("wall_height = %f\n",render->wall_height);
	//printf("wall_y0 = %d\n",render->wall_y0);
	//printf("wall_y1 = %d\n",render->wall_y1);
}

void	go_to_sector(t_sector *sec_0, int id, t_render *render)
{
	if (sec_0->sector_id < id)
		go_to_sector(sec_0->next_sector, id, render);
	else
		render->s = sec_0;
}

// void	go_to_sector(t_render *render,t_var *info, int id)
// {
// 	t_sector *tmp;
// 	printf("1\n");
// 	if (render->sec_0->sector_id != id)
// 	{
// 		printf("2\n");
// 		tmp = render->sec_0->next_sector;
// 		printf("3\n");
// 		while (tmp->sector_id < id)
// 			tmp = tmp->next_sector;
// 		printf("4\n");
// 	}
// 	else
// 		tmp = render->sec_0;
// 	printf("6\n");
// 	render->s = tmp;
// 	printf("7\n");
// 	(void)info;
// }

void	draw_column(t_var *info, t_render *render, int *tab)
{
	int		id_sec;
	int		tmp;

	render->n = -1;
	tmp = -1;
	while(++render->n < render->s->nbr_walls)
	{
		render->wall = render->s->walls + render->n;
		if(intersect(render->ray, render->wall) == 1)
		{
			//printf("tab %i\n",tab[render->wall->sector_id_it_leads_to]);
			if(render->wall->is_portal && tab[render->wall->sector_id_it_leads_to] == 0)
			{
				//printf("sec lead = %i\n", render->wall->sector_id_it_leads_to);
				tab[render->wall->sector_id_it_leads_to] = 1;
				id_sec = render->wall->sector_id_it_leads_to;
				tmp = render->sector_id;
				go_to_sector(render->sec_0, id_sec, render);
			//	printf("sec out = %i\n", render->s->sector_id);
				draw_column(info, render, tab);
			}
			if (tmp != -1)
				go_to_sector(render->sec_0, tmp, render);
			update_render(info, render);
			draw_textures(info, render);
			return;
		}
	}
}

void		init_nb_sec(t_sector *sector, t_render *render)
{
	if (sector->next_sector)
	{
		render->nb_sec++;
		init_nb_sec(sector->next_sector, render);
	}
}
int     raycasting(t_var *info, t_render *render)
{
	t_ray ray;
	int *tab;
	render->sector_id = info->player->sector_id;
	render->n = -1;
	render->x = 0;
	render->ray = &ray;
	render->ray->x = info->player->posx;
	render->ray->y = info->player->posy;
	render->ray->z = info->player->posz;
	render->ray->cam_x = 2 * render->x / (double)(WINDOW_W) - 1;
	render->ray->dx = info->player->dx + info->player->planex * render->ray->cam_x;
	render->ray->dy = info->player->dy + info->player->planey * render->ray->cam_x;
	if (!(tab = (int *)ft_memalloc((sizeof(int) * render->nb_sec + 1))))
		return (0);
	info->player->sector_id = player_sec(render->sec_0, info);
	if (info->player->sector_id)
		go_to_sector(render->sec_0, info->player->sector_id, render);
	//else {exit func}
	//printf("sector id = %i\n",info->player->sector_id);
	while(render->x < WINDOW_W)
	{
		go_to_sector(render->sec_0, info->player->sector_id, render);
		init_tab(tab, render->nb_sec);
		update_ray(info, render);
		draw_column(info, render, tab);
		render->x++;
	}
	free(tab);
	return (1);
}
