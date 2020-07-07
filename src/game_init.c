#include "doom_nukem.h"

void			ft_init_pour_linstant(t_var *info)
{
	info->frametime = 0.03;
	info->rotspeed = info->frametime * 0.5;
	info->d_gun = 0;
	info->d_gunb = 0;
	info->clock = 0;
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
	player->weapon = NULL;
	player->hp = 100;
	player->ammo = 0;
}

t_item	*init_item(t_render *render, t_item *src, int i)
{
	t_item	*dest;

	if (!dest)
		if (!(dest = (t_item *)ft_memalloc(sizeof(t_item))))
			return (0);
	dest->name = ft_strdup(src->name);
	dest->x = src->x;
	dest->y = src->y;
	dest->cap = 0;
	dest->id = i;
	render->nbr_items++;
	if (dest->name[0] == 'a')
	{
		dest->h = 128;
		dest->w = 128;
		dest->text_id = 0;
		dest->mun = 50;
		dest->hold = 0;
	}
	else if (dest->name[0] == 'c')
	{
		dest->h = 350;
		dest->w = 350;
		dest->text_id = 1;
		dest->pv = 20;
	}
	else if (dest->name[0] == 'b')
	{
		dest->h = 300;
		dest->w = 300;
		dest->text_id = 2;
	}
	else if (dest->name[0] == 'h')
	{
		dest->h = 250;
		dest->w = 250;
		dest->text_id = 4;
	}
	else if (dest->name[0] == 'm')
	{
		dest->h = 100;
		dest->w = 100;
		dest->text_id = 5;
	}
	else if (dest->name[0] == 's')
	{
		dest->h = 300;
		dest->w = 300;
		dest->text_id = 3;
		dest->pv = 40;
	}
	else
	{
		render->nbr_items--;
		if (src->next_item)
			dest = init_item(render, src->next_item, i);
		else
			dest = NULL;
		return (dest);
	}
	if (src->next_item)
		dest->next_item = init_item(render, src->next_item, i + 1);
	else
		dest->next_item = NULL;
	return (dest);
}

void	init_render(t_var *info, t_render *render, int x0, int sector_id)
{
	render->sector_id = sector_id;
	render->s = get_a_sector_by_id(info->map, 1);
	render->wall = NULL;
	render->sec_0 = render->s;
	render->nb_sec = 0;
	render->nbr_items = 0;
	if (info->map->items && info->map->items->name[0] != 0)
	{
		render->item = init_item(render, info->map->items, 0);
		render->item_0 = render->item;
	}
	init_nb_sec(render->sec_0, render);
}

/*int		init_next_render(t_var *info, t_render *render)
{
	t_render	*tmp;

	render->next_render = (t_render*)ft_memalloc(sizeof(t_render));
	if ((tmp = render->next_render) == NULL)
		return (0);
	init_render(info, tmp, render->x, render->wall->sector_id_it_leads_to);
	tmp->x1 = render->next_x;
	return (1);
}*/
