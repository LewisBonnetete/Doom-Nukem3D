/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 14:27:51 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/28 14:26:53 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include <SDL.h>
# include <SDL_image.h>
# include <SDL_ttf.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# define PARSE				0
# define WINDOW_W			720
# define WINDOW_H			480
# define NB_THREADS_MAX		12
# define RMASK				0
# define GMASK				0
# define BMASK				0
# define AMASK				0
# define RED				0xFF0000
# define DARK				0x2C2F33
# define GRAY				0x99AAB5
# define GREEN				0x32cd32
# define WHITE				0xFFFFFF
# define WALL_H				240
# define DECALLAGE			0
# define BLACK				0x000000
# define SKY_BLUE			0x00BFFF
# define GRASS_GREEN		0x1FBC3F
# define SOUTH_WALL			0xd2b48c
# define NORTH_WALL			0xD28F8F
# define EAST_WALL			0xDAA520
# define WEST_WALL			0xF4A460
# define NB_TEXT_I			8
# define NB_TEXT			4
# define DMG				1

typedef struct s_intersec	t_intersec;
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
typedef struct s_render		t_render;
typedef struct s_player		t_player;
typedef struct s_item		t_item;
typedef struct s_itab		t_itab;
typedef struct s_line		t_line;
typedef struct s_f_tool		t_f_tool;
typedef struct s_rgb		t_rgb;
typedef struct s_w_draw		t_w_draw;
typedef struct s_i_tool		t_i_tool;

struct					s_item
{
	char			*name;
	int				id;
	int				x;
	int				y;
	int				cap;
	int				h;
	int				w;
	int				text_id;
	int				mun;
	int				pv;
	int				hold;
	t_item			*next_item;
};

struct					s_point
{
	float				x;
	float				y;
	float				z;
};

struct					s_i_tool
{
	t_point				p;
	t_point				w;
	float				ty;
	int					y;
	int					i;
	Uint32				color;
	t_item				*weapon;
	int					k;
	int					pls;
};

struct					s_wall
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
	int					n_sec_id;
};

struct					s_sector
{
	t_wall				*walls;
	int					nbr_walls;
	t_item				*item;
	int					nbr_items;
	t_wall				floor;
	t_wall				celling;
	int					light;
	int					sector_id;
	t_sector			*next_sector;
	t_map				*map;
};

struct					s_box
{
	t_wall				walls[4];
	int					nbr_walls;
	int					size;
	t_wall				floor;
	t_wall				celling;
};

struct					s_map
{
	char				*name;
	t_box				box;
	t_sector			*sectors;
	int					size;
	t_point				spawn;
	int					i;
	int					cid;
	int					fid;
	t_item				*items;
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

struct					s_render
{
	int					x;
	int					n;
	int					x1;
	int					next_x;
	int					sector_id;
	double				wall_sqdist;
	double				wall_height;
	double				wall_dist;
	double				scalar;
	double				x2;
	double				y2;
	int					wall_y0;
	int					wall_y1;
	int					nb_sec;
	int					p_0;
	int					fid;
	int					cid;
	float				distance;
	float				height_item;
	float				widht_item;
	float				step_height;
	float				step_width;
	t_itab				*itab;
	t_sector			*sec_0;
	SDL_Surface			*tab_sdl_item[NB_TEXT_I + 1];
	SDL_Surface			*tab_sdl[NB_TEXT + 1];
	t_ray				*ray;
	t_sector			*s;
	t_wall				*wall;
	t_wall				wall_item;
	t_item				*item;
	t_item				*item_0;
	int					tab[10];
	int					nbr_items;
	int					nb_item_to_draw;
	double				tx;
	int					k;
	int					item_k;
};

struct					s_player
{
	int					fov;
	int					sector_id;
	double				posx;
	double				posy;
	double				posz;
	int					sprint;
	double				rotspeed;
	double				dx;
	double				dy;
	double				dz;
	double				planex;
	double				planey;
	double				movespeed;
	double				frametime;
	int					hp;
	int					hp_p;
	int					ammo;
	int					no_scope;
	t_item				*weapon;
};

struct					s_ray
{
	double				cam_x;
	double				x;
	double				y;
	double				z;
	double				x2;
	double				y2;
	double				z2;
	double				dx;
	double				dy;
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
	TTF_Font			*font;
	t_player			*player;
	t_map				*map;
	t_render			*render;
	double				olddirx;
	double				oldplanex;
	double				rotspeed;
	double				frametime;
	int					y_dec;
	int					x_dec;
	int					mouse_in;
	int					d_gun;
	int					d_gunb;
	int					clock;
	int					rain;
};

struct					s_itab
{
	float				dist;
	int					used;
	char				*name;
	int					item_x;
	int					item_y;
	int					start;
	int					end;
	int					item_h;
	int					item_w;
	int					text_id;
	int					h;
	int					w;
	int					id;
	int					pv;
};

struct					s_rgb
{
	int					r;
	int					g;
	int					b;
};

struct					s_input
{
	int					tir;
	int					up;
	int					down;
	int					left;
	int					right;
	int					shoot;
	int					straf_left;
	int					straf_right;
	int					rot_left;
	int					rot_right;
	double				straffer_x;
	double				straffer_y;
	double				diag_x;
	double				diag_y;
	int					diag;
	int					headup;
	int					headdown;
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

struct					s_f_tool
{
	int		i;
	int		j;
	int		k;
	double	dirx0;
	double	diry0;
	double	dirx1;
	double	diry1;
	int		p;
	double	dist;
	double	stepx;
	double	stepy;
	double	floorx;
	double	floory;
	double	posz;
	int		tx;
	int		ty;

};

struct					s_intersec
{
	float					a1;
	float					a2;
	float					b1;
	float					b2;
	float					x;
	float					y;
};

struct					s_w_draw
{
	double		pos_relative;
	t_point		hit;
	int			i;
	double		texy;
	int			temp;
	Uint32		color;
	double		temp2;
	double		step;
};

void					ft_put_weapon(t_var *info, t_render *render);
void					draw_i_color(t_var *info, t_render *render,
						t_i_tool *tool, t_item *item);
int						init_win1(t_var *info);
int						init_win2(t_var *info);
int						init_win3(t_var *info);
int						dealer(t_var *info);
void					sprint(t_var *info, SDL_Event event);
void					straff_and_rot(t_var *info, t_input input);
void					straff_and_rot2(t_var *info, t_input input);
void					rotate(t_var *info);
void					mouser(t_var *info);
void					get_speed(t_var *info);
void					get_move1(SDL_Event event, t_input *input);
void					get_move2(SDL_Event event, t_input *input);
int						move(t_var *info, t_input input);
void					move_diag(t_input *input);
void					diag(t_var *info, t_input input);
int						main_check(int ac, char **av, t_var *info);
int						png_parser_iter(t_render *render,
							int i, int fd);
void					diag1(t_var *info, t_input input);
void					diag2(t_var *info, t_input input);
void					diag3(t_var *info, t_input input);
void					diag4(t_var *info, t_input input);
void					rot_left(t_var *info);
void					rot_right(t_var *info);
SDL_Surface				*read_text(char *line);
void					dealer_iter(t_var *info, t_render *render);
void					sdl_main(t_render *render, t_var *info);
void					main_tool(t_var *info, t_render *render);
int						load_exit(char *the_map);
int						init_main(int ac, char **av,
							t_var *info, t_player *player);
void					init_player(t_player *player, t_map *map);
void					ft_init_pour_linstant(t_var *info);
void					you_win(t_var *info, t_render *render, t_i_tool *tool);
int						init_render(t_var *info, t_render *render,
							int sector_id);
int						init_next_render(t_var *info, t_render *render);
int						same_sector(t_var *info, t_item *item, int sector_id);
int						enemys_in_sector(t_var *info, t_player *player);
int						hit_objet(t_var *info, t_render *render);
void					update_ray_box(t_var *info, t_render *render,
							int dir, t_point p);
void					w_draw_calc(t_render *render, t_w_draw *draw);
void					draw_bottop(t_var *info, t_render *render);
void					draw_tex(t_var *info, t_render *render);
void					draw_textures(t_var *info, t_render *render);
void					draw_texture_wall(t_var *info, t_render *render);
Uint32					get_pixel(SDL_Surface *tex, int x, int y);
int						intersect(t_ray *ray, t_wall *wall);
void					init_floor(t_var *info, t_f_tool *tool);
int						darken_floor(t_f_tool *tool, t_render *render);
void					i_color_set(t_var *info, t_render *render,
							t_i_tool *tool, t_item *item);
int						darken_wall(t_var *info, Uint32 color,
							t_render *render, int i);
int						rgb_calc(int r, int g, int b);
int						rain_gen(t_var *info);
void					pls_ennemy(t_render *render, t_i_tool *tool, int k);
void					update_render(t_var *info, t_render *render);
void					put_item(int k, t_item *src,
							t_render *render, t_var *info);
void					shoot_ennemy(t_var *info);
void					change_weapon(t_var *info);
void					rgb_cap(t_rgb *rgb);
void					ft_exit(t_var *info, t_render *render);
void					free_info(t_var *info);
void					free_player(t_player *player);
void					free_map(t_map *map);
void					free_itab(t_itab *itab, t_render *render);
void					free_ray(t_ray *ray);
void					free_wall(t_wall *wall);
void					free_item(t_item *item);
void					free_render(t_render *render);
int						verify_crossing(t_point new,
							t_point old, t_sector *sector);
int						center_in_poly(t_point a, t_point b, t_sector *sector);
int						is_new_point_in_sector(t_point new, t_wall *walls);
int						check_wall_intersections(t_point new,
							t_point old, t_wall wall);
void					hitmarker(t_var *info);
void					crosshair(t_var *info);
int						comparator1(t_point new, t_point old,
							t_point w1, t_point w2);
int						comparator2(t_point new, t_point old,
							t_point w1, t_point w2);
void					red_flash(t_var *info);
void					draw_item_2(t_render *render,
							t_var *info, int k, t_item *item);
void					check_intersect(t_var *info,
							t_render *render, t_item *item);
void					draw_column(t_var *info, t_render *render, int *tab);
int						raycasting(t_var *info, t_render *render);
void					put_pixel(Uint32 color, int x,
							int y, SDL_Surface *image);
void					go_to_sector(t_sector *sec_0, int id, t_render *render);
int						xy_in_ab(double x, double y, t_point a, t_point b);
int						calc_item_wall(t_render *render,
						t_item *item, t_var *info);
void					draw_item(t_render *render, t_var *info);
double					norm2(double x, double y);
void					update_ray(t_var *info, t_render *render);
double					scalar(double x1, double y1, double x2, double y2);
void					init_cast(t_var *info, t_render *render, t_ray *ray);
void					init_nb_sec(t_sector *sector, t_render *render);
int						may_weapon(t_item *item);
int						draw_i2_help(t_var *info, t_render *render,
							t_i_tool *tool, int k);
int						mouse_test(t_var *info);
void					rotate(t_var *info);
void					mouse_cap(t_var *info, SDL_Event event);
void					mouser(t_var *info);
void					hp_hud_help(t_var *info, char *nb,
							SDL_Rect pos, SDL_Color color);
t_item					*go_to_item(t_item *item, char c);
void					hud(t_var *info, t_player *player, t_map *map);
void					weapon(t_var *info, t_player *player, SDL_Color color);
void					inventory(t_var *info,
							SDL_Color color);
void					name(t_var *info, t_map *map, SDL_Color color);
void					hp(t_var *info, t_player *player, SDL_Color color);
void					munitions(t_var *info, SDL_Color color);
int						check_map(char *the_map);
int						info_map(char *str, t_map *map);
int						rec_map(char *the_map, t_map *map);
t_box					rec_box(char *the_map, t_map *map);
t_sector				*rec_sectors(char *the_map, t_map *map);
void					rec_sectors_int(char *the_map,
							t_sector *sectors, t_map *map);
t_point					rec_point(char *the_map, t_map *map);
t_wall					rec_wall(char *the_map, t_map *map);
double					rec_double(char *the_map, t_map *map);
char					*rec_x_char(char *the_map, t_map *map);
int						rec_int(char *the_map, t_map *map);
char					rec_char(char *the_map, t_map *map);
char					*recup_map(char *src);
char					*little_strjoin(char *src, char c);
t_item					*rec_item(char *the_map, t_map *map);
int						do_trigo(t_var *info, t_wall *wall);
double					calc_dist(t_point a, t_point b);
int						tab_path(t_render *renderer);
void					ft_exit(t_var *info, t_render *render);
void					free_map(t_map *map);
void					init_tab(int *tab, int n);
int						hitboxy(t_var *info, t_render *render, double diry);
int						hitboxx(t_var *info, t_render *render, double dirx);
int						hitbox(t_var *info, t_render *render, int dir);
int						hitbox_diag(t_var *info,
						t_render *render, double diagx, double diagy);
int						is_new_point_in_sector(t_point new, t_wall *walls);
int						is_in_sectors_spawn(t_point first, t_map *map);
int						is_in_sector_float(float center_x, float center_y,
						t_sector *sector);
float					ft_fabs(float a);
t_sector				*get_to_last_sector(t_sector *sectors);
int						nbr_of_sectors(t_map *map);
t_sector				*get_a_sector_by_id(t_map *map, int id);
float					cross_product(t_point a, t_point b, t_point c);
int						is_between(float x, float a, float b);
int						is_same_point(t_point a, t_point b);
int						is_in_sectors(t_point first, t_map *map);
int						is_in_sector(t_point first, t_sector *sector);
int						check_wall_intersections(t_point new,
							t_point old, t_wall wall);
int						is_both_superior_y(t_point a, t_point b,
							t_point c, t_point d);
int						is_both_inferior_y(t_point a, t_point b,
							t_point c, t_point d);
int						is_both_superior_x(t_point a, t_point b,
							t_point c, t_point d);
int						is_both_inferior_x(t_point a, t_point b,
							t_point c, t_point d);
int						is_in_sectors_float(float center_x,
							float center_y, t_map *map);
int						pnpoly_float(int nbr_walls, t_wall *walls,
							float center_x, float center_y);
int						player_sec(t_sector *sector, t_var *info);
void					init_nb_sec(t_sector *sector, t_render *render);
int						tex_floor_ciel(t_var *info, t_render *render);
void					init_ceilling(t_var *info, t_f_tool *tool);
t_render				*cpy_render(t_render *render);
int						gameplay(t_var *info);
int						hit_box(t_var *info, t_render *render);
t_item					*init_item(t_render *render, t_item *src, int i);
void					free_info(t_var *info);
int						png_parse();
int						read_core_text(t_render *renderer);
void					hit_ennemy(t_var *info);
int						draw_line_condition(t_line *line);
int						draw_line(t_var *info, t_line *line, Uint32 color);
void					init_ceilling(t_var *info, t_f_tool *tool);

#endif
