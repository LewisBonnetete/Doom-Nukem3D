#include "doom_nukem.h"

double     calc_dist(t_point a, t_point b)
{
    double res;

    res = (b.x - a.x) * (b.x - a.x) 
    + (b.y - a.y) * (b.y - a.y);
    return (sqrt(res));
}
void    init_tab(int *tab, int n)
{
    int i;

    i = 0;
    while (i <= n + 1)
    {
        tab[i] = 0;
        i++;
    }
}

static	void		free_itab(t_itab *tab)
{
	if (tab->name)
		free(&tab->name);
	free(&tab);
}

static	void		free_ray(t_ray *ray)
{
	free(&ray);
}

static	void	free_wall(t_wall *wall)
{
	free(&wall);
}

static	void	free_item(t_item *item)
{
	free(&item);
}

static  void        free_sector(t_sector *sector)
{
	if (sector->walls)
		free(&sector->walls);
	if (sector->next_sector)
		free_sector(sector->next_sector);
    free(&sector);
}

static  void		free_render(t_render *render)
{
    int i;

	i = 0;
	while(i < NB_TEXT)
	{
		if (render->tab_sdl[i])
			SDL_FreeSurface(render->tab_sdl[i++]);
	}
	i = 0;
	while(i < NB_TEXT_I)
	{
		if (render->tab_sdl_item[i])
			SDL_FreeSurface(render->tab_sdl_item[i++]);
	}
	if(render->itab)
		free_itab(render->itab);
	if(render->ray)
		free_ray(render->ray);
	if(render->s)
		free_sector(render->s);
	if(render->wall)
		free_wall(render->wall);
	if(render->wall_item)
		free_wall(render->wall_item);
	while (render->item_0)
	{
		free_item(render->item_0);
		render->item_0 = render->item_0->next_item;
	}
	free(&render);
}

static  void        free_info(t_var *info)
{
	if (info->image)
		SDL_FreeSurface(info->image);
	if (info->texture)
		SDL_DestroyTexture(info->texture);
	if (info->window)
		SDL_DestroyWindow(info->window);
	if (info->render)
		free_render(info->render);
	free(&info);
}


void       free_map(t_map *map)
{
    if (map->sectors)
        free(&map->sectors);
    free(map);
}

void        ft_exit(t_var *info, t_render *render)
{
	if (info)
		free_info(info);
	SDL_Quit();
	exit (0);
}
