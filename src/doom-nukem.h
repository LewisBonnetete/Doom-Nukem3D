/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom-nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewis <lewis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 14:27:51 by lbonnete          #+#    #+#             */
/*   Updated: 2020/06/03 16:19:16 by lewis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include <SDL.h>
# include <SDL_image.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# define WINDOW_W			1280
# define WINDOW_H			720
# define NB_THREADS_MAX		12
# define RMASK				0
# define GMASK				0
# define BMASK				0
# define AMASK				0
# define WALL_H				350
# define DECALLAGE			0
# define BLACK				0x000000
# define SKY_BLUE			0x00BFFF
# define GRASS_GREEN		0x1FBC3F
# define SOUTH_WALL			0xd2b48c
# define NORTH_WALL			0xD28F8F
# define EAST_WALL			0xDAA520
# define WEST_WALL			0xF4A460
# define TEXTURE_1			"./xpm_textures/brick.xpm"
# define TEXTURE_2			"./xpm_textures/redbrick.xpm"
# define TEXTURE_3			"./xpm_textures/purplestone.xpm"
//# define TEXTURE_4			"./xpm_textures/wood.xpm"
# define NB_TEXT			4

typedef struct s_input		t_input;
typedef	struct s_var		t_var;
typedef	struct s_text		t_text;
typedef	struct s_point		t_point;
typedef	struct s_wall		t_wall;
typedef	struct s_wall		t_portal;
typedef struct s_ray		t_ray;
typedef	struct s_sector		t_sector;
typedef	struct s_box		t_box;
typedef	struct s_map		t_map;
typedef	struct s_enemy		t_enemy;
typedef	struct s_prop		t_prop;
typedef struct s_render		t_render;
typedef struct s_player		t_player;
typedef struct s_item		t_item;
typedef struct s_itab		t_itab;

struct					s_item
{
	char			*name;
	int				x;
	int				y;
	t_item			*next_item;
};

struct					s_point
{
	float				x;
	float				y;
	float				z;
};

struct					s_prop
{
	char			*name;
	int				x;
	int				y;
	t_prop			*next_prop;
};

struct 					s_wall
{
	t_point				a;
	t_point				b;
	t_point				c;
	t_point				d;
	double				wall_leng;
	int					text_id;
	int					wall_id;
	int					is_portal;
	int					is_transparent;
	int					is_textured;
	int					fill_up;
	int					fill_down;
	int					sector_id;
	double				height;
	double				eq_slope;
	double				eq_cste;
	int					sector_id_it_leads_to;
};

struct 					s_sector
{
	t_wall				*walls;
	int 				nbr_walls;
	t_wall				floor;
	t_wall				celling;
	int					light;
	int					sector_id;
	t_sector			*next_sector;
	t_map				*map;
	t_var				*info;
};

struct 					s_box
{
	t_wall				walls[4];
	int 				nbr_walls;
	int					size;
	t_wall				floor;
	t_wall				celling;
};

struct 					s_map
{
	t_box				box;
	t_sector			*sectors;
	int					size;
	SDL_Surface			*text_tab[10];
	t_point				spawn;
	int					i;
	t_item				*items;
	t_prop				*prop;
};

struct					s_text
{
	int					tex_id;
	double				wall_x;
	double				tex_x;
	double				tex_y;
	int					texwidth;
	int					texheight;
	Uint32				color;
};

	/*
	wall_sqdist : calcul pour la colonne render->x le carré de la distance du mur au joueur
		ps : on utilise le carré pour ne pas utiliser la fonction sqrt,
			on a juste beosin d'avoir un ordre de grandeuur euclidien ?
	wall_y1 coordonnée du pixel en haut du mur
	wall_y0 coordonnée du pixel en bas du mur
	*/
struct					s_render
{
	int					x;
	int					n;
	int 				x1;
	int					next_x;
	int					sector_id;
	double				wall_sqdist;
	double				wall_height;
	double				wall_dist;
	int					wall_y0;
	int					wall_y1;
	int					nb_sec;
	t_sector			*sec_0;
	SDL_Surface			*tab_sdl[NB_TEXT + 1];
	t_ray				*ray;
	t_sector			*s;
	t_wall				*wall;
	t_render			*next_render;
};

struct					s_player
{
	int					fov;
	int					sector_id;
	double				posx;
	double				posy;
	double				posz; // utile??
	double				dx;
	double				dy;
	double				dz;
	double				planex;
	double				planey;
	double				movespeed;
	double				frametime;
	int					hp;
	int					ammo;
	t_item				weapon;
	t_item				*inventory;
};

struct					s_ray
{
	double				cam_x;
	//int					hit_portal; inutile au final ?
	//int					hit_wall; inutile au final ?
	double				x;
	double				y;
	double				z;	//utile ??
	double				x2;
	double				y2;
	double				z2;
	double				dx;
	double				dy;
	double				dz;	// utile??
	double				eq_slope;
	double				eq_cste;
};

struct					s_var
{
	SDL_Window			*window;
	SDL_Event			*event;
	SDL_Renderer		*renderer;
	SDL_Surface			*image;
	SDL_Texture			*texture;
	t_player			*player;
	t_map				*map;
	double				olddirx;
	double				oldplanex;
	double				rotspeed;
	double				frametime;
};

struct 					s_itab
{
	float				dist;
	char				*name;
};


struct					s_input
{
	int					up;
	int					down;
	int 				shoot;
	int					straf_left;
	int					straf_right;
	int					rot_left;
	int					rot_right;
	double				straffer_x;
	double				straffer_y;
	double				diag_x;
	double				diag_y;
	int					diag;
};

//sdl func
int						init_win1(t_var *info);
int						init_win2(t_var *info);
int     				dealer(t_var *info, t_render *render);

//init func
void					init_player(t_player *player, t_map *map);
void					ft_init_pour_linstant(t_var *info);
void					init_render(t_var *info, t_render *render, int x0, int sector_id);
int						init_next_render(t_var *info, t_render *render);

//draw
void	draw_bottop(t_var *info, t_render *render);
void	draw_tex(t_var *info, t_render *render);
void	draw_textures(t_var *info, t_render *render);
void	draw_texture_wall(t_var *info, t_render *render);
Uint32			get_pixel(SDL_Surface *tex, int x, int y);
int		intersect(t_ray *ray, t_wall *wall);

//algo
int     raycasting(t_var *info, t_render *render);
void	put_pixel_to_suface(Uint32 color, int x, int y, SDL_Surface *image);
int		xy_in_ab(double x, double y, t_point a, t_point b);

//load_map
int	check_map(char *the_map);
int	info_map(char *str, t_map *map);
int     rec_map(char *the_map, t_map *map);
t_box	rec_box(char *the_map, t_map *map);
t_sector	*rec_sectors(char *the_map, t_map *map);
void	rec_sectors_int(char *the_map, t_sector *sectors, t_map *map);
t_point	rec_point(char *the_map, t_map *map);
t_wall	rec_wall(char *the_map, t_map *map);
double	rec_double(char *the_map, t_map *map);
char	*rec_x_char(char *the_map, t_map *map);
int     rec_int(char *the_map, t_map *map);
void	rec_char(char *the_map, char dest, t_map *map);
char    *recup_map(char *src);
char    *little_strjoin(char *src, char c);
t_item  *rec_item(char *the_map, t_map *map);
t_prop  *rec_prop(char *the_map, t_map *map);

// tools
int			do_trigo(t_var *info, t_wall *wall);
double		calc_dist(t_point a, t_point b);
void		tab_path(t_render *renderer);
void        ft_exit(t_var *info, t_render *render);
void		free_map(t_map *map);
void    	init_tab(int *tab, int n);

//hitbox
int			hitboxy(t_var *info, t_render *render, double diry);
int			hitboxx(t_var *info, t_render *render, double dirx);
//edit tools
int		is_new_point_in_sector(t_point new, t_wall *walls);
int		is_in_sectors_spawn(t_point first,t_map *map);
float	ft_fabs(float a);
//int		draw_line_condition(t_line *line);
//int		draw_line(t_var *info, t_line *line, Uint32 color);
t_sector	*get_to_last_sector(t_sector *sectors);
int			nbr_of_sectors(t_map *map);
t_sector	*get_a_sector_by_id(t_map *map, int id);
float		cross_product(t_point a, t_point b, t_point c);
int		is_between(float x, float a, float b);
int		is_same_point(t_point a, t_point b);
int		is_in_sectors(t_point first,t_map *map);
int		is_in_sector(t_point first,t_sector *sector);
int		check_wall_intersections(t_point new, t_point old, t_wall wall);
int		is_both_superior_y(t_point a, t_point b, t_point c, t_point d);
int		is_both_inferior_y(t_point a, t_point b, t_point c, t_point d);
int		is_both_superior_x(t_point a, t_point b, t_point c, t_point d);
int		is_both_inferior_x(t_point a, t_point b, t_point c, t_point d);
int		is_in_sectors_float(float center_x, float center_y, t_map *map);
int 	pnpoly_float(int nbr_walls, t_wall *walls, float center_x, float center_y);
int		player_sec(t_sector *sector, t_var *info);
void		init_nb_sec(t_sector *sector, t_render *render);

t_render            *cpy_render(t_render *render);

#endif
