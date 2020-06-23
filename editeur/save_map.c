/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/06/23 15:23:52 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem_edit.h"
#include <sys/stat.h>
//l'idée est de créer la map de tel sorte que l'on ai une lettre suivi d'une info
//a la fin on aura donc une grande ligne avec toutes les infos dont on va avoir besoin pour la map
//il faut donc utiliser creat_fichier avec le t_map que l'on veut créer en .map
//creation du fichier et ouverture
//strcat avec un seul caractère
char    *little_strjoin(char *src, char c)
{
    int     i;
    char	*dest;

    i = ft_strlen(src);
    if (!((dest) = (char *)malloc(sizeof(char) * i + 1)))
	    return (0);
    dest[i + 1] = 0;
    i = -1;
    while (src[++i])
        dest[i] = src[i];
    dest[i] = c;
    if (src)
	ft_strdel(&src);
    return (dest);
}
//écriture de la map
int     do_map(t_map *map, int fd)
{
    char    c;

    c = 'm';
    if (write(fd, &c, 1) == -1)
        return (0);
    if (do_box(map->box, fd) == 0)
        return (0);
    if (map->sectors)
        if (do_sectors(map->sectors, fd) == 0)
         return (0);
    if (do_int(map->size, fd) == 0)
        return (0);
    if (do_point(map->spawn, fd) == 0)
        return(0);
    if (map->items)
		if (do_item(map->items, fd) == 0)
			return (0);
	if (map->props)
		if (do_prop(map->props, fd) == 0)
			return (0);
	if (map->enemys)
		if (do_enemy(map->enemys, fd) == 0)
			return (0);
    return (1);
}

int	do_enemy(t_enemy *enemy, int fd)
{
    char	c;

    c = 'y';
    if (write(fd, &c, 1) == -1)
		return (0);
	if (enemy->name)
		if (do_x_char(enemy->name, fd) == 0)
			return (0);
    if (do_int(enemy->x, fd) == 0)
		return (0);
    if (do_int(enemy->y, fd) == 0)
		return (0);
    if (enemy->next_enemy)
		do_enemy(enemy->next_enemy, fd);
    return (1);
}

int	do_item(t_item *tem, int fd)
{
    char	c;

    c = 't';
    if (write(fd, &c, 1) == -1)
		return (0);
	if (tem->name)
		if (do_x_char(tem->name, fd) == 0)
			return (0);
    if (do_int(tem->x, fd) == 0)
		return (0);
    if (do_int(tem->y, fd) == 0)
		return (0);
    if (tem->next_item)
		do_item(tem->next_item, fd);
    return (1);
}

int     do_prop(t_prop *prop, int fd)
{
    char        c;

    c = 'p';
    if (write(fd, &c, 1) == -1)
        return (0);
	if (prop->name)
		if (do_x_char(prop->name, fd) == 0)
			return (0);
    if (do_int(prop->x, fd) == 0)
        return (0);
    if (do_int(prop->y, fd) == 0)
        return (0);
    if (prop->next_prop)
        do_prop(prop->next_prop, fd);
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
        if (do_wall(box.walls[x], fd) == 0)
            return (0);
    if (do_int(box.nbr_walls, fd) == 0)
        return (0);
    if (do_int(box.size, fd) == 0)
        return (0);
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
    if (do_int(sectors->nbr_walls, fd) == 0)
        return (0);
    if (do_x_wall(sectors->walls, fd, sectors->nbr_walls) == 0)
        return (0);
    if (do_wall(sectors->floor, fd) == 0 || do_wall(sectors->celling, fd) == 0)
        return (0);
    if (do_int(sectors->light, fd) == 0 || do_int(sectors->sector_id, fd) == 0)
        return (0);
    if (sectors->next_sector)
        if (do_sectors(sectors->next_sector, fd) == 0)
            return (0);
    return (1);
}
//ecriture de plusieurs structure wall
int     do_x_wall(t_wall *wall, int fd, int g)
{
    char    c;
    int     x;

    c = 'x';
    if (write(fd, &c, 1) == -1)
	return (0);
    x = -1;
    while (++x < g)
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
    if (do_point(wall.a, fd) == 0 || do_point(wall.b, fd) == 0
            || do_point(wall.c, fd) == 0 || do_point(wall.d, fd) == 0)
        return (0);
    if (do_int(wall.text_id, fd) == 0 || do_int(wall.wall_id, fd) == 0
    	|| do_int(wall.is_portal, fd) == 0 || do_int(wall.is_transparent, fd) == 0
        || do_int(wall.is_textured, fd) == 0 || do_int(wall.fill_up, fd) == 0
     	|| do_int(wall.fill_down, fd) == 0 || do_int(wall.sector_id, fd) == 0
	|| do_int(wall.sector_id_it_leads_to, fd) == 0)
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
#include <stdio.h>
//ecriture d'un int
int     do_int(int i, int fd)
{
    char    *c;
    char    b;
    int     r;

    b = 'i';
    if (write(fd, &b, 1) == -1)
        return (0);
    if (i < 0)
    {
	if (write(fd, "0", 1) == -1)
	    return (0);
    }
    else
    {
	c = ft_itoa(i);
    	r = -1;
    	while (c[++r])
       	    if (write(fd, &c[r], 1) == -1)
            	return (0);
    }
    return (1);
}
//permet de creer le fichier
int     creat_fichier(t_map *map, char *name)
{
    int     fd;
	char	*namefinal;
	char	*namefinalfinal;
	char	*path;

    //on créer une map
	path = "../maps/";
	namefinal = ft_strjoin(name, ".map");
	namefinalfinal = ft_strjoin(path, namefinal);
    if ((fd = creat(namefinalfinal, O_CREAT | O_RDWR)) == -1)
	return (0);
    close(fd);
    if (chmod(namefinalfinal, S_IRWXU) < 0)
	return (0);
    if ((fd = open(namefinalfinal, O_APPEND | O_RDWR)) == -1)
        return (0);
    if (do_map(map, fd) == 0)
        return (0);
    close(fd);
	free(namefinalfinal);
	free(namefinal);
	free(name);
    return (1);
}
