#include "doom_nukem.h"

void		update_ray(t_var *info, t_render *render)
{
	render->ray->cam_x = 2 * render->x / (double)(WINDOW_W) - 1;
	render->ray->dx = info->player->dx +
	info->player->planex * render->ray->cam_x;
	render->ray->dy = info->player->dy +
	info->player->planey * render->ray->cam_x;
	if (render->ray->dx != 0.0)
	{
		render->ray->eq_slope = render->ray->dy
		/ render->ray->dx;
		render->ray->eq_cste = render->ray->y
		- render->ray->eq_slope * render->ray->x;
	}
	else
	{
		render->ray->eq_slope = 1111;
		render->ray->eq_cste = render->ray->x;
	}
}

void		init_cast(t_var *info, t_render *render, t_ray *ray)
{
	render->sector_id = info->player->sector_id;
	render->n = -1;
	render->x = 0;
	render->ray = ray;
	render->ray->x = info->player->posx;
	render->ray->y = info->player->posy;
	render->ray->z = info->player->posz;
	render->ray->cam_x = 2 * render->x / (double)(WINDOW_W) - 1;
	render->ray->dx = info->player->dx
	+ info->player->planex * render->ray->cam_x;
	render->ray->dy = info->player->dy
	+ info->player->planey * render->ray->cam_x;
}

void		init_nb_sec(t_sector *sector, t_render *render)
{
	if (sector->next_sector)
	{
		render->nb_sec++;
		init_nb_sec(sector->next_sector, render);
	}
}

int			rgb_calc(int r, int g, int b)
{
	return (256 * 256 * (int)(r) + 256 * (int)(g) + (int)(b));
}
