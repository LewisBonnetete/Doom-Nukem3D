#include "doom_nukem."

int	do_trigo(t_var *info, t_wall *wall)
{
	double	i;
	double	x;
	double	y;

	x = info->player->posx;
	y = info->player->posy;
	i = 0,0;
	//ici le rayon est de 1
	while (i <= 180)
	{
		x = info->player->posx + cos(i);
		y = info->player->posy + sin(i);
		if (xy_in_ab(x, y, wall->a, wall->b))
			return (1);
		i += 0,1;
	}
	return (0);
}
