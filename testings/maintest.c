#include "doom-nukem.h"
//#include <stdio.h>

void	init_artificial_map(t_map *map)
{
	t_sector	*sector2;

	map->spawn.x = 2;
	map->spawn.y = 2;
	map->spawn.z = 1;
	map->sectors = malloc(sizeof(t_sector));

	map->sectors->nbr_walls = 4;
	map->sectors->light = 0;
	map->sectors->sector_id = 1;
	map->sectors->walls = malloc(sizeof(t_wall) * map->sectors->nbr_walls);
	map->sectors->next_sector = malloc(sizeof(t_sector));

	sector2 = map->sectors->next_sector;
	sector2->nbr_walls = 4;
	sector2->light = 0;
	sector2->sector_id = 2;
	sector2->walls = malloc(sizeof(t_wall) * sector2->nbr_walls);
	sector2->next_sector = NULL;

	map->sectors->walls[0].a.x = 1;
	map->sectors->walls[0].a.y = 1;
	map->sectors->walls[0].a.z = 4;
	map->sectors->walls[0].b.x = 4;
	map->sectors->walls[0].b.y = 1;
	map->sectors->walls[0].b.z = 4;
	map->sectors->walls[0].c.x = 4;
	map->sectors->walls[0].c.y = 1;
	map->sectors->walls[0].c.z = 1;
	map->sectors->walls[0].d.x = 1;
	map->sectors->walls[0].d.y = 1;
	map->sectors->walls[0].d.z = 1;
	map->sectors->walls[0].text_id = 1;
	map->sectors->walls[0].wall_id = 0;
	map->sectors->walls[0].is_portal = 0;
	map->sectors->walls[0].is_transparent = 0;
	map->sectors->walls[0].is_textured = 1;
	map->sectors->walls[0].fill_up = 0;
	map->sectors->walls[0].fill_down = 0;
	map->sectors->walls[0].sector_id = 1;
	map->sectors->walls[0].sector_id_it_leads_to = 0;

	map->sectors->walls[1].a.x = 4;
	map->sectors->walls[1].a.y = 1;
	map->sectors->walls[1].a.z = 4;
	map->sectors->walls[1].b.x = 4;
	map->sectors->walls[1].b.y = 4;
	map->sectors->walls[1].b.z = 4;
	map->sectors->walls[1].c.x = 4;
	map->sectors->walls[1].c.y = 4;
	map->sectors->walls[1].c.z = 1;
	map->sectors->walls[1].d.x = 4;
	map->sectors->walls[1].d.y = 1;
	map->sectors->walls[1].d.z = 1;
	map->sectors->walls[1].text_id = 1;
	map->sectors->walls[1].wall_id = 1;
	map->sectors->walls[1].is_portal = 0;
	map->sectors->walls[1].is_transparent = 0;
	map->sectors->walls[1].is_textured = 1;
	map->sectors->walls[1].fill_up = 0;
	map->sectors->walls[1].fill_down = 0;
	map->sectors->walls[1].sector_id = 1;
	map->sectors->walls[1].sector_id_it_leads_to = 0;

	map->sectors->walls[2].a.x = 4;
	map->sectors->walls[2].a.y = 4;
	map->sectors->walls[2].a.z = 4;
	map->sectors->walls[2].b.x = 1;
	map->sectors->walls[2].b.y = 4;
	map->sectors->walls[2].b.z = 4;
	map->sectors->walls[2].c.x = 4;
	map->sectors->walls[2].c.y = 4;
	map->sectors->walls[2].c.z = 1;
	map->sectors->walls[2].d.x = 4;
	map->sectors->walls[2].d.y = 4;
	map->sectors->walls[2].d.z = 1;
	map->sectors->walls[2].text_id = 1;
	map->sectors->walls[2].wall_id = 2;
	map->sectors->walls[2].is_portal = 0;
	map->sectors->walls[2].is_transparent = 0;
	map->sectors->walls[2].is_textured = 1;
	map->sectors->walls[2].fill_up = 0;
	map->sectors->walls[2].fill_down = 0;
	map->sectors->walls[2].sector_id = 1;
	map->sectors->walls[2].sector_id_it_leads_to = 0;

	map->sectors->walls[3].a.x = 1;
	map->sectors->walls[3].a.y = 4;
	map->sectors->walls[3].a.z = 4;
	map->sectors->walls[3].b.x = 1;
	map->sectors->walls[3].b.y = 1;
	map->sectors->walls[3].b.z = 4;
	map->sectors->walls[3].c.x = 1;
	map->sectors->walls[3].c.y = 1;
	map->sectors->walls[3].c.z = 1;
	map->sectors->walls[3].d.x = 1;
	map->sectors->walls[3].d.y = 4;
	map->sectors->walls[3].d.z = 1;
	map->sectors->walls[3].text_id = 1;
	map->sectors->walls[3].wall_id = 3;
	map->sectors->walls[3].is_portal = 0;
	map->sectors->walls[3].is_transparent = 0;
	map->sectors->walls[3].is_textured = 1;
	map->sectors->walls[3].fill_up = 0;
	map->sectors->walls[3].fill_down = 0;
	map->sectors->walls[3].sector_id = 1;
	map->sectors->walls[3].sector_id_it_leads_to = 0;

	map->box.floor.a = map->sectors->walls[0].d;
	map->box.floor.b = map->sectors->walls[1].d;
	map->box.floor.c = map->sectors->walls[2].d;
	map->box.floor.d = map->sectors->walls[3].d;

	map->box.celling.a = map->sectors->walls[0].a;
	map->box.celling.b = map->sectors->walls[1].a;
	map->box.celling.c = map->sectors->walls[2].a;
	map->box.celling.d = map->sectors->walls[3].a;

	//2 sector

	sector2->walls[0].a.x = 5;
	sector2->walls[0].a.y = 5;
	sector2->walls[0].a.z = 6;
	sector2->walls[0].b.x = 8;
	sector2->walls[0].b.y = 5;
	sector2->walls[0].b.z = 6;
	sector2->walls[0].c.x = 8;
	sector2->walls[0].c.y = 5;
	sector2->walls[0].c.z = 2;
	sector2->walls[0].d.x = 5;
	sector2->walls[0].d.y = 5;
	sector2->walls[0].d.z = 2;
	sector2->walls[0].text_id = 1;
	sector2->walls[0].wall_id = 0;
	sector2->walls[0].is_portal = 0;
	sector2->walls[0].is_transparent = 0;
	sector2->walls[0].is_textured = 1;
	sector2->walls[0].fill_up = 0;
	sector2->walls[0].fill_down = 0;
	sector2->walls[0].sector_id = 2;
	sector2->walls[0].sector_id_it_leads_to = 0;

	sector2->walls[1].a.x = 8;
	sector2->walls[1].a.y = 5;
	sector2->walls[1].a.z = 6;
	sector2->walls[1].b.x = 8;
	sector2->walls[1].b.y = 8;
	sector2->walls[1].b.z = 6;
	sector2->walls[1].c.x = 8;
	sector2->walls[1].c.y = 8;
	sector2->walls[1].c.z = 2;
	sector2->walls[1].d.x = 8;
	sector2->walls[1].d.y = 5;
	sector2->walls[1].d.z = 2;
	sector2->walls[1].text_id = 1;
	sector2->walls[1].wall_id = 1;
	sector2->walls[1].is_portal = 0;
	sector2->walls[1].is_transparent = 0;
	sector2->walls[1].is_textured = 1;
	sector2->walls[1].fill_up = 0;
	sector2->walls[1].fill_down = 0;
	sector2->walls[1].sector_id = 2;
	sector2->walls[1].sector_id_it_leads_to = 0;

	sector2->walls[2].a.x = 8;
	sector2->walls[2].a.y = 8;
	sector2->walls[2].a.z = 6;
	sector2->walls[2].b.x = 5;
	sector2->walls[2].b.y = 8;
	sector2->walls[2].b.z = 6;
	sector2->walls[2].c.x = 8;
	sector2->walls[2].c.y = 8;
	sector2->walls[2].c.z = 2;
	sector2->walls[2].d.x = 8;
	sector2->walls[2].d.y = 8;
	sector2->walls[2].d.z = 2;
	sector2->walls[2].text_id = 1;
	sector2->walls[2].wall_id = 2;
	sector2->walls[2].is_portal = 1;
	sector2->walls[2].is_transparent = 0;
	sector2->walls[2].is_textured = 1;
	sector2->walls[2].fill_up = 0;
	sector2->walls[2].fill_down = 0;
	sector2->walls[2].sector_id = 2;
	sector2->walls[2].sector_id_it_leads_to = 0;

	sector2->walls[3].a.x = 5;
	sector2->walls[3].a.y = 8;
	sector2->walls[3].a.z = 6;
	sector2->walls[3].b.x = 5;
	sector2->walls[3].b.y = 5;
	sector2->walls[3].b.z = 6;
	sector2->walls[3].c.x = 5;
	sector2->walls[3].c.y = 5;
	sector2->walls[3].c.z = 2;
	sector2->walls[3].d.x = 5;
	sector2->walls[3].d.y = 8;
	sector2->walls[3].d.z = 2;
	sector2->walls[3].text_id = 1;
	sector2->walls[3].wall_id = 3;
	sector2->walls[3].is_portal = 0;
	sector2->walls[3].is_transparent = 0;
	sector2->walls[3].is_textured = 1;
	sector2->walls[3].fill_up = 0;
	sector2->walls[3].fill_down = 0;
	sector2->walls[3].sector_id = 2;
	sector2->walls[3].sector_id_it_leads_to = 0;
}

void	init_player(t_player *player, t_map *map)
{
	player->sector_id = map->sectors->sector_id;
	player->posx = (double)map->spawn.x;
	player->posy = (double)map->spawn.y;
	player->posz = (double)map->spawn.z;
	player->dx = -1.0;
	player->dy = 0.0;
	player->dz = 0.0;
	player->planex = 0.0;
	player->planey = 0.85;
}

void	init_render(t_var *info, t_render *render, int x0, int sector_id)
{
	render->x = x0;
	render->n = -1;
	render->sector_id = sector_id;
	render->s = info->map.sectors + sector_id - 1;
	render->ray.cam_x = 2 * render->x / (double)(WINDOW_W) - 1;
	render->ray.dx = info->player.dx + info->player.planex * render->ray.cam_x;
	render->ray.dy = info->player.dy + info->player.planey * render->ray.cam_x;
	render->wall = NULL;
	render->next_render = NULL;
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
	if (render->ray.dx != 0.0)
	{
		render->ray.eq_slope = render->ray.dy / render->ray.dx;
		render->ray.eq_cste =  render->ray.y - render->ray.eq_slope * render->ray.x;
	}
	else
	{
		render->ray.eq_slope = 1111;
		render->ray.eq_cste = render->ray.x;
	}
}

/*
** si le rayon est parallèle a l'axe des ordonnées
** ray->eq_slope = 1111
** ray->eq_cste = valeur de l'abscisse
*/

int		xy_in_frontview(double x, double y, t_ray ray)
{
	if ((ray.dx > 0 && (x <= ray.x)) || (ray.dy > 0 && (y <= ray.y)) ||
	(ray.dx < 0 && (x >= ray.x)) || (ray.dy < 0 && (y >= ray.y)))
		return (0);
	return (1);
}

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
	printf("wall -\t\teq_slope = %f\n", wall->eq_slope);
	printf("wall -\t\teq_cste = %f\n", wall->eq_cste);
	wall->height = (double)(wall->c.z - wall->a.z);
}

/*
** si le mur est parallele a l'axe des ordonnées,
** on met 11111 sur wall->eq_slope
** et la valeur de l'abscisse sur wall->eq_cste
*/

int		intersect(t_ray ray, t_wall *wall)
{
	printf("intersect -\twall_id = %i\n", wall->wall_id);
	calc_wall_spec(wall);	// a rajouter au moment du parsing ? plus rapide que pendant le rendering
	if (ray.eq_slope == wall->eq_slope)
	{
		printf("intersect -\tpas de calcul du pt d'intersection :\n\tray.eq_slope = [%f]\n\twall->eq_slope = [%f]\n",ray.eq_slope, wall->eq_slope);
		return (0);
	}
	if (wall->eq_slope == 1111)
	{
		ray.x2 = wall->eq_cste;
		ray.y2 = ray.eq_slope * ray.x2 + ray.eq_cste;
	}
	else if (ray.eq_slope == 1111)
	{
		ray.x2 = ray.x;
		ray.y2 = wall->eq_slope * ray.x2 + wall->eq_cste;
	}
	else
	{
		ray.x2 = (wall->eq_cste - ray.eq_cste) / (ray.eq_slope - wall->eq_slope);
		ray.y2 = ray.eq_slope * ray.x2 + ray.eq_cste;
	}
	printf("Pt d'intersect : (%f,%f)\n", ray.x2, ray.y2);
	if (xy_in_ab(ray.x2, ray.y2, wall->a, wall->b))
	{
		printf("intersect -\txy_in_ab = 1\n");
		return (xy_in_frontview(ray.x2, ray.y2, ray));
	}
	return (0);
}

int		xy_in_ab(double x, double y, t_point a, t_point b)
{

	//return (a.x >= x >= b.x || a.x <= x <= b.x);
	return (((a.x <= x && x <= b.x) || (b.x <= x && x <= a.x))
	  && ((a.y <= y && y <= b.y) || (b.y <= y && y <= a.y)));
}

/*
void	test_wall_calc_spec()
{

}
*/
int main()
{
	t_var		info;
	t_render	render;
	int			i = -1;

	init_artificial_map(&(info.map));
	init_player(&(info.player), &(info.map));
	init_render(&info, &render, 0, info.player.sector_id);
	update_ray(&info, &render);
	printf("main - \t\tplayer.sector_id = %i\n", info.player.sector_id);
	printf("main - \t\t render.sector_id = %i\n", render.sector_id);
	printf("main - \t\trender.s->sector_id = %i\n", render.s->sector_id);
	printf("main - \t\trender.s->nbr_walls = %i\n", render.s->nbr_walls);
	printf("main - \t\tplayer.dir : (%f,%f)\n\n\n", info.player.dx, info.player.dy);
	printf("main - \t\tray.dir : (%f,%f)\n\n\n", render.ray.dx, render.ray.dy);
	while (++i < render.s->nbr_walls)
	{
		render.wall = render.s->walls + i;
		printf("main - \t\twall_id = %i\n", render.wall->wall_id);
		printf("main - \t\tplayer.sector_id = %i\n", info.player.sector_id);
		printf("RESULTAT - \tintersect = %i\n\n",intersect(render.ray, render.wall));
	}
	free(info.map.sectors->next_sector);
	free(info.map.sectors);
	/*t_ray		ray;
	t_point		a, b;
	ray.x = 0;
	ray.y = 0;
	ray.eq_slope = 1;
	ray.eq_cste = 0;
	a.x = 0;
	a.y = 1;
	b.x = 1;
	b.y = 0;
	printf("%i\n", xy_in_ab(1.0, 1.0, a, b));
	*/
	return (0);
}
