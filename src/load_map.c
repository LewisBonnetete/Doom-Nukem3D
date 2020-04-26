//récupération des info de la map
#include "editeur/doom-nukem_edit.h"
//maintenant nous avons une grande ligne avec toutes les infos, il ne faut plus que les récupérer avec des forets de if
//on donc besoin de l'endroit ou se trouve la map (str) et de la map a remplir (t_map) et de lancer info_map
//si la fonction retourne 1 tout s'est bien passé, sinon elle retourne 0,n il y a donc une erreur dans la map envoyé en argument
//je precise que tout est a testé, et rien n'est a la norme.
//recupère les infos du .map avec recup_map puis remplit le t_map avec rec_map
int     info_map(char *str, t_map *map)
{
    char	*the_map;
    int     i;

    i = -1;
    if ((the_map = recup_map(str)) == 0)
        return (0);
    while (the_map[++i])
    {
        if (the_map[i] == 'm')
	{
	    if (rec_map(++i, the_map, map) == 0)
                return (0);
	}
	else
            return (0);
    }
    ft_strdel((char **)the_map);
    return (1);
}
//recupere une structure t_map
int     rec_map(int i, char *the_map, t_map *map)
{
    if (!((map) = (t_map *)malloc(sizeof(t_map))))
        return (0);
    if (the_map[i] == 'b')
        if (rec_box(++i, the_map, map->box) == 0)
            return (0);
    if (the_map[i] == 's')
        if (rec_sectors(++i, the_map, map->sectors)== 0)
            return (0);
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, map->size) == 0)
            return (0);
    if (the_map[i] == 'p')
        if (rec_point(++i, the_map, map->spawn) == 0)
            return (0);
    return (1);
}
//recupere une structure t_box
int     rec_box(int i, char *the_map, t_box box)
{
    int     x;

    x = -1;
    while (++x < 5)
        if (the_map[i] == 'w')
            if (rec_wall(++i, the_map, box.walls[x]) == 0)
                return (0);
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, box.nbr_walls) == 0)
            return (0);
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, box.size) == 0)
            return (0);
    if (the_map[i] == 'w')
        if (rec_wall(++i, the_map, box.floor) == 0)
            return (0);
    if (the_map[i] == 'w')
        if (rec_wall(++i, the_map, box.celling) == 0)
            return (0);        
    return (1);
}
//recupere une structure t_sector
int     rec_sectors(int i, char *the_map, t_sector *sectors)
{
    if (!((sectors) = (t_sector *)malloc(sizeof(t_sector))))
        return (0);
    if (the_map[i] == 'x')
        if (rec_x_wall(++i, the_map, sectors->walls) == 0)
            return (0);
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, sectors->nbr_walls) == 0)
            return (0);
    if (the_map[i] == 'w')
        if (rec_wall(++i, the_map, sectors->floor) == 0)
            return (0);
    if (the_map[i] == 'w')
        if (rec_wall(++i, the_map, sectors->celling) == 0)
            return (0);
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, sectors->light) == 0)
            return (0);
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, sectors->sector_id) == 0)
            return (0);
    if (the_map[i] == 's')
    {
	    if (rec_sectors(++i, the_map, sectors->next_sector) == 0)
            return (0);
    }
    else
        sectors->next_sector = NULL;
    if (the_map[i] == 'm')
        if (rec_map(++i, the_map, sectors->map) == 0)
            return (0);
    if (the_map[i] == 'v')
        if (rec_var(++i, the_map, sectors->info) == 0)
            return (0);
    return (1);
}
//recupere une structure t_wall *walls
int     rec_x_wall(int i, char *the_map, t_wall *wall)
{
    if (!(wall = (t_wall *)malloc(sizeof(t_wall))) == 0)
        return (0);
    if (rec_wall(++i, the_map, wall) == 0)
        return (0);
    if (the_map[i] == 'w')
	if (rec_x_wall(++i, the_map, wall + 1) == 0)
            return (0);
    return (1);
}
//recupere une structure t_point
int     rec_point(int i, char *the_map, t_point point)
{
    if (the_map[i] == 'p')
        if (rec_int(++i, the_map, point.x) == 0)
            return (0);
    if (the_map[i] == 'p')
        if (rec_int(++i, the_map, point.y) == 0)
            return (0);
    if (the_map[i] == 'p')
        if (rec_int(++i, the_map, point.z) == 0)
            return (0);
    return (1);
}
//recupere une structure t_wall
int     rec_wall(int i, char *the_map, t_wall wall)
{
    if (rec_wall_point(i, the_map, wall) == 0)
        return (0);
    if (rec_wall_int(i, the_map, wall) == 0)
        return (0);
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, wall.sector_id_it_leads_to) == 0)
            return (0); 
    return (1);
}
//recupere les int de la structure t_wall
int     rec_wall_int(int i, char *the_map, t_wall wall)
{
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, wall.text_id) == 0)
            return(0);
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, wall.is_portal) == 0)
            return(0);
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, wall.is_transparent) == 0)
            return(0);
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, wall.is_textured) == 0)
            return(0);
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, wall.fill_up) == 0)
            return(0);
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, wall.fill_down) == 0)
            return(0);
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, wall.sector_id) == 0)
            return(0);
    return (1);
}
//recupere les points d'une structure t_wall
int     rec_wall_point(int i, char *the_map, t_wall wall)
{
    if (the_map[i] == 'd')
        if (rec_point(++i, the_map, wall.a) == 0)
            return (0);
    if (the_map[i] == 'd')
        if (rec_point(++i, the_map, wall.b) == 0)
            return (0);
    if (the_map[i] == 'd')
        if (rec_point(++i, the_map, wall.c) == 0)
            return (0);
    if (the_map[i] == 'd')
        if (rec_point(++i, the_map, wall.d) == 0)
            return (0);
    return (1);
}
//recupere un structure t_input_edit
int     rec_input(int i, char *the_map, t_input_edit *in)
{
    if (!(in = (t_input_edit *)malloc(sizeof(t_input_edit))) == 0)
	return (0);
    if (the_map[i] == 'd')
        if (rec_double(++i, the_map, in->mouse_x) == 0)
            return (0);
    if (the_map[i] == 'd')
        if (rec_double(++i, the_map, in->mouse_y) == 0)
            return (0);
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, in->right_click) == 0)
            return (0);
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, in->left_click) == 0)
            return (0);
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, in->del) == 0)
            return (0);
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, in->t_s) == 0)
            return (0);
    if (rec_input_int(i, the_map, in) == 0)
        return (0);
    return (1);
}
//recupere les int d'une structure t_input_edit
int     rec_input_int(int i, char *the_map, t_input_edit *in)
{
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, in->t_n) == 0)
            return (0);
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, in->t_0) == 0)
            return (0);
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, in->t_1) == 0)
            return (0);
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, in->t_2) == 0)
            return (0);
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, in->t_3) == 0)
            return (0);
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, in->t_4) == 0)
            return (0);
    if (rec_input_int_2(i, the_map, in) == 0)
        return (0);
    return (1);
}

int     rec_input_int_2(int i, char *the_map, t_input_edit *in)
{
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, in->t_5) == 0)
            return (0);
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, in->t_6) == 0)
            return (0);
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, in->t_7) == 0)
            return (0);
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, in->t_8) == 0)
            return (0);
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, in->t_9) == 0)
            return (0);
    return (1);
}
//recupere une structure t_var
int     rec_var(int i, char *the_map, t_var *v)
{
    int     x;

    x = -1;
    if (!(v = (t_var *)malloc(sizeof(t_var))) == 0)
	return (0);
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, v->weapon_cap) == 0)
            return (0);
    if (rec_var_int(i, the_map, v) == 0)
        return (0);
    while (the_map[i] == 'e')
    {
        if (rec_x_char(++i, the_map, v->map[++x]) == 0)
            return (0);
        v->map[x + 1] = 0;
    }
    if (rec_var_double(i, the_map, v) == 0)
        return (0);
    if (the_map[i] == 't')
        if (rec_input(++i, the_map, v->input_edit) == 0)
            return (0);
    return (1);
}
// recupere les it d'une structure t_var
int     rec_var_int(int i, char *the_map, t_var *v)
{
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, v->texture_cap) == 0)
            return (0);
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, v->mouse_in) == 0)
            return (0);
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, v->p_x) == 0)
            return (0);
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, v->p_y) == 0)
            return (0);
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, v->sprint) == 0)
            return (0);
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, v->x_dec) == 0)
            return (0);
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, v->y_dec) == 0)
            return (0);;
    return (1);
}
// recupere les double d'une structure t_var
int     rec_var_double(int i, char *the_map, t_var *v)
{
    if (the_map[i] == 'd')
        if (rec_double(++i, the_map, v->posx) == 0)
            return (0);
    if (the_map[i] == 'd')
        if (rec_double(++i, the_map, v->posy) == 0)
            return (0);
    if (the_map[i] == 'd')
        if (rec_double(++i, the_map, v->ori_x) == 0)
            return (0);
    if (the_map[i] == 'd')
        if (rec_double(++i, the_map, v->ori_y) == 0)
            return (0);
    if (the_map[i] == 'd')
        if (rec_double(++i, the_map, v->dirx) == 0)
            return (0);
    if (the_map[i] == 'd')
        if (rec_double(++i, the_map, v->diry) == 0)
            return (0);
    if (the_map[i] == 'd')
        if (rec_double(++i, the_map, v->planex) == 0)
            return (0);
    if (the_map[i] == 'd')
        if (rec_double(++i, the_map, v->planey) == 0)
            return (0);
    if (rec_var_double_2(i, the_map, v) == 0)
        return (0);
    return (1);
}

int     rec_var_double_2(int i, char *the_map, t_var *v)
{
    if (the_map[i] == 'd')
        if (rec_double(++i, the_map, v->time) == 0)
            return (0);
    if (the_map[i] == 'd')
        if (rec_double(++i, the_map, v->oldtime) == 0)
            return (0);
    if (the_map[i] == 'd')
        if (rec_double(++i, the_map, v->time_reset) == 0)
            return (0);
    if (the_map[i] == 'd')
        if (rec_double(++i, the_map, v->movespeed) == 0)
            return (0);
    if (the_map[i] == 'd')
        if (rec_double(++i, the_map, v->rotspeed) == 0)
            return (0);
    if (the_map[i] == 'd')
        if (rec_double(++i, the_map, v->olddirx) == 0)
            return (0);
    if (the_map[i] == 'd')
        if (rec_double(++i, the_map, v->oldplanex) == 0)
            return (0);
    if (the_map[i] == 'd')
        if (rec_double(++i, the_map, v->frametime) == 0)
            return (0);
    return (1);
}
// recupere un double
int     rec_double(int i, char *the_map, double d)
{
    double  a;
    double  b;

    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, (int)b) == 0)
            return (0);
    if (the_map[i] == 'i')
        if (rec_int(++i, the_map, (int)a) == 0)
            return (0);
    b = b / 10;
    if ((d = a + b) == -1)
	return (0);
    return (1);
}
//recupere une chaine de caractere
int     rec_x_char(int i, char *the_map, char *src)
{
    char    a;

    if (the_map[i] == 'c')
    {
        if (src)
        {
            if (rec_char(++i, the_map, a) == 0)
                return (0);
            src = little_strcat(src, a);
        }
        else
        {
            if (!(src = (char *)malloc(sizeof(char) + 2)))
                return (0);
            if (rec_char(++i, the_map, src[0]))
                return (0);
            src[1] = 0;
        }
    }
    if (the_map[i] == 'c')
        if (rec_x_char(i, the_map, src) == 0)
		return (0);
    return (1);
}
//recupere un int
int     rec_int(int i, char *the_map, int dest)
{
    char    *str;
    int     j;
    int     tmp;
    size_t  len;

    tmp = i;
    while (the_map[i] >= '0' && the_map[i] <= '9')
        ++i;
    len = i - tmp;
    if ((str = ft_strnew(len)) == 0)
        return (0);
    i = tmp;
    j = -1;
    while (the_map[i] >= '0' && the_map[i] <= '9')
        str[++j] = the_map[i++];
    str[j + 1] = 0;
    if ((dest = ft_atoi(str)) == -1)
	return (0);
    return (1);
}
//recupere un char
int     rec_char(int i, char *the_map, char dest)
{
    if ((dest == the_map[i++]) == 0)
        return (0);
    return (1);
}
//récuprération de la map avec gnl
char    *recup_map(char *src)
{
    char    *line;
    int     fd;
    int     error;
    char    *map;

    if ((fd = open(src, O_RDONLY)) == -1)
        return (0);
    while ((error = get_next_line(fd, &line)) > 0)
    {
        if (ft_cpy_map(line, map) == 0)
        {
            ft_strdel(&line);
            close(fd);
            return (0);
        }
        ft_strdel(&line);
    }
    close(fd);
    return (map);
}
//fonction qui fait un strcat, meme si la ligne n'existe pas
int     ft_cpy_map(char *line, char *map)
{
    if (!map)
        (map = ft_strdup(line));
    else
        (map = ft_strcat(map, line));
    if (!map)
        return (0);
    return (1);
}
