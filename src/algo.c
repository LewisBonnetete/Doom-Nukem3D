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
		+ (render->wall->c.z - render->ray->z) * (render->wall->c.z - render->ray->z);
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
	// printf("wall_y0 = %d\n",render->wall_y0);
	// printf("wall_y1 = %d\n",render->wall_y1);
}

void	draw_column(t_var *info, t_render *render)
{
	render->n = -1;
	while(++render->n < render->s->nbr_walls)
	{
		render->wall = render->s->walls + render->n;
		if(intersect(render->ray, render->wall) == 1)
		{
			if(render->wall->is_portal)
			{
				init_next_render(info, render);
				draw_column(info, render);
				ft_memdel((void**)&(render->next_render));
			}
			update_render(info, render);
			draw_textures(info, render);
			return;
		}
	}
}

int     raycasting(t_var *info, t_render *render)
{
	t_ray ray;
	
	render->ray = &ray;
	init_render(info, render, 0, info->player->sector_id);
	while(render->x < WINDOW_W)
	{
		update_ray(info, render);
		draw_column(info, render);
		render->x++;
	}
	return (1);
}
