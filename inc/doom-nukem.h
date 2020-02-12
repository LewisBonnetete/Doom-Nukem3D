/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom-nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewis <lewis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 14:27:51 by lbonnete          #+#    #+#             */
/*   Updated: 2020/02/11 16:29:14 by lewis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include <SDL.h>
# include <SDL_image.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <pthread.h>
# include "../libft/libft.h"
# define WINDOW_W			1280
# define WINDOW_H			720
# define W_H 				853
# define NB_THREADS_MAX		12
# define BLACK				0x000000
# define SKY_BLUE			0x00BFFF
# define GRASS_GREEN		0x1FBC3F
# define SOUTH_WALL			0xd2b48c
# define NORTH_WALL			0xD28F8F
# define EAST_WALL			0xDAA520
# define WEST_WALL			0xF4A460
# define RMASK				0
# define GMASK				0
# define BMASK				0
# define AMASK				0
# define EXIT_W				4
# define NORTH				3
# define SOUTH				2
# define WEST				1
# define EAST				0

typedef struct s_input	t_input;
typedef	struct s_var	t_var;
typedef	struct s_text	t_text;
typedef	struct s_point	t_point;
typedef	struct s_wall	t_wall;
typedef	struct s_wall	t_portal;
typedef	struct s_sector	t_sector;
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
	t_text				text;
	int					wall_id;
};

struct 					s_portal
{
	t_point				a;
	t_point				b;
	t_point				c;
	t_point				d;
	t_text				text;
	int					textured;
	t_text				fill;
	int					sector_id;
	int					sector_next;
};

struct 					s_sector
{
	t_wall				*walls;
	t_portal			*portals;
	t_wall				floor;
	t_wall				celling;
	int					light;
	int					sector_id;
};

struct 					s_map
{
	t_sector			*sectors;
	int					length;
	int					width;
	int					height;
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
	SDL_Surface			*text_tab[6];
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

#endif