#include "doom-nukem.h"

double     calc_dist(t_point a, t_point b)
{
    double res;

    res = (b.x - a.x) * (b.x - a.x) 
    + (b.y - a.y) * (b.y - a.y);
    return (sqrt(res));
}

static  void        free_info(t_var *info)
{
   // if (info->renderer)
      //  SDL_DestroyRenderer(info->renderer);
    if (info->image)
        SDL_FreeSurface(info->image);
    if (info->texture)
        SDL_DestroyTexture(info->texture);
    if (info->window)
       SDL_DestroyWindow(info->window);
    free(info);
}

static  void        free_sector(t_sector *sector)
{
    if (sector->walls)
        free(&sector->walls);
    if (sector->info == NULL)
        free_info(sector->info);
    if (sector->next_sector)
        free_sector(sector->next_sector);
    free(sector);

}

static  void		free_render(t_var *info, t_render *render)
{
    int i;
    // if (render->ray)
    //   free(&render->ray);
    // if (render->wall)
    //   free(&render->wall);
    i = 0;
    while(i < NB_TEXT)
    {
        if (render->tab_sdl[i])
            SDL_FreeSurface(render->tab_sdl[i++]);
    }
    if(render->s)
        free_sector(render->s);
    if(render->next_render)
        free_render(info, render->next_render);
    free(render);
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
    if (render)
        free_render(info, render);
    //if (info->map)
    //    free_map(info->map);
    SDL_Quit();
    exit (0);
}
