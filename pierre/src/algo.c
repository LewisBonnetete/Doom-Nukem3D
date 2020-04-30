#include "doom-nukem.h"

/*t_var   init_var(char *str)
{
	void str;
}
*/
void	put_pixel_to_suface(Uint32 color, int x, int y, SDL_Surface *image)
{
	Uint32 *pixels;

	pixels = image->pixels;
	if (x >= 0 && y >= 0 && x < image->w && y < image->h)
		pixels[y * image->w + x] = color;
}

void	draw_tex(t_var *info, t_render *render)
{
	//printf("draw\n");
	int i;

	i = 0;
	while (i < render->wall_y0 - render->wall_y1)
	{
		put_pixel_to_suface(255, render->x,i + render->wall_y0 , info->image);
		i++;
	}

}

/*
** si le rayon est parallèle a l'axe des ordonnées
** ray->eq_slope = 1111
** ray->eq_cste = valeur de l'abscisse
*/

void	calc_wall_spec(t_wall *wall)
{
	if (wall->b.x != wall->a.x)
	{
		if (wall->a.y == wall->b.y)
			wall->eq_slope = 0;
		else
			wall->eq_slope =
				(double)(wall->b.y - wall->a.y)/(wall->b.x - wall->a.x);
		wall->eq_cste = (double)wall->a.y - wall->eq_slope * wall->a.x;
	}
	else
	{
		wall->eq_slope = 1111;
		wall->eq_cste = (double)wall->a.x;
	}
	//printf("wall -\t\teq_slope = %f\n", wall->eq_slope);
	//printf("wall -\t\teq_cste = %f\n", wall->eq_cste);
	//wall->height = (double)(wall->a.z - wall->c.z);
	wall->height = (double)(wall->c.z - wall->a.z);
}

/*
** si le mur est parallele a l'axe des ordonnées,
** on met 11111 sur wall->eq_slope
** et la valeur de l'abscisse sur wall->eq_cste
*/

int		intersect(t_ray *ray, t_wall *wall)
{
	//printf("intersect -\twall_id = %i\n", wall->wall_id);
	calc_wall_spec(wall);	// a rajouter au moment du parsing ? plus rapide que pendant le rendering
	if (ray->eq_slope == wall->eq_slope)
	{
		//printf("intersect -\tpas de calcul du pt d'intersection :\n\tray.eq_slope = [%f]\n\twall->eq_slope = [%f]\n",ray.eq_slope, wall->eq_slope);
		return (0);
	}
	if (wall->eq_slope == 1111)
	{
		ray->x2 = wall->eq_cste;
		ray->y2 = ray->eq_slope * ray->x2 + ray->eq_cste;
	}
	else if (ray->eq_slope == 1111)
	{
		ray->x2 = ray->x;
		ray->y2 = wall->eq_slope * ray->x2 + wall->eq_cste;
	}
	else
	{
		ray->x2 = (wall->eq_cste - ray->eq_cste) / (ray->eq_slope - wall->eq_slope);
		ray->y2 = ray->eq_slope * ray->x2 + ray->eq_cste;
	}
	//printf("Pt d'intersect : (%f,%f)\n", ray.x2, ray.y2);
	if (xy_in_ab(ray->y2, ray->y2, wall->a, wall->b))
	{
		//printf("intersect -\txy_in_ab = 1\n");
		return (xy_in_frontview(ray->x2, ray->y2, *ray));
	}
	return (0);
}

void	init_render(t_var *info, t_render *render, int x0, int sector_id)
{
	render->x = x0;
	render->n = -1;
	render->sector_id = sector_id;
	render->s = info->map.sectors + sector_id - 1;
	render->ray->cam_x = 2 * render->x / (double)(WINDOW_W) - 1;
	render->ray->dx = info->player->dx + info->player->planex * render->ray->cam_x;
	render->ray->dy = info->player->dy + info->player->planey * render->ray->cam_x;
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
	if(render->wall->is_portal)
	{
		//if (render->wall->is_transparent)
		//	draw_tex(info, render);
			//draw_portal_texture(info, render);
			// rajouter la texture sur les pixels dans le rectangle de diagonale (x0,y0) et (x1,y1)
		//if (render->wall->is_textured)
			//draw_tex(info, render);
			//draw_portal_fill(info, render);
			//		Pareil que draw_portal_texture?
			//  texture sur les pixels dans le rectangle de diagonale (x0,y0) et (x1,y1)
			//		OU
			//  texture fill_up et fill_down,
			//	sur les pixels au dessus et en dessous du rectangle de diagonale (x0,y0) et (x1,y1)
	}
	else
		draw_bottop(info, render);
		draw_tex(info, render);
		//horizontalement : remplit, selon la texture, les pixels entre render->x et render->next_x
		//verticalement : voir en fonction de la distance au mur et sa hauteur ?
}

void	update_ray(t_var *info, t_render *render)
{
	render->n = -1;
	render->ray->x = info->player->posx;
	render->ray->y = info->player->posy;
	render->ray->z = info->player->posz;
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
	//printf("ray slope = %f\nray dx =%f\nray dy%f\n",render->ray->eq_slope,render->ray->dx,render->ray->dy);
	//printf("ray cste =%f\n",render->ray->eq_cste);
}

/*
** si le rayon est parallèle a l'axe des ordonnées
** ray->eq_slope = 1111
** ray->eq_cste = valeur de l'abscisse
*/

int		xy_in_frontview(double x, double y, t_ray ray)
{
	//printf("frontview in\n");
	if ((ray.dx > 0 && (x <= ray.x)) || (ray.dy > 0 && (y <= ray.y)) ||
	(ray.dx < 0 && (x >= ray.x)) || (ray.dy < 0 && (y >= ray.y)))
		return (0);
	//printf("frontview = true\n");
	return (1);
}

/*
** si le mur est parallele a l'axe des ordonnées,
** on met 11111 sur wall->eq_slope
** et la valeur de l'abscisse sur wall->eq_cste
*/

int		xy_in_ab(double x, double y, t_point a, t_point b)
{
	return (((a.x <= x && x <= b.x) || (b.x <= x && x <= a.x))
		&& ((a.y <= y && y <= b.y) || (b.y <= y && y <= a.y)));
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
	printf("wall_sqdist = %f\n",render->wall_sqdist);
	printf("wall_dist = %f\n",render->wall_dist);
	printf("wall_height = %f\n",render->wall_height);
	printf("wall_y0 = %f\n",render->wall_y0);
	printf("wall_y1 = %f\n",render->wall_y1);
	//printf("y0=%i\ny1=%i\n",render->wall_y0,render->wall_y1);
}

void	draw_column(t_var *info, t_render *render)
{
	while(++render->n < render->s->nbr_walls)
	{
	//	printf("bonjour\n");
		render->wall = render->s->walls + render->n;
		//printf("wallID in draw = %i\nn = %i\nnbr_walls = %i\n",render->wall->wall_id, render->n,render->s->nbr_walls);
		if(intersect(render->ray, render->wall) == 1)
		{
		//	printf("bonjour1\n");
			if(render->wall->is_portal)
			{
			//	printf("bonjour2\n");
				init_next_render(info, render);
				draw_column(info, render);
				ft_memdel((void**)&(render->next_render));
			}
		//	printf("update\n");
			update_render(info, render);		// manque wall_y0 et wall_y1
		//	printf("draw\n");
			draw_textures(info, render);		// a faire quand on a wally0/y1
			return;
		}
	//	printf("bonjour out\n");
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
