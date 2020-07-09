#include "doom_nukem.h"

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
