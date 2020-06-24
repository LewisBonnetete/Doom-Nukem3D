#include "doom-nukem.h"

Uint32			get_pixel(SDL_Surface *tex, int x, int y)
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

void			tex_floor_ciel(t_var *info, t_render *render)
{
	int i;
	int j;
	int k;
	double dirx0;
	double diry0;
	double dirx1;
	double diry1;
	int p;
	double dist;
	double stepx;
	double stepy;
	double floorx;
	double floory;
	i = 0;
	j = 0;
	k = 0;
	double posz;

	while (i++ < WINDOW_H)
	{
		dirx0 = info->player->dx - info->player->planex;
		diry0 = info->player->dy - info->player->planey;
		dirx1 = info->player->dx + info->player->planex;
		diry1 = info->player->dy + info->player->planey;
		posz = 0.5 * WINDOW_H;
		p = i - WINDOW_H / 2;
		dist = posz / p;
		stepx = dist * (dirx1 - dirx0) / WINDOW_W;
		stepy = dist * (diry1 - diry0) / WINDOW_W;
		floorx = info->player->posx + dist * dirx0;
		floory = info->player->posy + dist * diry0;
		j = 0;
		while (j++ < WINDOW_W)
		{
			int cellx = (int)floorx;
			int celly = (int)floory;
			int tx = (int)(render->tab_sdl[render->s->celling.text_id]->w * (floorx - cellx)) & (render->tab_sdl[render->s->celling.text_id]->w - 1);
        	int ty = (int)(render->tab_sdl[render->s->celling.text_id]->h * (floory - celly)) & (render->tab_sdl[render->s->celling.text_id]->h - 1);
			floorx += stepx;
			floory += stepy;
			// printf("tx = %f\n", tx);
			// printf("ty = %f\n", ty);
			Uint32 color = get_pixel(render->tab_sdl[1],tx,ty);
			put_pixel_to_suface(color, j, i, info->image);
			color = get_pixel(render->tab_sdl[2],tx,ty);
			put_pixel_to_suface(color,j , WINDOW_H - i - 1, info->image);
		}
	}
}

static	void	ft_put_weapon(t_var *info, t_render *render)
{
	int		x;
	int		y;
	Uint32	color;

	x = 0;
	while (x < render->tab_sdl[3]->w)
	{
		y = 0;
		while (y < render->tab_sdl[3]->h)
		{
			color = get_pixel(render->tab_sdl[3], y, x);
			if (color != 0)
				put_pixel_to_suface(color, x + WINDOW_W / 2 - 45,
				WINDOW_H + y - 125, info->image);
			y++;
		}
		x++;
	}
}

void	put_pixel_to_suface(Uint32 color, int x, int y, SDL_Surface *image)
{
	Uint32 *pixels;

	pixels = image->pixels;
	if (x >= 0 && y >= 0 && x < image->w && y < image->h)
		pixels[y * image->w + x] = color;
}

void	draw_tex(t_var *info, t_render *render)
{
	int i;

	i = render->wall_y1;
	while (i <= render->wall_y0)
	{
		put_pixel_to_suface(255, render->x, i, info->image);
		i++;
	}
}


void	draw_bottop(t_var *info, t_render *render)
{
	int i;

	i = WINDOW_H + 1;
	while (--i > render->wall_y1)
		put_pixel_to_suface(GRASS_GREEN, render->x,i , info->image);
	i = render->wall_y0 + 1;
	while (--i > 0)
		put_pixel_to_suface(SKY_BLUE, render->x,i , info->image);
}

void	draw_textures(t_var *info, t_render *render)
{
	if(render->wall->is_portal)
	{
		//if (render->wall->is_transparent)
		//{
		//	draw_tex(info, render);
		//	draw_portal_texture(info, render);
		//}
		// rajouter la texture sur les pixels dans le rectangle de diagonale (x0,y0) et (x1,y1)
		//if (render->wall->is_textured)
		//{
		//	draw_tex(info, render);
		//	draw_portal_fill(info, render);
		//}
		//		Pareil que draw_portal_texture?
		//  texture sur les pixels dans le rectangle de diagonale (x0,y0) et (x1,y1)
		//		OU
		//  texture fill_up et fill_down,
		//	sur les pixels au dessus et en dessous du rectangle de diagonale (x0,y0) et (x1,y1)
	}
	else
    {
		//draw_bottop(info, render);
		draw_texture_wall(info, render);
		ft_put_weapon(info, render);
    }
		//horizontalement : remplit, selon la texture, les pixels entre render->x et render->next_x
		//verticalement : voir en fonction de la distance au mur et sa hauteur ?
}

void	draw_texture_wall(t_var *info, t_render *render)
{
	double 		pos_relative;
	t_point		hit;
	int			i;
	double 		texy;
	int			temp;
	Uint32		color;
	double 		temp2;
	hit.x = render->ray->x2;
	hit.y = render->ray->y2;
	render->wall->wall_leng = calc_dist(render->wall->a, render->wall->b);
	pos_relative = calc_dist(hit, render->wall->b);
	temp2 = (double)render->tab_sdl[0]->h / (double)WALL_H; //Dans le cas d un item wallH = itemH/2
	pos_relative = pos_relative * temp2;
	temp = (int)pos_relative;
	pos_relative -= temp;
	pos_relative = pos_relative * render->tab_sdl[render->wall->text_id]->w;
	render->wall_height = fabs(render->wall_height);
	double step = 1.0 * (double)render->tab_sdl[render->wall->text_id]->h / render->wall_height;
	i = render->wall_y1;
	texy = 0;
	while (i <= render->wall_y0)
	{
		if (i == render->wall_y0 || i == render->wall_y1)
		{
			put_pixel_to_suface(BLACK, render->x, i, info->image);
		}
		else
		{
			texy += step;
			color = get_pixel(render->tab_sdl[render->wall->text_id], (int)pos_relative, (int)texy);
			put_pixel_to_suface(color ,render->x, i, info->image);	
		}
		i++;
	}
}

