//récupération des info de la map
#include "doom-nukem.h"
#include <sys/stat.h>
//maintenant nous avons une grande ligne avec toutes les infos, il ne faut plus que les récupérer avec des forets de if
//on donc besoin de l'endroit ou se trouve la map (str) et de la map a remplir (t_map) et de lancer info_map
//si la fonction retourne 1 tout s'est bien passé, sinon elle retourne 0,n il y a donc une erreur dans la map envoyé en argument
//je precise que tout est a testé, et rien n'est a la norme.
//recupère les infos du .map avec recup_map puis remplit le t_map avec rec_map
int     info_map(char *str, t_map *map)
{
    char	*the_map;

	ft_putendl("Loading map");
    map->i = -1;
    if (!(the_map = recup_map(str)))
        return (0);
    if (the_map[++map->i] == 'm')
    {
    	if (rec_map(the_map, map) == 0)
           return (0);
    }
    else
		return (0);
    ft_strdel(&the_map);
    return (1);
}
//recupere une structure t_map
int     rec_map(char *the_map, t_map *map)
{
	ft_putendl("map");
    if (the_map[++map->i] == 'b')
       map->box = rec_box(the_map, map);
	printf("%c\n",the_map[map->i+1]);
    if (the_map[++map->i] == 's')
       map->sectors = rec_sectors(the_map, map);
    if (the_map[++map->i] == 'i')
       map->size = rec_int(the_map, map);
    if (the_map[++map->i] == 'p')
       map->spawn = rec_point(the_map, map);
    return (1);
}
//recupere une structure t_box
t_box	rec_box(char *the_map, t_map *map)
{
    int     x;
    t_box   box;

	ft_putendl("box");
    ++map->i;
    x = -1;
    while (++x < 5)
    {
        if (the_map[map->i] == 'w')
           box.walls[x] = rec_wall(the_map, map); 
    	++map->i;
    }
    if (the_map[++map->i] == 'i')
        box.nbr_walls = rec_int(the_map, map);
    if (the_map[++map->i] == 'i')
        box.size = rec_int(the_map, map);
    if (the_map[++map->i] == 'w')
        box.floor = rec_wall(the_map, map);
    if (the_map[++map->i] == 'w')
        box.celling = rec_wall(the_map, map);
    return (box);
}
//recupere une structure t_sector
t_sector	*rec_sectors(char *the_map, t_map *map)
{
    int	g;
    t_sector	*sectors;

	ft_putendl("sect");
    g = -1;
    if (!((sectors) = (t_sector *)malloc(sizeof(t_sector))))
        return (0);
	printf("%p\n",sectors);
    if (the_map[++map->i] == 'i')
        sectors->nbr_walls = rec_int(the_map, map);
    if (!((sectors->walls) = (t_wall *)malloc(sizeof(t_wall)
	* sectors->nbr_walls)))
		return (0);
    if (the_map[++map->i] == 'x')
    	while (++g < sectors->nbr_walls)
			if (the_map[++map->i] == 'w')
	    		sectors->walls[g] = rec_wall(the_map, map);
    if (the_map[++map->i] == 'w')
        sectors->floor = rec_wall(the_map, map);
    if (the_map[++map->i] == 'w')
        sectors->celling = rec_wall(the_map, map);
    rec_sectors_int(the_map, sectors, map);
    if (the_map[++map->i] == 's')
    {
	    sectors->next_sector = rec_sectors(the_map, map);
    }
    else
    {
		--map->i;
        sectors->next_sector = NULL;
    }
    if (the_map[map->i] == 'm')
        sectors->map = map;
    return (sectors);
}
//recupere les int de sectors
void	rec_sectors_int(char *the_map, t_sector *sectors, t_map *map)
{
    if (the_map[++map->i] == 'i')
	sectors->light = rec_int(the_map, map);
    if (the_map[++map->i] == 'i')
        sectors->sector_id = rec_int(the_map, map);
}
//recupere une structure t_point
t_point	rec_point(char *the_map, t_map *map)
{
    t_point	point;

    if (the_map[++map->i] == 'i')
        point.x = rec_int(the_map, map);
    if (the_map[++map->i] == 'i')
        point.y = rec_int(the_map, map);
    if (the_map[++map->i] == 'i')
        point.z = rec_int(the_map, map);
    return (point);
}
//recupere une structure t_wall
t_wall	rec_wall(char *the_map, t_map *map)
{
    t_wall	wall;

    if (the_map[++map->i] == 'p')
        wall.a = rec_point(the_map, map);
    if (the_map[++map->i] == 'p')
        wall.b = rec_point(the_map, map);
    if (the_map[++map->i] == 'p')
        wall.c = rec_point(the_map, map);
    if (the_map[++map->i] == 'p')
        wall.d = rec_point(the_map, map);	
    if (the_map[++map->i] == 'i')
        wall.text_id = rec_int(the_map, map);
    if (the_map[++map->i] == 'i')
        wall.wall_id = rec_int(the_map, map);
    if (the_map[++map->i] == 'i')
        wall.is_portal = rec_int(the_map, map);
    if (the_map[++map->i] == 'i')
        wall.is_transparent = rec_int(the_map, map);
    if (the_map[++map->i] == 'i')
        wall.is_textured = rec_int(the_map, map);
    if (the_map[++map->i] == 'i')
        wall.fill_up = rec_int(the_map, map);
    if (the_map[++map->i] == 'i')
        wall.fill_down = rec_int(the_map, map);
    if (the_map[++map->i] == 'i')
        wall.sector_id = rec_int(the_map, map);
    if (the_map[++map->i] == 'i')
        wall.sector_id_it_leads_to = rec_int(the_map, map);
    return (wall);
}
// recupere un double
double	rec_double(char *the_map, t_map *map)
{
    double  a;
    double  b;
    double  d;

    a = 0;
    b = 0;
    if (the_map[++map->i] == 'i')
        b = rec_int(the_map, map);
    if (the_map[++map->i] == 'i')
        a = rec_int(the_map, map);
    b = b / 10;
    d = a + b;
    return (d);
}
//recupere une chaine de caractere
char	*rec_x_char(char *the_map, t_map *map)
{
    char    a;
    char    *src;

    src = 0;
    a = 0;
    if (the_map[++map->i] == 'c')
    {
	++map->i;
	while ((the_map[map->i] >= 65 && the_map[map->i] <= 90)
		|| (the_map[map->i] >= 97 && the_map[map->i] <= 122))
	{
		if (src)
        	{
            		rec_char(the_map, a, map);
			src = little_strjoin(src, a);
        	}
        	else
        	{
            		if (!(src = (char *)malloc(sizeof(char) + 2)))
                		return (0);
            		rec_char(the_map, src[0], map);
			src[1] = 0;
        	}
	}
    }
    if (the_map[map->i] == 'c')
    {
	++map->i;
        rec_x_char(the_map, map);
    }
    return (src);
}
//recupere un int
int     rec_int(char *the_map, t_map *map)
{
    char    *str;
    int     j;
    int     tmp;
    size_t  len;
    int	    dest;

    ++map->i;
    tmp = map->i;
    while (the_map[map->i] >= '0' && the_map[map->i] <= '9')
        ++map->i;
    len = map->i - tmp;
    str = ft_strnew(len);
    map->i = tmp;
    j = -1;
    while (the_map[map->i] >= '0' && the_map[map->i] <= '9')
        str[++j] = the_map[map->i++];
    str[j + 1] = 0;
    dest = ft_atoi(str);
    --map->i;
    return (dest);
}
//recupere un char
void	rec_char(char *the_map, char dest, t_map *map)
{
    dest = the_map[map->i];
}
//récuprération de la map avec gnl
char    *recup_map(char *src)
{
	char    *line;
    int     fd;
    int     error;
    char    *map;

    map = 0;
    if ((fd = open(src, O_RDONLY)) == -1)
        return (0);
    while ((error = get_next_line(fd, &line)) > 0)
    {
	if (map == 0)
	    map = ft_strdup(line);
	else if (!line)
        {
	    map = ft_strcat(map, line);
	    if (!map)
	    {
		ft_strdel(&line);
            	close(fd);
            	return (0);
	    }
        }
        ft_strdel(&line);
    }
    close(fd);
    return (map);
}
