#include "doom-nukem.h"

void	tab_path(t_render *renderer)
{
	int	i;

	i = -1;
	while (++i < NB_TEXT)
	{
		if (i == 0)
			if ((renderer->tab_sdl[i] = IMG_Load("./xpm_textures/stone.png")) == 0)
				return;
		if (i == 1)
			if ((renderer->tab_sdl[i] = IMG_Load(TEXTURE_2)) == 0)
				return;
		if (i == 2)
			if ((renderer->tab_sdl[i] = IMG_Load(TEXTURE_3)) == 0)
				return;
	}
	renderer->tab_sdl[i] = NULL;
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
