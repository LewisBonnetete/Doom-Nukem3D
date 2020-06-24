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
	player->sector_id = 1;
	player->posx = (double)map->spawn.x;
	player->posy = (double)map->spawn.y;
	player->posz = (double)map->spawn.z;
	player->dx = 1.0;
	player->dy = 0.0;
	player->dz = 0.0;
	player->planex = 0.0;
	player->planey = 0.6;
	player->frametime = 0.03;
	player->movespeed = player->frametime * 2.5;
}

void	init_render(t_var *info, t_render *render, int x0, int sector_id)
{
	render->sector_id = sector_id;
	render->s = get_a_sector_by_id(info->map, 1);
	render->wall = NULL;
	render->next_render = NULL;
	render->sec_0 = render->s;
	render->nb_sec = 0;
	init_nb_sec(render->sec_0, render);
	init_item_id(render, 0);
}

void	init_item_id(t_item item, int i)
{
	item->id = i;
	if (item->next_item)
		init_item_id(item->next_item, i + 1);
}

int		init_next_render(t_var *info, t_render *render)
{
	t_render	*tmp;

	render->next_render = (t_render*)ft_memalloc(sizeof(t_render));
	if ((tmp = render->next_render) == NULL)
		return (0);
	init_render(info, tmp, render->x, render->wall->sector_id_it_leads_to);
	tmp->x1 = render->next_x;
	return (1);
}
