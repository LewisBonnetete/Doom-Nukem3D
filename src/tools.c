#include "doom-nukem.h"

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

// void                cpy_walls(t_wall *dest, t_wall *src)
// {
//     dest->wall_leng = src->wall_leng;
//     dest->text_id = src->text_id;
//     dest->wall_id = src->wall_id;
//     dest->is_portal = src->is_portal;
//     dest->is_transparent = src->is_transparent;
//     dest->is_textured = src->is_textured;
//     dest->fill_up = src->fill_up;
//     dest->fill_down = src->fill_down;
//     dest->sector_id = src->sector_id;
//     dest->height = src->height;
//     dest->sector_id_it_leads_to = src->sector_id_it_leads_to;
//     dest->a = src->a;
//     dest->b = src->b;
//     dest->c = src->c;
//     dest->d = src->d;
// }

// void                cpy_sector(t_sector *sec, t_sector *src)
// {
//     int i;

//     i = 0;
//     sec->sector_id = src->sector_id;
//     sec->nbr_walls = src->nbr_walls;    
//     sec->light = src->light;
//     if (!(sec->walls = (t_wall *)ft_memalloc(sizeof(t_wall) * src->nbr_walls)))
//         return (0);
//     while (i++ < src->nbr_walls)
//         cpy_walls(sec->walls, src->walls);
//     if (src->next_sector)
//     {
//         if (!(sec->next_sector = (t_sector *)ft_memalloc(sizeof(t_sector))))
//             return (0);
//         cpy_sector(sec->next_sector, src->next_sector);
//     } 
// }
// t_render            *cpy_render(t_render *render)
// {
//     t_render *dest;

//     if (!(dest = (t_render *)ft_memalloc(sizeof(t_render))))
//         return (0);
//     dest->x = render->x;
//     dest->sector_id = render->sector_id;
//     dest->nb_sec = render->nb_sec;
//     if (!(dest->s = (t_sector *)ft_memalloc(sizeof(t_sector))))
//         return (0);
//     cpy_sector(dest->s, t_render->s);
//     return (dest);
// }

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
    free(&info);
}

static  void        free_sector(t_sector *sector)
{
    if (sector->walls)
        free(&sector->walls);
    if (sector->info == NULL)
        free_info(sector->info);
    if (sector->next_sector)
        free_sector(sector->next_sector);
    free(&sector);
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
    free(&render);
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
