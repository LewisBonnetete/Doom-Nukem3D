#include "doom-nukem.h"

void	rot_right(t_var *info)
{
	info->olddirx = info->player->dx;
	info->player->dx = info->player->dx * cos(-info->rotspeed) - info->player->dy
	* sin(-info->rotspeed);
	info->player->dy = info->olddirx * sin(-info->rotspeed) + info->player->dy
	* cos(-info->rotspeed);
	info->oldplanex = info->player->planex;
	info->player->planex = info->player->planex * cos(-info->rotspeed) - info->player->planey
	* sin(-info->rotspeed);
	info->player->planey = info->oldplanex * sin(-info->rotspeed) + info->player->planey
	* cos(-info->rotspeed);
}

void	rot_left(t_var *info)
{
	info->olddirx = info->player->dx;
	info->player->dx = info->player->dx * cos(info->rotspeed) - info->player->dy
	* sin(info->rotspeed);
	info->player->dy = info->olddirx * sin(info->rotspeed) + info->player->dy
	* cos(info->rotspeed);
	info->oldplanex = info->player->planex;
	info->player->planex = info->player->planex * cos(info->rotspeed) - info->player->planey
	* sin(info->rotspeed);
	info->player->planey = info->oldplanex * sin(info->rotspeed) + info->player->planey
	* cos(info->rotspeed);
}

int     dealer(t_var *info, t_render *render)
{
	SDL_Event e;

	if (SDL_PollEvent(&e) == 1)
	{
		if (e.type == SDL_QUIT)
			return (0);
		if (e.key.keysym.sym == SDLK_ESCAPE)
			return (0);
		if (e.type == SDL_MOUSEBUTTONDOWN)
			return(0);
        if (e.key.keysym.sym == SDLK_LEFT)
	    {
		    if (e.key.state == SDL_PRESSED)
		    {
                rot_left(info);
                raycasting(info, render);
            }
        }
	    if (e.key.keysym.sym == SDLK_RIGHT)
	    {
		    if (e.key.state == SDL_PRESSED)
            {
                rot_right(info);
                raycasting(info, render);
            }
        }
    }
    return(1);
}
