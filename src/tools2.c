#include "doom-nukem.h"

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

// int		hit_object(t_var *info, t_render *render)
// {
// 	int i;

// 	i = 0;
// 	render->x = WINDOW_W / 2;
// 	update_ray(info, render);
// 	while (i < info->sector->nb_item)
// 	{
// 		if (xy_in_frontview(info->sector->item[i].x, info->sector->item[i].y, render->ray))
// 		{
// 			//calc wall.a wall.b
// 			if (xy_in_ab(info->sector->item[i].x, info->sector->item[i].y, wall.a, wall.b))
// 				//determnier eq cart de a(player);b(item) qui touche le wall entre wall.a et wall.b
// 				//point d intersection entre wall et eq cart en deduire position de l item sur les X de l ecran
// 				dist = calc_dist(info->sector->item[i].x, info->sector->item[i].y, player->posx, player->posy);
// 				dist = sqrt(dist);
// 				//changer la hauteur de l item pour les perspectives 
// 				//draw l item sur x = X de l ecran et y fonction de dist
// 		}
// 		i++;
// 	}
// }