/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom-nukem_edit.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewis <lewis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 14:27:51 by lbonnete          #+#    #+#             */
/*   Updated: 2020/05/11 13:13:49 by lewis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

//changer gnl pour /dev/zero

# include <SDL.h>
# include <SDL_image.h>
# include <SDL_ttf.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"
# define WINDOW_W			1280
# define WINDOW_H			720
# define NB_THREADS_MAX		12
# define BLACK				0x23272a
# define WHITE				0xFFFFFF
# define BLUE				0x7289DA
# define DARK				0x2C2F33
# define GRAY				0x99AAB5
# define RMASK				0
# define GMASK				0
# define BMASK				0
# define AMASK				0

typedef struct s_input	t_input;
typedef struct s_input_edit	t_input_edit;
typedef	struct s_var	t_var;
typedef	struct s_text	t_text;
typedef	struct s_point	t_point;
typedef	struct s_wall	t_wall;
typedef	struct s_wall	t_portal;
typedef	struct s_sector	t_sector;
typedef	struct s_box	t_box;
typedef	struct s_map	t_map;
typedef	struct s_enemy	t_enemy;
typedef	struct s_prop	t_prop;
typedef	struct s_line	t_line;

struct					s_point
{
	int				x;
	int				y;
	int				z;
};

struct 					s_wall
{
	t_point				a;
	t_point				b;
	t_point				c;
	t_point				d;
	int					text_id;
	int					wall_id;
	int					is_portal;
	int					is_transparent;
	int					is_textured;
	int					fill_up;
	int					fill_down;
	int					sector_id;
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
	int					spawn_sector_id;
	int					i;
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

struct					s_var
{
	SDL_Window			*window;
	SDL_Event			*event;
	SDL_Renderer		*renderer;
	SDL_Surface			*image;
	SDL_Texture			*texture;
	TTF_Font			*font;
	int					weapon_cap;
	int					texture_cap;
	int					mouse_in;
	int					p_x;
	int					p_y;
	float				pf_x;
	float				pf_y;
	float				c_angl;
	char				**map;
	double				posx;
	double				posy;
	double				ori_x;
	double				ori_y;
	double				dirx;
	double				diry;
	double				planex;
	double				planey;
	double				time;
	double				oldtime;
	double				time_reset;
	double				movespeed;
	double				rotspeed;
	double				olddirx;
	double				oldplanex;
	double				frametime;
	int					sprint;
	int					x_dec;
	int					y_dec;
	t_input_edit		*input_edit;
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

struct					s_input_edit
{
	double				mouse_x;
	double				mouse_y;
	int					right_click;
	int					left_click;
	int 				del;
	int					t_s;
	int					t_n;
	int					t_0;
	int					t_1;
	int					t_2;
	int					t_3;
	int					t_4;
	int					t_5;
	int					t_6;
	int					t_7;
	int					t_8;
	int					t_9;
};

struct					s_line
{
	int			x1;
	int			y1;
	int			x2;
	int			y2;
	int			dx;
	int			sx;
	int			dy;
	int			sy;
	int			err;
	int			e2;
};

//sdl func
int						init_win1(t_var *info);
int						init_win2(t_var *info);
int						init_win3(t_var *info);

//calculators
float		cross_product(t_point a, t_point b, t_point c);
int			is_both_inferior_x(t_point a, t_point b, t_point c, t_point d);
int			is_both_superior_x(t_point a, t_point b, t_point c, t_point d);
int			is_both_inferior_y(t_point a, t_point b, t_point c, t_point d);
int			is_both_superior_y(t_point a, t_point b, t_point c, t_point d);

//editer
int		editer(t_var *info, t_map *map);
int		validate(t_map *map);
int		set_spawn(t_map *map);
int 	portals(t_map *map);
int		dealers_edit(t_var *info, t_map *map, t_input_edit *input_edit);
void	dealers_init(t_input_edit *input_edit);
void	dealers_tester(t_input_edit input_edit);
int		get_map_size();

//checkers
int		is_valid_wall(SDL_Event *event, t_sector *sector, int i);
int		is_valid_first_wall(SDL_Event *event,t_map *map);
int		is_valid_last_wall(SDL_Event *event, t_sector *sector, int i);
int		check_wall_intersections(t_point new, t_point old, t_wall wall);
int		check_convexity(t_sector *sector);
int		check_self_intersection(t_sector *sector);
int		is_in_sectors(t_point first,t_map *map);
int		is_in_sectors_spawn(t_point first,t_map *map);
int		is_in_sectors_float(float center_x, float center_y, t_map *map);
int		is_new_point_in_sector(t_point new, t_wall *walls);
int		is_same_point(t_point a, t_point b);

//init func
void	init_box(t_map *map);
void	init_map(t_map *map);
void	init_var(t_var *info);
void	init_walls(t_wall *walls, int nbr_walls);
void	init_sector(t_sector *sector);
void	init_wall(t_wall *wall);

//drawers
void	draw_interactions_edit(t_var *info, t_map *map);
int		draw_state(t_sector *sector);
void	draw_wall_edit(t_var *info, t_map *map, t_sector *sector, int wall_id);
void	draw_portal_edit(t_var *info, t_map *map, t_sector *sector, int wall_id);
void	draw_sector_wall_edit(t_var *info, t_map *map, t_sector *sector);
void	draw_sector_portal_edit(t_var *info, t_map *map, t_sector *sector);
void	draw_sectors_edit(t_var *info, t_map *map);
void	draw_grid(t_var *info, t_map *map);
void	draw_map_edit(t_var *info, t_map *map);
void	draw_cadre(t_var *info);
void	draw_square(t_var *info, t_point a, t_point b, Uint32 color);

void	put_pixel_to_suface(Uint32 color, int x, int y, SDL_Surface *image);
int		draw_line(t_var *info, t_line *line, Uint32 color);

//creators
int		create_sector(t_var *info, t_map *map);

//destroyers
int		exit_edit(t_var *info, t_map *map);

//tools
t_sector	*get_to_last_sector(t_sector *sector);
int			nbr_of_sectors(t_map *map);
t_sector	*get_a_sector_by_id(t_map *map, int id);
void		del_sector(t_var *info, t_map *map);
int			is_between(float x, float a, float b);

//loadmap
int     creat_fichier(t_map *map, char *name);
int     do_int(int i, int fd);
int     do_char(char c, int fd);
int     do_x_char(char *str, int fd);
int     do_double(double d, int fd);
int     do_input(t_input_edit *in, int fd);
int     do_var(t_var *v, int fd);
int     do_wall(t_wall wall, int fd);
int     do_point(t_point point, int fd);
int     do_x_wall(t_wall *wall, int fd, int g);
int     do_sectors(t_sector *sectors, int fd);
int     do_box(t_box box, int fd);
int     do_map(t_map *map, int fd);
char    *little_strcat(char *src, char c);

//Hud
void	hud(t_var *info);

#endif