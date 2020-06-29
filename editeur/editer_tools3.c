
#include "doom-nukem_edit.h"

int		x_coo(SDL_Event *event, t_map *map)
{
	float	temp;

	temp = (float)event->button.x / (float)(WINDOW_H - 50) * map->size;
	return (round(temp));
}

int		y_coo(SDL_Event *event, t_map *map)
{
	float	temp;

	temp = (float)event->button.x / (float)(WINDOW_H - 50) * map->size;
	return (round(temp));
}
