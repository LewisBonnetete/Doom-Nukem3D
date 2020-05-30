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
		put_pixel_to_suface(WEST_WALL, render->x,i , info->image);
}

void	draw_textures(t_var *info, t_render *render)
{
	if(render->wall->is_portal)
	{
		//if (render->wall->is_transparent)
		//	draw_tex(info, render);
			//draw_portal_texture(info, render);
			// rajouter la texture sur les pixels dans le rectangle de diagonale (x0,y0) et (x1,y1)
		//if (render->wall->is_textured)
			//draw_tex(info, render);
			//draw_portal_fill(info, render);
			//		Pareil que draw_portal_texture?
			//  texture sur les pixels dans le rectangle de diagonale (x0,y0) et (x1,y1)
			//		OU
			//  texture fill_up et fill_down,
			//	sur les pixels au dessus et en dessous du rectangle de diagonale (x0,y0) et (x1,y1)
	}
	else
    {
		draw_bottop(info, render);
		draw_tex(info, render);
    }
		//horizontalement : remplit, selon la texture, les pixels entre render->x et render->next_x
		//verticalement : voir en fonction de la distance au mur et sa hauteur ?
}
