#include "doom_nukem.h"

void		init_floor(t_var *info, t_f_tool *tool)
{
	tool->dirx0 = info->player->dx - info->player->planex;
	tool->diry0 = info->player->dy - info->player->planey;
	tool->dirx1 = info->player->dx + info->player->planex;
	tool->diry1 = info->player->dy + info->player->planey;
	tool->posz = 0.5 * WINDOW_H;
	tool->p = tool->i - WINDOW_H / 2;
	tool->dist = tool->posz / tool->p;
	tool->stepx = tool->dist * (tool->dirx1 - tool->dirx0) / WINDOW_W;
	tool->stepy = tool->dist * (tool->diry1 - tool->diry0) / WINDOW_W;
	tool->floorx = info->player->posx + tool->dist * tool->dirx0;
	tool->floory = info->player->posy + tool->dist * tool->diry0;
	tool->j = 0;
}


int			darken_floor(t_f_tool *tool, t_render *render)
{
	Uint32	color;

	color = get_pixel(render->tab_sdl[2], tool->tx, tool->ty);
	t_rgb	rgb;
	double	screen_r;
	double	screen_i;
	rgb.r = (color >> 16) & 0xFF;
	rgb.g = (color >> 8) & 0xFF;
	rgb.b = color & 0xFF;
	screen_r = ft_fabs(2.0 * (double)tool->i / (double)WINDOW_H - 1);
	screen_i = ft_fabs(2.0 * (double)tool->j / (double)WINDOW_W - 1);
	rgb.r = rgb.r / (0.33 * tool->dist +
	(screen_r * screen_r + screen_i * screen_i) * 3);
	rgb.g = rgb.g / (0.33 * tool->dist +
	(screen_r * screen_r + screen_i * screen_i) * 3);
	rgb.b = rgb.b / (0.33 * tool->dist + (screen_r *
	screen_r + screen_i * screen_i) * 3);
	if (rgb.r >= 255)
		rgb.r = 255;
	if (rgb.g >= 255)
		rgb.g = 255;
	if (rgb.b >= 255)
		rgb.b = 255;
	return (rgb_calc(rgb.r, rgb.g, rgb.b));
}

int			darken_wall(t_var *info, Uint32 color, t_render *render, int i)
{
	t_rgb	rgb;
	double	screen_r;
	double	screen_i;

	rgb.r = (color >> 16) & 0xFF;
	rgb.g = (color >> 8) & 0xFF;
	rgb.b = color & 0xFF;
	screen_r = ft_fabs(render->ray->cam_x);
	screen_i = ft_fabs(2.0 * (double)i / (double)WINDOW_W - 0.70);
	rgb.r = rgb.r / (0.5 * render->wall_dist +
	(screen_r * screen_r + screen_i * screen_i) * 3);
	rgb.g = rgb.g / (0.5 * render->wall_dist +
	(screen_r * screen_r + screen_i * screen_i) * 3);
	rgb.b = rgb.b / (0.5 * render->wall_dist + (screen_r *
	screen_r + screen_i * screen_i) * 3);
	if (rgb.r >= 255)
		rgb.r = 255;
	if (rgb.g >= 255)
		rgb.g = 255;
	if (rgb.b >= 255)
		rgb.b = 255;
	return (rgb_calc(rgb.r, rgb.g, rgb.b));
}

void		w_draw_calc(t_render *render, t_var *info, t_w_draw *draw)
{
	draw->hit.x = render->ray->x2;
	draw->hit.y = render->ray->y2;
	render->wall->wall_leng = calc_dist(render->wall->a, render->wall->b);
	draw->pos_relative = calc_dist(draw->hit, render->wall->b);
	draw->temp2 = (double)render->tab_sdl[0]->h / (double)WALL_H;
	draw->pos_relative = draw->pos_relative * draw->temp2;
	draw->temp = (int)draw->pos_relative;
	draw->pos_relative -= draw->temp;
	draw->pos_relative = draw->pos_relative *
	render->tab_sdl[render->wall->text_id]->w;
	render->wall_height = fabs(render->wall_height);
	draw->step = 1.0 * (double)render->tab_sdl[render->wall->text_id]->h
	/ render->wall_height;
	draw->i = render->wall_y1;
	draw->texy = 0;
}

Uint32		get_pixel(SDL_Surface *tex, int x, int y)
{
	Uint32 color;
	Uint32 *pixels;

	color = 0;
	pixels = tex->pixels;
	if (x >= 0 && y >= 0 && x < tex->w && y < tex->h)
	{
		color = pixels[tex->h * x + y];
	}
	return (color);
}
