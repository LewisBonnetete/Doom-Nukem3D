/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom-nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewis <lewis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 14:27:51 by lbonnete          #+#    #+#             */
/*   Updated: 2020/06/05 13:39:01 by lewis            ###   ########.fr       */
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

typedef struct s_input	t_input;
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

};

struct 					s_sector
{
	t_wall				*walls;
	int 				nbr_walls;
	t_wall				floor;
	t_wall				celling;
	double				light;
	int					sector_id;
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

struct					s_var
{
	SDL_Window			*window;
	SDL_Event			*event;
	SDL_Renderer		*renderer;
	SDL_Surface			*image;
	SDL_Texture			*texture;
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

//init func
void					init_box(t_map *map);

#endif