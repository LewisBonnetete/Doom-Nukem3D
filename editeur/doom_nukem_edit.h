/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem_edit.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 14:27:51 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/27 13:40:40 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_EDIT_H
# define DOOM_NUKEM_EDIT_H

# include <SDL.h>
# include <SDL_image.h>
# include <SDL_ttf.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"
# define WINDOW_W			1280
# define WINDOW_H			720
# define BLACK				0x23272a
# define WHITE				0xFFFFFF
# define BLUE				0x7289DA
# define ORANGE				0xFFA500
# define RED				0xFF0000
# define DARK				0x2C2F33
# define GRAY				0x99AAB5
# define GREEN				0x32cd32
# define RMASK				0
# define GMASK				0
# define BMASK				0
# define AMASK				0
# define NAME_DEC			2

typedef	struct s_var		t_var;
typedef	struct s_text		t_text;
typedef	struct s_point		t_point;
typedef	struct s_wall		t_wall;
typedef	struct s_wall		t_portal;
typedef	struct s_sector		t_sector;
typedef	struct s_box		t_box;
typedef	struct s_map		t_map;
typedef	struct s_enemy		t_enemy;
typedef	struct s_prop		t_prop;
typedef	struct s_line		t_line;
typedef	struct s_item		t_item;
typedef struct s_convex		t_convex;
typedef struct s_intersec	t_intersec;
typedef struct s_norm1		t_norm1;
typedef struct s_gws		t_gws;

struct						s_gws
{
	t_map					*map;
	t_sector				*sector;
	int						*height;
	SDL_Event				*event;
	int						i;
};

struct						s_point
{
	int						x;
	int						y;
	int						z;
};

struct						s_norm1
{
	t_item					*item;
	t_prop					*prop;
	t_enemy					*enemy;
};

struct						s_convex
{
	int						a;
	int						b;
	int						c;
	int						got_positive;
	int						got_negative;
};

struct						s_intersec
{
	float					a1;
	float					a2;
	float					b1;
	float					b2;
	float					x;
	float					y;
};

struct						s_item
{
	char					*name;
	int						x;
	int						y;
	t_item					*next_item;
};

struct						s_prop
{
	char					*name;
	int						x;
	int						y;
	t_prop					*next_prop;
};

struct						s_enemy
{
	char					*name;
	int						x;
	int						y;
	t_enemy					*next_enemy;
};

struct						s_wall
{
	t_point					a;
	t_point					b;
	t_point					c;
	t_point					d;
	int						text_id;
	int						wall_id;
	int						is_portal;
	int						is_transparent;
	int						is_textured;
	int						fill_up;
	int						fill_down;
	int						sector_id;
	int						sector_id_it_leads_to;
};

struct						s_sector
{
	t_wall					*walls;
	int						nbr_walls;
	t_wall					floor;
	t_wall					celling;
	double					light;
	int						sector_id;
	t_sector				*next_sector;
	t_map					*map;
	t_var					*info;
};

struct						s_box
{
	t_wall					walls[4];
	int						nbr_walls;
	int						size;
	t_wall					floor;
	t_wall					celling;
};

struct						s_map
{
	t_box					box;
	t_sector				*sectors;
	int						size;
	SDL_Surface				*text_tab[10];
	t_point					spawn;
	int						spawn_sector_id;
	t_point					end;
	int						i;
	t_item					*items;
	t_prop					*props;
	t_enemy					*enemys;
	int						cid;
	int						fid;
};

struct						s_text
{
	int						tex_id;
	double					wall_x;
	double					tex_x;
	double					tex_y;
	int						texwidth;
	int						texheight;
	Uint32					color;
};

struct						s_var
{
	SDL_Window				*window;
	SDL_Event				*event;
	SDL_Renderer			*renderer;
	SDL_Surface				*image;
	SDL_Texture				*texture;
	TTF_Font				*font;
	int						weapon_cap;
	int						texture_cap;
	int						mouse_in;
	int						p_x;
	int						p_y;
	float					pf_x;
	float					pf_y;
	float					c_angl;
	char					**map;
	double					posx;
	double					posy;
	double					ori_x;
	double					ori_y;
	double					dirx;
	double					diry;
	double					planex;
	double					planey;
	double					time;
	double					oldtime;
	double					time_reset;
	double					movespeed;
	double					rotspeed;
	double					olddirx;
	double					oldplanex;
	double					frametime;
	int						sprint;
	int						x_dec;
	int						y_dec;
};

struct						s_line
{
	int						x1;
	int						y1;
	int						x2;
	int						y2;
	int						dx;
	int						sx;
	int						dy;
	int						sy;
	int						err;
	int						e2;
};

int							init_win1(t_var *info);
int							init_win2(t_var *info);
int							init_win3(t_var *info);
float						cross_product(t_point a, t_point b, t_point c);
int							is_both_inferior_x(t_point a, t_point b,
								t_point c, t_point d);
int							is_both_superior_x(t_point a, t_point b,
								t_point c, t_point d);
int							is_both_inferior_y(t_point a, t_point b,
								t_point c, t_point d);
int							is_both_superior_y(t_point a, t_point b,
								t_point c, t_point d);
int							editer(t_var *info, t_map *map);
int							validate(t_map *map);
int							set_spawn(t_map *map);
int							portals(t_map *map);
int							get_map_size();
char						*get_item_name();
int							valid_new_item(t_map *map, int x, int y);
t_item						*go_to_last_item(t_item *items);
int							add_item(t_map *map, char *name, int x, int y);
int							del_item(t_map *map, int x, int y);
int							item_checks(t_point new, t_map *map);
int							prop_checks(t_point new, t_map *map);
int							valid_new_prop(t_map *map, int x, int y);
void						create_item(t_map *map);
void						create_prop(t_map *map);
int							add_prop(t_map *map, char *name, int x, int y);
int							del_item(t_map *map, int x, int y);
int							del_prop(t_map *map, int x, int y);
void						del_item_or_prop(t_map *map);
char						*get_prop_name();
void						create_enemy(t_map *map);
char						*get_enemy_name();
int							valid_new_enemy(t_map *map, int x, int y);
int							enemy_checks(t_point new, t_map *map);
t_enemy						*go_to_last_enemy(t_enemy *enemys);
int							add_enemy(t_map *map, char *name, int x, int y);
int							del_enemy(t_map *map, int x, int y);
int							is_valid_wall(SDL_Event *event,
								t_sector *sector, int i);
int							is_valid_first_wall(SDL_Event *event, t_map *map);
int							is_valid_last_wall(SDL_Event *event,
								t_sector *sector, int i);
int							check_wall_intersections(t_point new,
								t_point old, t_wall wall);
int							check_convexity(t_sector *sector);
int							check_self_intersection(t_sector *sector);
int							is_in_sectors(t_point first, t_map *map);
int							is_in_sectors_spawn(t_point first, t_map *map);
int							is_in_sectors_float(float center_x,
								float center_y, t_map *map);
int							is_new_point_in_sector(t_point new, t_wall *walls);
int							is_same_point(t_point a, t_point b);
int							check_surrounding(t_sector *sector);
int							is_in_sector(t_point first, t_sector *sector);
int							is_new_point_in_sectors(t_point new, t_map *map);
int							is_new_point_in_sector(t_point new, t_wall *walls);
int							center_in_poly(t_point a, t_point b,
								t_sector *sector);
int							verify_crossing(t_point new, t_point old,
								t_sector *sector);
int							comparator1(t_point new, t_point old,
								t_point w1, t_point w2);
int							comparator2(t_point new, t_point old,
								t_point w1, t_point w2);
void						init_box(t_map *map);
void						init_map(t_map *map);
void						init_var(t_var *info);
void						init_walls(t_wall *walls, int nbr_walls);
void						init_sector(t_sector *sector);
void						init_wall(t_wall *wall);
void						draw_interactions_edit(t_var *info, t_map *map);
int							draw_state(t_sector *sector);
void						draw_wall_edit(t_var *info, t_map *map,
								t_sector *sector, int wall_id);
void						draw_portal_edit(t_var *info, t_map *map,
								t_sector *sector, int wall_id);
void						draw_sector_wall_edit(t_var *info,
								t_map *map, t_sector *sector);
void						draw_sector_portal_edit(t_var *info,
								t_map *map, t_sector *sector);
void						draw_sectors_edit(t_var *info, t_map *map);
void						draw_grid(t_var *info, t_map *map);
void						draw_map_edit(t_var *info, t_map *map);
void						draw_cadre(t_var *info);
void						draw_square(t_var *info, t_point a,
								t_point b, Uint32 color);
void						draw_items(t_var *info, t_map *map);
void						draw_props(t_var *info, t_map *map);
void						draw_enemys(t_var *info, t_map *map);
void						put_pixel_to_suface(Uint32 color, int x,
								int y, SDL_Surface *image);
int							draw_line(t_var *info, t_line *line, Uint32 color);
int							create_sector(t_var *info, t_map *map);
int							get_walls_sector(t_map *map,
								t_sector *sector, int *height);
void						get_textures(t_wall *wall);
void						get_portal_info(t_wall *wall);
void						get_nbr_walls_sector_textures(t_sector *sector);
void						get_height_sector(int *height);
void						wall_fusion(t_sector *sector, int i);
int							create_sector(t_var *info, t_map *map);
void						close_sector(t_sector *sector, int i);
int							create_wall_edit(t_sector *sector, int *height,
								int i, SDL_Event event);
int							create_first_wall_edit(t_sector *sector,
								int *height, int i, SDL_Event event);
int							set_end(t_map *map);
int							exit_edit(t_var *info, t_map *map);
t_sector					*get_to_last_sector(t_sector *sector);
int							nbr_of_sectors(t_map *map);
t_sector					*get_a_sector_by_id(t_map *map, int id);
void						del_sector(t_var *info, t_map *map);
int							is_between(float x, float a, float b);
int							x_coo(SDL_Event *event, t_map *map);
int							y_coo(SDL_Event *event, t_map *map);
int							is_in_object(t_point new, t_map *map);
int							creat_fichier(t_map *map, char *name);
int							do_int(int i, int fd);
int							do_char(char c, int fd);
int							do_x_char(char *str, int fd);
int							do_double(double d, int fd);
int							do_var(t_var *v, int fd);
int							do_wall(t_wall wall, int fd);
int							do_point(t_point point, int fd);
int							do_x_wall(t_wall *wall, int fd, int g);
int							do_sectors(t_sector *sectors, int fd);
int							do_box(t_box box, int fd);
int							do_map(t_map *map, int fd);
int							do_item(t_item *tem, int fd);
int							do_prop(t_prop *prop, int fd);
int							do_enemy(t_enemy *enemy, int fd);
char						*little_strjoin(char *src, char c);
void						hud(t_var *info);
int							is_in_sector_spawn(t_point first,
								t_sector *sector);
void						get_map_textures(t_map *map);
int							dealers_edit(t_var *info, t_map *map);
void						del_items_if_in_sector(t_item *items,
								t_sector *sector);
int							is_same_wall(t_wall *w1, t_wall *w2);
#endif
