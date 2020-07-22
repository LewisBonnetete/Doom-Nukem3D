/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/22 18:34:27 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	weapon(t_var *info, t_player *player, SDL_Color color)
{
	SDL_Surface	*texte;
	SDL_Rect	pos;

	if (player->weapon)
	{
		texte = TTF_RenderText_Blended(info->font, player->weapon->name, color);
		pos.x = 10;
		pos.y = WINDOW_H - 30;
		SDL_BlitSurface(texte, NULL, info->image, &pos);
		SDL_FreeSurface(texte);
	}
}

void	inventory(t_var *info, SDL_Color color)
{
	SDL_Surface	*texte;
	SDL_Rect	pos;
	t_item		*item;

	texte = TTF_RenderText_Blended(info->font, "inventory", color);
	pos.x = WINDOW_W - 95;
	pos.y = 5;
	SDL_BlitSurface(texte, NULL, info->image, &pos);
	item = info->render->item_0;
	pos.y += 10;
	SDL_FreeSurface(texte);
	while (item && pos.y < WINDOW_H - 40)
	{
		if (item->cap == 2)
		{
			texte = TTF_RenderText_Blended(info->font, item->name, color);
			pos.y += 20;
			SDL_BlitSurface(texte, NULL, info->image, &pos);
			SDL_FreeSurface(texte);
		}
		item = item->next_item;
	}
}

void	name(t_var *info, t_map *map, SDL_Color color)
{
	SDL_Surface	*texte;
	SDL_Rect	pos;

	texte = TTF_RenderText_Blended(info->font, map->name, color);
	pos.x = 10;
	pos.y = 5;
	SDL_BlitSurface(texte, NULL, info->image, &pos);
	SDL_FreeSurface(texte);
}

void	hp(t_var *info, t_player *player, SDL_Color color)
{
	SDL_Rect	pos;
	char		*nb;

	nb = ft_itoa(player->hp);
	pos.x = WINDOW_W - 195;
	pos.y = WINDOW_H - 30;
	if (info->player->hp < info->player->hp_p)
	{
		color.r = (RED >> 16) & 0xFF;
		color.g = (RED >> 8) & 0xFF;
		color.b = RED & 0xFF;
		info->player->hp_p -= 1;
	}
	if (info->player->hp > info->player->hp_p)
	{
		color.r = (GREEN >> 16) & 0xFF;
		color.g = (GREEN >> 8) & 0xFF;
		color.b = GREEN & 0xFF;
		info->player->hp_p += 1;
		free(nb);
		nb = ft_itoa(player->hp_p);
	}
	hp_hud_help(info, nb, pos, color);
	free(nb);
}

void	munitions(t_var *info, SDL_Color color)
{
	t_item		*weapon;
	SDL_Rect	pos;
	char		*nb;

	if (may_weapon(info->render->item_0))
	{
		weapon = go_to_item(info->render->item_0, 'a');
		while (weapon && weapon->hold != 1)
		{
			if (weapon->next_item)
				weapon = go_to_item(weapon->next_item, 'a');
			else
				weapon = NULL;
		}
		if (!weapon)
		{
			weapon = go_to_item(info->render->item_0, 'a');
			weapon->hold = 1;
		}
		nb = ft_itoa(weapon->mun);
		pos.x = 170;
		pos.y = WINDOW_H - 30;
		hp_hud_help(info, nb, pos, color);
		free(nb);
	}
}
