/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/06/30 17:57:50 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	weapon(t_var *info, t_player *player, SDL_Color color)
{
	SDL_Surface	*texte;
	SDL_Rect	pos;
	
	texte = TTF_RenderText_Blended(info->font, "weapon", color);
	pos.x = 20;
	pos.y = 100;
	SDL_BlitSurface(texte, NULL, info->image, &pos);
	SDL_FreeSurface(texte);
}

void	inventory(t_var *info, t_player *player, SDL_Color color)
{
	SDL_Surface	*texte;
	SDL_Rect	pos;
	
	texte = TTF_RenderText_Blended(info->font, "inventory", color);
	pos.x = 20;
	pos.y = 80;
	SDL_BlitSurface(texte, NULL, info->image, &pos);
	SDL_FreeSurface(texte);
}

void	name(t_var *info, t_map *map, SDL_Color color)
{
	SDL_Surface	*texte;
	SDL_Rect	pos;
	
	texte = TTF_RenderText_Blended(info->font, "name", color);
	pos.x = 20;
	pos.y = 60;
	SDL_BlitSurface(texte, NULL, info->image, &pos);
	SDL_FreeSurface(texte);
	
}

void	hp(t_var *info, t_player *player, SDL_Color color)
{
	SDL_Surface	*texte;
	SDL_Rect	pos;
	
	texte = TTF_RenderText_Blended(info->font, "hp", color);
	pos.x = 20;
	pos.y = 20;
	SDL_BlitSurface(texte, NULL, info->image, &pos);
	SDL_FreeSurface(texte);
}

void	ammo(t_var *info, t_player *player, SDL_Color color)
{
	SDL_Surface	*texte;
	SDL_Rect	pos;
	
	texte = TTF_RenderText_Blended(info->font, "ammo", color);
	pos.x = 20;
	pos.y = 40;
	SDL_BlitSurface(texte, NULL, info->image, &pos);
	SDL_FreeSurface(texte);
}
