#include "doom-nukem.h"

char	**tab_path()
{
	int	i;
	char	*tab_text[NB_TEXTURE];

	i = -1;
	while (++i < NB_TEXTURE)
	{
		if (i - 1 < 0)
			tab_text[i] = ft_strdup(TEXTURE_1);
		else if (tab_text[i - 1] == TEXTURE_1)
			tab_text[i] = ft_strdup(TEXTURE_2);
		else if (tab_text[i - 1] == TEXTURE_2)
			tab_text[i] = ft_strdup(TEXTURE_3);
	}
	return (tab_text);
}

int	load_text(char **tab, t_render renderer)
{
	//mettre tab_sdl dans une structure
	SDL_Surface	*tab_sdl[NB_TEXTURE];
	//SDL_Texture	*tab_text[NB_TEXTURE];
	int		i;

	i = -1;
	while (++i < NB_TEXTURE)
		if ((tab_sdl[i] = IMG_Load(tab[i])) == 0)
			return (0);
	i = -1;
/* 	while (++i < NB_TEXTURE)
	{
		if ((tab_text[i] = SDL_CreateTextureFromSurface(renderer, tab_sdl[i])) == 0)
			return (0);
		SDL_FreeSurface(tab_sdl[i]);
	}
*/
	return (1);
}
