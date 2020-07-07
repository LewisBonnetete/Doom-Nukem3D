#include "doom_nukem.h"

int		tab_path(t_render *renderer)
{
	int	i;

	i = -1;
	while (++i < NB_TEXT)
	{
		if (i == 0)
			if ((renderer->tab_sdl[i] = IMG_Load("./xpm_textures/stone2.png")) == 0)
				return (0);
		if (i == 1)
			if ((renderer->tab_sdl[i] = IMG_Load("./xpm_textures/dark_wall.png")) == 0)
				return (0);
		if (i == 2)
			if ((renderer->tab_sdl[i] = IMG_Load("./xpm_textures/stone3.png")) == 0)
				return (0);
		if (i == 3)
			if ((renderer->tab_sdl[i] = IMG_Load("./xpm_textures/Jagpistol.png")) == 0)
				return (0);
	}
	renderer->tab_sdl[i] = NULL;
	return (1);
}

int		tab_path_text(t_render *renderer)
{
	int	i;

	i = -1;
	while (++i < NB_TEXT_I)
	{
		if (i == 0)
			if ((renderer->tab_sdl_item[i] = IMG_Load("./xpm_textures/ak47.png")) == 0)
				return (0);
		if (i == 1)
			if ((renderer->tab_sdl_item[i] = IMG_Load("./xpm_textures/creeper.png")) == 0)
				return (0);
		if (i == 2)
			if ((renderer->tab_sdl_item[i] = IMG_Load("./xpm_textures/barrel.png")) == 0)
				return (0);
		if (i == 3)
			if ((renderer->tab_sdl_item[i] = IMG_Load("./xpm_textures/soldier.png")) == 0)
				return (0);
		if (i == 4)
			if ((renderer->tab_sdl_item[i] = IMG_Load("./xpm_textures/heal.png")) == 0)
				return (0);
		if (i == 5)
			if ((renderer->tab_sdl_item[i] = IMG_Load("./xpm_textures/balle.png")) == 0)
				return (0);
		if (i == 6)
			if ((renderer->tab_sdl_item[i] = IMG_Load("./xpm_textures/dos_soldier.png")) == 0)
				return (0);
	}
	renderer->tab_sdl_item[7] = NULL;
	return (1);
}
// int	load_text(char **tab, t_render renderer)
// {
// 	int		i;

// 	i = -1;
// 	while (++i < NB_TEXT)
// 		if ((renderer.tab_sdl[i] = IMG_Load(tab[i])) == 0)
// 			return (0);
// 	renderer.tab_sdl[i] = NULL;
// /*	i = -1;
//  	while (++i < NB_TEXTURE)
// 	{
// 		if ((tab_text[i] = SDL_CreateTextureFromSurface(renderer, tab_sdl[i])) == 0)
// 			return (0);
// 		SDL_FreeSurface(tab_sdl[i]);
// 	}
// */
// 	return (1);
// }
