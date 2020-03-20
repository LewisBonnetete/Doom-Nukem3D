#include "../doom-nukem.h"	// attention

t_var   init_var(char *str)
{
	;
}

void	init_render(t_var *info, t_render *render, int x0, int sector_id)
{
	render->x = x0;
	render->x0 = x0;
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
	// reste a calculer tmp->y0 et tmp->y1 (qui represente le sol et plafond du nouveau secteur dans l'ecran ? pas vraiment avec les angles et la perspective)
	// ou
	// les definir dans la structure wall (mieux je pense)
	return (1);
}

void	draw_wall_textures(t_var *info, t_render *render)
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
		draw_wall(info, render);
		/* horizontalement : remplit, selon la texture, les pixels entre render->x et render->next_x */
		/* verticalement : voir en fonction de la distance au mur et sa hauteur ? */
}

int		intersect(t_ray ray, t_wall *wall)
{
	/*
	renvoie 1 si le rayon croise le mur
	ATTENTION dans le calcul
	le secteur etant convexe, chaque rayon croisera les droites de 2murs
	cf lien gamedev de Tom
	-> regarder la direction (le sens > equationd de droite) du joueur/rayon
	*/
}

void	update_render(t_var *info, t_render *render)
{
	/*
	wall_distance : calcul pour la colonne render->x de la distance du mur sur cette colonne au joueur/plane/fov whatever
	wall_y1 coordonnée du pixel en haut du mur
	wall_y0 coordonnée du pixel en bas du mur
	next_x coordonnée de la fin du mur (hypothétique car peut etre > a WINDOW_W)
		utile pour afficher le mur en entier d'un bloc sans verifier pour chaque colonne l'intersection
		nécessaire dans le cas d'un portail pour définir la fin du next_render->x1 (=min(render->x1, next_x))
	*/
}

int     walls_and_portals_rendering(t_var *info, t_render *render)
{
	while(render->x < render->x1)
	{
		while(++render->n < render->s->nbr_walls && render->x < render->x1)
		{
			render->wall = render->s->walls[n];
			if(intersect(render->ray, render->wall) == 1)
			{
				update_render(info, render);	// wall_dist, wall_y0, wall_y1, (next_x ?)
				if(render->wall.is_portal)
				{
					init_next_render(info, render);
					walls_and_portals_rendering(info, render->next_render);	// récurssion
					//render->x = render->next_render.x1;
					ft_memdel((void**)&(render->next_render));	// free le malloc dans init_next_render
				}
				draw_wall_textures(info, render);	// affiche les textures du mur ou du portail
				render->x = ft_min(render->next_x, render->x1); // incrément le x
				// render->ray.hit_wall = 1;
				// break;
			}
		}
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
	init_render(info, &render, 0, info->player.sector_id);
	//floor_ceiling_rendering(info);
	walls_and_portals_rendering(info; &render);
}
