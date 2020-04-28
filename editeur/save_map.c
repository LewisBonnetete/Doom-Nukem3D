/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewis <lewis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/04/16 15:27:09 by lewis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//enregistrer une map
#include "doom-nukem_edit.h"
//l'idée est de créer la map de tel sorte que l'on ai une lettre suivi d'une info
//a la fin on aura donc une grande ligne avec toutes les infos dont on va avoir besoin pour la map
//il faut donc utiliser creat_fichier avec le t_map que l'on veut créer en .map
//creation du fichier et ouverture
//strcat avec un seul caractère
char    *little_strcat(char *src, char c)
{
    int     i;

    i = 0;
    while (src[i])
        ++i;
    src[i] = c;
    src[i + 1] = 0;
    return (src);
}
//écriture de la map
int     do_map(t_map *map, int fd)
{
    char    c;

    c = 'm';
    if (write(fd, &c, 1) == -1)
        return (0);
    if (map->box)
        if (do_box(map->box, fd) == 0)
            return (0);
    if (map->sectors)
        if (do_sectors(map->sectors, fd) == 0)
         return (0);
    if (map->size)
        if (do_int(map->size, fd) == 0)
           return (0);
    if (map->spawn)
        if (do_point(map->spawn, fd) == 0)
            return(0);
    return (1);
}
//écriture de la structure box
int     do_box(t_box box, int fd)
{
    int     x;
    char    c;

    c = 'b';
    x = -1;
    if (write(fd, &c, 1) == -1)
        return (0);
    while (++x < 5)
        if (box.walls[x])
            if (do_wall(box.walls[x], fd) == 0)
                return (0);
    if (box.nbr_walls)
        if (do_int(box.nbr_walls, fd) == 0)
            return (0);
    if (box.size)
        if (do_int(box.size, fd) == 0)
            return (0);
    if (box.floor && box.celling)
        if (do_wall(box.floor, fd) == 0 || do_wall(box.celling, fd) == 0)
            return (0);
    return (1);
}
//écriture de la structure sectors
int     do_sectors(t_sector *sectors, int fd)
{
    char    c;

    c = 's';
    if (write(fd, &c, 1) == -1)
        return (0);
    if (do_x_wall(sectors->walls, fd) == 0)
        return (0);
    if (sectors->nbr_walls)
        if (do_int(sectors->nbr_walls, fd) == 0)
            return (0);
    if (sectors->floor && sectors->celling)
        if (do_wall(sectors->floor, fd) == 0 || do_wall(sectors->celling, fd) == 0)
            return (0);
    if (sectors->light && sectors->sector_id)
        if (do_int(sectors->light, fd) == 0 || do_int(sectors->sector_id, fd) == 0)
            return (0);
    if (sectors->next_sector)
        if (do_sectors(sectors->next_sector, fd) == 0)
            return (0);
    if (sectors->map)
        if (do_map(sectors->map, fd) == 0)
            return (0);
    if (sectors->info)
        if (do_var(sectors->info, fd) == 0)
            return (0);
    return (1);
}
//ecriture de plusieurs structure wall
int     do_x_wall(t_wall *wall, int fd)
{
    char    c;
    int     x;

    c = 'x';
    if (write(fd, &c, 1) == -1)
	return (0);
    x = -1;
    while (wall[++x])
        if (do_wall(wall[x], fd) == 0)
            return (0);
    return (1);
}
//écriture de la structure point
int     do_point(t_point point, int fd)
{
    char    c;

    c = 'p';
    if (write(fd, &c, 1) == -1)
        return (0);
    if (point.x && point.y && point.z)
        if (do_int(point.x, fd) == 0 || do_int(point.y, fd) == 0
            || do_int(point.z, fd) == 0)
            return (0);
    return (1);
}
//ecriture de la strcuture wall
int     do_wall(t_wall wall, int fd)
{
    char    c;

    c = 'w';
    if (write(fd, &c, 1) == -1)
        return (0);
    if (wall.a && wall.b && wall.c && wall.d)
        if (do_point(wall.a, fd) == 0 || do_point(wall.b, fd) == 0
            || do_point(wall.c, fd) == 0 || do_point(wall.d, fd) == 0)
            return (0);
    if (wall.text_id && wall.wall_id && wall.is_portal && wall.is_transparent
        && wall.is_textured && wall.fill_up && wall.fill_down && wall.sector_id
        && wall.sector_id_it_leads_to)
        if (do_int(wall.text_id, fd) == 0 || do_int(wall.wall_id, fd) == 0
            || do_int(wall.is_portal, fd) == 0 || do_int(wall.is_transparent, fd) == 0
            || do_int(wall.is_textured, fd) == 0 || do_int(wall.fill_up, fd) == 0
            || do_int(wall.fill_down, fd) == 0 || do_int(wall.sector_id, fd) == 0
            || do_int(wall.sector_id_it_leads_to, fd) == 0)
            return (0);
    return (1);
}
//ecriture de la structure var
int     do_var(t_var *v, int fd)
{
    char    c;
    int     x;

    c = 'v';
    if (write(fd, &c, 1) == -1)
        return (0);
    if (v->weapon_cap && v->texture_cap && v->mouse_in && v->p_x && v->p_y
        && v->sprint && v->x_dec && v->y_dec)
        if (do_int(v->weapon_cap, fd) == 0 || do_int(v->texture_cap, fd) == 0
            || do_int(v->mouse_in, fd) == 0 || do_int(v->p_x, fd) == 0
            || do_int(v->p_y, fd) == 0 || do_int(v->sprint, fd) == 0
            || do_int(v->x_dec, fd) == 0 || do_int(v->y_dec, fd) == 0)
            return (0);
    /*if (v.pf_x && v.pf_y && v.c_angl)
        if (do_float(v.pf_x, fd) == 0 || do_float(v.pf_y, fd) == 0
            || do_float(v.c_angl, fd) == 0)
            return (0);*/
    x = -1;
    while (v->map[++x])
        if (v->map[x])
            if (do_x_char(v->map[x], fd) == 0)
                return (0);
    if (v->posx && v->posy && v->ori_x && v->ori_y && v->dirx && v->diry && v->planex
        && v->planey && v->time && v->oldtime && v->time_reset && v->movespeed
        && v->rotspeed && v->olddirx && v->oldplanex && v->frametime)
        if (do_double(v->posx, fd) == 0 || do_double(v->posy, fd) == 0
            || do_double(v->ori_x, fd) == 0 || do_double(v->ori_y, fd) == 0
            || do_double(v->dirx, fd) == 0 || do_double(v->diry, fd) == 0
            || do_double(v->planex, fd) == 0 || do_double(v->planey, fd) == 0
            || do_double(v->time, fd) == 0 || do_double(v->oldtime, fd) == 0
        || do_double(v->time_reset, fd) == 0 || do_double(v->movespeed, fd) == 0
            || do_double(v->rotspeed, fd) == 0 || do_double(v->olddirx, fd) == 0
            || do_double(v->oldplanex, fd) == 0 || do_double(v->frametime, fd) == 0)
            return (0);
    if (v->input_edit)
        if (do_input(v->input_edit, fd) == 0)
            return (0);
    return (1);
}
//ecriture de la structure input_edit
int     do_input(t_input_edit *in, int fd)
{
    char    c;

    c = 't';
    if (write(fd, &c, 1) == -1)
        return (0);
    if (in->mouse_x && in->mouse_y)
        if (do_double(in->mouse_x, fd) == 0 || do_double(in->mouse_y, fd) == 0)
            return (0);
    if (in->right_click && in->left_click && in->del && in->t_s 
	&& in->t_n && in->t_0 && in->t_1 && in->t_2 && in->t_3 && in->t_4 && in->t_5
        && in->t_6 && in->t_7 && in->t_8 && in->t_9)
        if (do_int(in->right_click, fd) == 0 || do_int(in->left_click, fd) == 0
            || do_int(in->del, fd) == 0 || do_int(in->t_s, fd) == 0
            || do_int(in->t_n, fd) == 0 || do_int(in->t_0, fd) == 0
            || do_int(in->t_1, fd) == 0 || do_int(in->t_2, fd) == 0
            || do_int(in->t_3, fd) == 0 || do_int(in->t_4, fd) == 0
            || do_int(in->t_5, fd) == 0 || do_int(in->t_6, fd) == 0
            || do_int(in->t_7, fd) == 0 || do_int(in->t_8, fd) == 0
            || do_int(in->t_9, fd) == 0 )
            return (0);
    return (1);
}
//ecriture des double
int     do_double(double d, int fd)
{
    char    c;
    int     a;
    int     b;

    c = 'd';
    if (write(fd, &c, 1) == -1)
        return (0);
    a = (int)d;
    d = d - a;
    b = d * 10;
    if (do_int(b, fd) == 0 || do_int(a, fd) == 0)
        return (0);
    return (1);
}
//ecriture d'une chaine de char
int     do_x_char(char *str, int fd)
{
    int     x;
    char    c;

    c = 'e';
    if (write(fd, &c, 1) == -1)
        return (0);
    x = -1;
    while (str[++x])
        if (write(fd, &str[x], 1) == -1)
            return (0);
    return (1);
}
//ecriture d'un char
int     do_char(char c, int fd)
{
    char    a;

    a = 'c';
    if (write(fd, &a, 1) == -1)
        return (0);
    if (write(fd, &c, 1) == -1)
        return (0);
    return (1);
}
//ecriture d'un float
/*int     do_float(float f, int fd)
{
    char    c;
    int     a;
    float   b;

    c = 'f';
    if (write(fd, &c, 1) == -1)
        return(0);
    while ()
    {

    }
    return (1);
}*/
//ecriture d'un int
int     do_int(int i, int fd)
{
    char    *c;
    char    b;
    int     r;

    b = 'i';
    if (write(fd, &b, 1) == -1)
        return (0);
    c = ft_itoa(i);
    r = -1;
    while (c[r++])
        if (write(fd, &c[r], 1) == -1)
            return (0);
    return (1);
}
int     creat_fichier(t_map *map, char *name)
{
    int     fd;

    //on créer une map
    if (creat(name, O_CREAT) == -1)
        return (0);
    if ((fd = open(name, O_APPEND)) == -1)
        return (0);
    if (do_map(map, fd) == 0)
        return(0);
	free(name);
    close(fd);
    return(1);
}
