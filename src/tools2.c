#include "doom_nukem.h"

int	do_trigo(t_var *info, t_wall *wall)
{
	double	i;
	double	x;
	double	y;
	int	a;

	x = info->player->posx;
	y = info->player->posy;
	i = 0.0;
	//ici le rayon est de 1
	while (i <= 180.0)
	{
		x = info->player->posx + cos(i);
		y = info->player->posy + sin(i);
		if ((a = xy_in_ab(x, y, wall->a, wall->b)) != 0)
			return (1);
		i += 0.1;
	}
	return (0);
}

int		hitboxx(t_var *info, t_render *render, double dirx)
{
	double x;
	double y;

	x = -0.2;
	y = -0.2;
	while (x < 0.2)
	{
		y = -0.2;
		while (y < 0.2)
		{
			render->n = -1;
			while(++render->n < render->s->nbr_walls)
			{
				render->wall = render->s->walls + render->n;
				if (x * x + y * y  <= 0.17 * 0.17 &&  xy_in_ab(info->player->posx + x, y, render->s->walls->a, render->s->walls->b))
				{
					if(dirx >= 0 && x >= 0)
						return (0);
					if(dirx <= 0 && x <= 0)
						return (0);
				}
			}
			y += 0.01;
		}
		x += 0.01;
	}
	return(1);
}

int		hitboxy(t_var *info, t_render *render, double diry)
{
	double x;
	double y;

	x = -0.2;
	y = -0.2;
	while (x < 0.2)
	{
		y = -0.2;
		while (y < 0.2)
		{
			render->n = -1;
			while(++render->n < render->s->nbr_walls)
			{
				render->wall = render->s->walls + render->n;
				if (x * x + y * y  <= 0.17 * 0.17 &&  xy_in_ab(x ,info->player->posy + y, render->wall->a, render->wall->b))
				{
					if(diry >= 0 && x >= 0)
						return (0);
					if(diry <= 0 && x <= 0)
						return (0);
				}
			}
			y += 0.01;
		}
		x += 0.01;
	}
	return(1);
}

void		update_ray_box(t_var *info, t_render *render, int dir, t_point p)
{
	render->x = WINDOW_W / 2;
	render->ray->x = p.x;
	render->ray->y = p.y;
	render->ray->cam_x = 2 * render->x / (double)(WINDOW_W) - 1;
	if (dir == 0)
	{
		render->ray->dx = info->player->dx;
		render->ray->dy = info->player->dy;
	}
	if (dir == 1)
	{
		render->ray->dx = -info->player->dx;
		render->ray->dy = -info->player->dy;
	}
	if (dir == 2)
	{
		render->ray->dx = -info->player->dy;
		render->ray->dy = info->player->dx;
	}
	if (dir == 3)
	{
		render->ray->dx = info->player->dy;
		render->ray->dy = -info->player->dx;
	}
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

int			hitbox(t_var *info, t_render *render, int dir)
{
	t_point r;
	t_point p;
	double tmp;

	p.x = info->player->posx;
	p.y = info->player->posy;
	update_ray_box(info, render, dir, p);	
	render->n = -1;
	while (++render->n < render->s->nbr_walls)
	{
		render->wall = &render->s->walls[render->n];
		if (intersect(render->ray, render->wall) == 1)
		{
			r.x = render->ray->x2;
			r.y = render->ray->y2;
			if(render->wall->is_portal == 1)
				return (1);
			if (calc_dist(r, p) <= 0.5)
				return (0);
		}
	}
	return (1);
}
