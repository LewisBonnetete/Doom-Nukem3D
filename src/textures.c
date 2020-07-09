/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:04:28 by lewis             #+#    #+#             */
/*   Updated: 2020/07/09 14:53:21 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		tab_path(t_render *renderer)
{
	int	i;

	i = -1;
	while (++i < NB_TEXT)
	{
		if (i == 0)
			if ((renderer->tab_sdl[i] =
				IMG_Load("./xpm_textures/stone2.png")) == 0)
				return (0);
		if (i == 1)
			if ((renderer->tab_sdl[i] =
				IMG_Load("./xpm_textures/dark_wall.png")) == 0)
				return (0);
		if (i == 2)
			if ((renderer->tab_sdl[i] =
				IMG_Load("./xpm_textures/stone3.png")) == 0)
				return (0);
		if (i == 3)
			if ((renderer->tab_sdl[i] =
				IMG_Load("./xpm_textures/Jagpistol.png")) == 0)
				return (0);
	}
	return (1);
}

int		tab_path_text(t_render *renderer)
{
	if ((renderer->tab_sdl_item[0] =
		IMG_Load("./xpm_textures/ak47.png")) == 0)
		return (0);
	if ((renderer->tab_sdl_item[1] =
		IMG_Load("./xpm_textures/creeper.png")) == 0)
		return (0);
	if ((renderer->tab_sdl_item[2] =
		IMG_Load("./xpm_textures/barrel.png")) == 0)
		return (0);
	if ((renderer->tab_sdl_item[3] =
		IMG_Load("./xpm_textures/soldier.png")) == 0)
		return (0);
	if ((renderer->tab_sdl_item[4] =
		IMG_Load("./xpm_textures/heal.png")) == 0)
		return (0);
	if ((renderer->tab_sdl_item[5] =
		IMG_Load("./xpm_textures/balle.png")) == 0)
		return (0);
	if ((renderer->tab_sdl_item[6] =
		IMG_Load("./xpm_textures/dos_soldier.png")) == 0)
		return (0);
	if ((renderer->tab_sdl_item[7] =
		IMG_Load("./xpm_textures/portal.png")) == 0)
		return (0);
	return (1);
}
