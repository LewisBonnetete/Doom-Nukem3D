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
	
	(void)render;
	if (SDL_PollEvent(&e) == 1)
	{
		if (e.type == SDL_QUIT)
			ft_exit(info, render);
		if (e.key.keysym.sym == SDLK_ESCAPE)
			ft_exit(info, render);
		if (e.type == SDL_MOUSEBUTTONDOWN)
			ft_exit(info, render);
        if (e.key.keysym.sym == SDLK_LEFT)
	    {
		    if (e.key.state == SDL_PRESSED)
		    {
                rot_left(info);
            }
        }
	    if (e.key.keysym.sym == SDLK_RIGHT)
	    {
		    if (e.key.state == SDL_PRESSED)
            {
                rot_right(info);
            }
        }
		if (e.key.keysym.sym == SDLK_UP)
		{
			if (e.key.state == SDL_PRESSED)
			{
					info->player->posx += info->player->dx * info->player->movespeed;
					info->player->posy += info->player->dy * info->player->movespeed;
			}		
		}
		if (e.key.keysym.sym == SDLK_DOWN)
  		{
			if (e.key.state == SDL_PRESSED)
			{
				info->player->posx -= info->player->dx * info->player->movespeed;
				info->player->posy -= info->player->dy * info->player->movespeed;
			}
		}
	}
    return (1);
}