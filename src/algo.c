#include "../inc/doom-nukem.h"

t_var   init_var(char *str)
{
	;
}

int     play(char *file, char *str)
{
	t_raycast   render; // x0, x1, y0, y1, secteur

	check_input(str);
	t_var info;
	init_var(str) // rempli info
	render.xo = 0;
	render.x1 = WINDOW_W;
	render.y0 = 0;
	render.y1 = WINDOW_H;
	init_infos(&info, str);
	algo(&info; render);
}

	/*
	** a rajouter dans info
	**       t_player    player = pos, dir, fov, secteur
	*/

int     algo(t_var *info, t_raycast render)
{



	t_ray      ray; // cam_x, dir, hit_portal, hit_wall
	t_wall      wall;
	int         x;
	int         n;

	x = render.x0;
	init_ray(ray);
	n = -1;
	while(x < render.x1)//casting rays
	{
		wall = render.secteur.wall;
		while(++n < render.secteur.nbr_walls)
		{
			wall = render.sector.wall[n]; //a faitre
			if(intersect(ray, wall) == 1)
			{
				get_projection_of_wall(info, wall, render, ray); // fentre.x1,y1,y2
					// si new_x1 > WINDOW_W, wall affichable qu'en partie
					// si new_x1 = WINDOW_W, wall remplit la fin de l'ecran
					// idem pour y1.
				if(wall.is_portal)
				{
					render.x0 = x;
					render.secteur = wall.sector_next;
					algo(info, render);
					if (wall.is_transparent)
						draw_portal_texture(info, wall, render, ray);
					if (wall.is_textured)
						draw_portal_fill(info, wall, render, ray);
					x = render.x1;
				}
				else
				{
					draw_wall(info, render, wall, ray);
					ray.hit_wall = 1;
					x = render.x1;
				}
				break;
			}
		}
		draw_floor_or_ceilling(info, render, ray);
	}
}

int     wall_intersec(int wall, int x, t_var *info)
{

}
