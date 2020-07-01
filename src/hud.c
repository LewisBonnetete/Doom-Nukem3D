/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/01 17:03:18 by lbonnete         ###   ########.fr       */
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

void	inventory(t_var *info, t_player *player, SDL_Color color)
{
	SDL_Surface	*texte;
	SDL_Rect	pos;
	t_item		*item;

	texte = TTF_RenderText_Blended(info->font, "inventory", color);
	pos.x = WINDOW_W - 95;
	pos.y = 5;
	SDL_BlitSurface(texte, NULL, info->image, &pos);
	SDL_FreeSurface(texte);
	// item = info->render->item;
	//Ca ca segfault aled
	pos.y += 10;
	while (item && pos.y < WINDOW_H - 40)
	{
		if (item->cap == 2)
		{
			texte = TTF_RenderText_Blended(info->font, item->name, color);
			pos.y += 20 ;
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
	int			i;

	i = 0;
	while (map->name[i - 1] != '/')
		i++;
	texte = TTF_RenderText_Blended(info->font, &map->name[i], color);
	pos.x = 10;
	pos.y = 5;
	SDL_BlitSurface(texte, NULL, info->image, &pos);
	SDL_FreeSurface(texte);
	
}

void	hp(t_var *info, t_player *player, SDL_Color color)
{
	SDL_Surface	*texte;
	SDL_Rect	pos;
	char		*nb;

	nb = ft_itoa(player->hp);
	texte = TTF_RenderText_Blended(info->font, nb, color);
	pos.x = WINDOW_W - 195;
	pos.y = WINDOW_H - 30;
	SDL_BlitSurface(texte, NULL, info->image, &pos);
	SDL_FreeSurface(texte);
	free(nb);
}

void	ammo(t_var *info, t_player *player, SDL_Color color)
{
	SDL_Surface	*texte;
	SDL_Rect	pos;
	char		*nb;

	nb = ft_itoa(player->ammo);
	texte = TTF_RenderText_Blended(info->font, nb, color);
	pos.x = 170;
	pos.y = WINDOW_H - 30;
	SDL_BlitSurface(texte, NULL, info->image, &pos);
	SDL_FreeSurface(texte);
	free(nb);
}
