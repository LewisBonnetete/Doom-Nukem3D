/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/07 18:14:47 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem_edit.h"

void	command_hud2(t_var *info, SDL_Color color)
{
	SDL_Rect	pos;
	SDL_Surface *texte;

	texte = TTF_RenderText_Blended(info->font, "[  I  ] Add an Item", color);
	pos.x = WINDOW_H + 20;
	pos.y = 240;
	SDL_BlitSurface(texte, NULL, info->image, &pos);
	SDL_FreeSurface(texte);
	texte = TTF_RenderText_Blended(info->font, "[ P ] Add a Prop", color);
	pos.x = WINDOW_H + 20;
	pos.y = 280;
	SDL_BlitSurface(texte, NULL, info->image, &pos);
	SDL_FreeSurface(texte);
	texte = TTF_RenderText_Blended(info->font, "[ E ] Add an Enemy", color);
	pos.x = WINDOW_H + 20;
	pos.y = 320;
	SDL_BlitSurface(texte, NULL, info->image, &pos);
	SDL_FreeSurface(texte);
	texte = TTF_RenderText_Blended(info->font,
	"[ R ] Remove an Item, a Prop or an Enemy", color);
	pos.x = WINDOW_H + 20;
	pos.y = 360;
	SDL_BlitSurface(texte, NULL, info->image, &pos);
	SDL_FreeSurface(texte);
}

void	command_hud(t_var *info, SDL_Color color)
{
	SDL_Rect	pos;
	SDL_Surface *texte;

	texte = TTF_RenderText_Blended(info->font,
	"[ S ] Create a new sector", color);
	pos.x = WINDOW_H + 20;
	pos.y = 160;
	SDL_BlitSurface(texte, NULL, info->image, &pos);
	SDL_FreeSurface(texte);
	texte = TTF_RenderText_Blended(info->font,
	"[ D ] Delete sector or cancel creations", color);
	pos.x = WINDOW_H + 20;
	pos.y = 200;
	SDL_BlitSurface(texte, NULL, info->image, &pos);
	SDL_FreeSurface(texte);
	texte = TTF_RenderText_Blended(info->font, "[ V ] Validate the map", color);
	pos.x = WINDOW_H + 20;
	pos.y = 400;
	SDL_BlitSurface(texte, NULL, info->image, &pos);
	SDL_FreeSurface(texte);
	command_hud2(info, color);
}

void	info_hud_2(t_var *info, SDL_Color color)
{
	SDL_Rect	pos;
	SDL_Surface	*texte;

	texte = TTF_RenderText_Blended(info->font,
	"You must build your map from top to bottom", color);
	pos.x = WINDOW_H + 20;
	pos.y = 90;
	SDL_BlitSurface(texte, NULL, info->image, &pos);
	SDL_FreeSurface(texte);
	texte = TTF_RenderText_Blended(info->font, "and from left to right", color);
	pos.x = WINDOW_H + 20;
	pos.y = 120;
	SDL_BlitSurface(texte, NULL, info->image, &pos);
	SDL_FreeSurface(texte);
}

void	info_hud(t_var *info, SDL_Color color)
{
	SDL_Rect	pos;
	SDL_Surface	*texte;

	texte = TTF_RenderText_Blended(info->font,
	"We will be using the terminal to define most", color);
	pos.x = WINDOW_H + 20;
	pos.y = 20;
	SDL_BlitSurface(texte, NULL, info->image, &pos);
	SDL_FreeSurface(texte);
	texte = TTF_RenderText_Blended(info->font, "of your map's aspects", color);
	pos.x = WINDOW_H + 20;
	pos.y = 50;
	SDL_BlitSurface(texte, NULL, info->image, &pos);
	SDL_FreeSurface(texte);
	info_hud_2(info, color);
}

void	hud(t_var *info)
{
	t_point		a;
	t_point		b;
	SDL_Color	color;

	a.x = WINDOW_H + 1;
	a.y = 0;
	b.x = WINDOW_W;
	b.y = WINDOW_H;
	draw_square(info, a, b, DARK);
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	command_hud(info, color);
	info_hud(info, color);
}
