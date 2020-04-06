#include "../doom-nukem.h"	// attention

t_var   init_var(char *str)
{
	;
}

void	init_render(t_var *info, t_render *render, int x0, int sector_id)
{
	render->x = x0;
	render->n = -1;
	render->sector_id = sector_id;
	render->s = info->map.sectors[sector_id];
	render->ray.cam_x = 2 * render->x / (double)(WINDOW_W) - 1;
	render->ray.dx = info->player.dx + info->player.planex * render->ray.cam_x;
	render->ray.dy = info->player.dy + info->player.planey * render->ray.cam_x;
	render->wall = NULL;
	render->next_render = NULL;
}

int		init_next_render(t_var *info, t_render *render)
{
	t_render	*tmp;

	render->next_render = (t_render*)ft_memalloc(sizeof(t_render));
	if ((tmp = render->next_render) == NULL)
		return (0);
	init_render(info, tmp, render->x, render->wall->sector_next);
	tmp->x1 = render->next_x;
	return (1);
}

void	draw_textures(t_var *info, t_render *render)
{
	if(render->wall.is_portal)
	{
		if (render->wall.is_transparent)
			draw_portal_texture(info, render);
			/* rajouter la texture sur les pixels dans le rectangle de diagonale (x0,y0) et (x1,y1) */
		if (render->wall.is_textured)
			draw_portal_fill(info, render);
			/*		Pareil que draw_portal_texture? */
			/*  texture sur les pixels dans le rectangle de diagonale (x0,y0) et (x1,y1) */
			/*		OU		*/
			/*  texture fill_up et fill_down,
				sur les pixels au dessus et en dessous du rectangle de diagonale (x0,y0) et (x1,y1) */
	}
	else
		draw_wall_texture(info, render);
		/* horizontalement : remplit, selon la texture, les pixels entre render->x et render->next_x */
		/* verticalement : voir en fonction de la distance au mur et sa hauteur ? */
}

void	calc_wall_spec(t_wall *wall)
{
	if (b->x != a->x)
	{
		wall->eq_slope = (double)(b->y - a->y)/(b->x - a->x);
		wall->eq_cste = (double)wall->a.y - wall->eq_slope * wall->a.x;
	}
	else
	{
		wall->eq_slope = 11111;
		wall->eq_cste = 11111;
	}
	wall->height = (double)(wall->c.z - wall->a.z);
}

int		xy_in_ab(double x, double y, t_point a, t_point b)
{
	return (((x => a.x && x <= b.x) || (x <= a.x && x >= b.x))
		&& ((y => a.y && y <= b.y) || (y <= a.y && y >= b.y)));
}

int		xy_in_frontview(double x, double y, t_ray ray, t_var *info)
{
	if ((ray.dx > 0 && (x <= ray.x)) || (ray.dy > 0 && (y <= ray.y)) ||
	(ray.dx < 0 && (x >= ray.x)) || (ray.dy < 0 && (y >= ray.y)))
		return (0);
	return (1);
}

int		intersect(t_ray ray, t_wall *wall)
{
	calc_wall_spec(wall);	// a rajouter au moment du parsing ? plus rapide que pendant le rendering
	if (ray.eq_slope == wall->eq_slope)
		return (0);
	if (wall->eq_slope == 11111)
		ray.x2 = (double)wall->a.x;
	else
		ray.x2 = (wall->eq_cste - ray.eq_cste) / (ray.eq_slope - wall->eq_slope);
	ray.y2 = ray.eq_slope * ray.x2 + ray.eq_cste;
	if (xy_in_ab(ray.x2, ray.y2, wall->a, wall->b))
		return (xy_is_frontview(ray.x2, ray.y2, ray));
	return (0);
}

void	update_render(t_var *info, t_render *render)
{
	render->wall_sqdist =
		((render->ray.y2 - render->ray.y) * (render->ray.y2 - render->ray.y))
		+ (render->ray.x2 - render->ray.x) * (render->ray.x2 - render->ray.x))
		+ (render->wall->a.z - render->ray.z) * (render->wall->a.z - render->ray.z);
	render->wall_dist = sqrt(render->wall_sqdist);
	render->wall_height = WALL_H * (double)render->wall->height / (double)render->wall_dist;
	/* optimisation : possible d'éviter la fnc sqrt ?
	render->wall_height = WALL_H * render->wall->height / render->wall_sqdist;
	https://www.codeproject.com/Articles/69941/Best-Square-Root-Method-Algorithm-Function-Precisi
	*/
	// render->wall_y0 = f(render->wall->a.z, info->player.posz, render->wall_dist);
	// render->wall_y1 = f(render->wall->c.z, info->player.posz, render->wall_dist);
	if (info->player.sector_id != render->sector_id && info->player.posz != render->wall->a.z)
	{
		height_diff = render->wall->a.z - render->ray.z;
		render->wall_sqdist += height_diff * height_diff;
	}
}

void	update_ray(t_var *info, t_render *render)
{
	render->n = -1;
	render->ray.x = info->player.posx;
	render->ray.y = info->player.posy;
	render->ray.z = info->player.posz;
	render->ray.cam_x = 2 * render->x / (double)(WINDOW_W) - 1;
	render->ray.dx = info->player.dx + info->player.planex * render->ray.cam_x;
	render->ray.dy = info->player.dy + info->player.planey * render->ray.cam_x;
	render->ray.eq_slope = ray.dy / ray.dx;
	render->ray.eq_cste =  info->player.posy - render->ray.eq_slope * info->player.posx;
}

void	draw_column(t_var *info, t_render *render)
{
	while(++render->n < render->s->nbr_walls)
	{
		render->wall = render->s->walls[n];
		if(intersect(render->ray, render->wall) == 1)
		{
			if(render->wall.is_portal)
			{
				init_next_render(info, render);
				draw_column(info, render);
				ft_memdel((void**)&(render->next_render));
			}
			update_render(info, render);		// manque wall_y0 et wall_y1
			draw_textures(info, render);		// a faire quand on a wally0/y1
			return;
		}
	}
}

int     raycasting(t_var *info, t_render *render)
{
	init_render(info, &render, 0, info->player.sector_id);
	while(render->x < WINDOW_W)
	{
		update_ray(render);
		draw_column(info, render);
		render->x++;
	}
}

int     play(t_var *info, char *str)
{
	t_render	render;

	check_input(info, str);		// se coordonner pour le fichier .map/editeur
	init_var(info, str)			// rempli info
	render.x0 = 0;
	render.x1 = WINDOW_W;
	render.y0 = 0;
	render.y1 = WINDOW_H;
	//floor_ceiling_rendering(info);
	raycasting(info; &render);
}
