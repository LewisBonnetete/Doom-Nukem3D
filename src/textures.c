#include "doom-nukem.h"

void	tab_path(t_render *renderer)
{
	int	i;
	char	*tab_text[NB_TEXT];
	i = -1;
	while (++i < NB_TEXT)
	{
		if (i - 1 < 0)
			tab_text[i] = ft_strdup(TEXTURE_1);
		else if (tab_text[i - 1] == TEXTURE_1)
			tab_text[i] = ft_strdup(TEXTURE_2);
		else if (tab_text[i - 1] == TEXTURE_2)
			tab_text[i] = ft_strdup(TEXTURE_3);
	}
	i = -1;
	while (++i < NB_TEXT)
		if ((renderer->tab_sdl[i] = IMG_Load(tab_text[i])) == 0)
			return;
	free(tab_text);
	free(&tab_text);
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
