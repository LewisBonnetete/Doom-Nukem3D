#include "doom-nukem.h"

void			ft_init_pour_linstant(t_var *info)
{
	info->frametime = 0.03;
	info->rotspeed = info->frametime * 0.5;
//	info->y_dec = 0;
//	info->texture_cap = 0;
//	info->mouse_in = 0;
//	info->weapon_cap = 0;
}

void	init_player(t_player *player, t_map *map)
{
	player->sector_id = map->sectors->sector_id;
	player->posx = (double)map->spawn.x;
	player->posy = (double)map->spawn.y;
	player->posz = (double)map->spawn.z;
	player->dx = 1.0;
	player->dy = 0.0;
	player->dz = 0.0;
	player->planex = 0.0;
	player->planey = 0.4;
}

void	init_render(t_var *info, t_render *render, int x0, int sector_id)
{
	render->x = x0;
	render->n = -1;
	render->sector_id = sector_id;
	render->s = info->map.sectors + sector_id - 1;
	render->ray->x = info->player->posx;
	render->ray->y = info->player->posy;
	render->ray->z = info->player->posz;
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