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