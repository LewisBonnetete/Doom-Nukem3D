/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom-nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 14:27:51 by lbonnete          #+#    #+#             */
/*   Updated: 2020/02/19 14:38:43 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include <SDL.h>
# include <SDL_image.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"
# define WINDOW_W			1280
# define WINDOW_H			720
# define NB_THREADS_MAX		12
# define RMASK				0
# define GMASK				0
# define BMASK				0
# define AMASK				0
# define WALL_H				256
# define DECALLAGE			0
# define BLACK				0x000000
# define SKY_BLUE			0x00BFFF
# define GRASS_GREEN		0x1FBC3F
# define SOUTH_WALL			0xd2b48c
# define NORTH_WALL			0xD28F8F
# define EAST_WALL			0xDAA520
# define WEST_WALL			0xF4A460

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
	int					sector_next;
	double				height;
	double				eq_slope;
	double				eq_cste;
	int					sector_id_it_leads_to;
};

struct 					s_sector
{
	t_wall				*walls;
	int 				nbr_walls;
	t_wall				floor;		// ???
	t_wall				celling;	// ???
	int					light;
	int					sector_id;
	t_sector			*next_sector;
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
	int					nbr_sectors;
	int					size;
	SDL_Surface			*text_tab[10];
	t_point				spawn;
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
	t_map				map;
	double				olddirx;
	double				oldplanex;
	double				rotspeed;
	double				frametime;
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
void					init_box(t_map *map);
//algo
int		xy_in_ab(double x, double y, t_point a, t_point b);
int		xy_in_frontview(double x, double y, t_ray ray);
void	draw_tex(t_var *info, t_render *render);
int     raycasting(t_var *info, t_render *render);
void	init_box(t_map *map);
void	init_artificial_map(t_map *map);
void	draw_bottop(t_var *info, t_render *render);
void	put_pixel_to_suface(Uint32 color, int x, int y, SDL_Surface *image);

#endif
