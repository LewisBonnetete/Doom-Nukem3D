/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/17 13:24:39 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	hp_hud_help(t_var *info, char *nb, SDL_Rect pos, SDL_Color color)
{
	SDL_Surface *texte;

	texte = TTF_RenderText_Blended(info->font, nb, color);
	SDL_BlitSurface(texte, NULL, info->image, &pos);
	SDL_FreeSurface(texte);
}
