/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   png_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:04:28 by lewis             #+#    #+#             */
/*   Updated: 2020/07/27 17:48:30 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int			tex_loader(SDL_Surface *tab[12])
{
	if ((tab[0] = IMG_Load("./xpm_textures/fps.png")) == 0)
		return (0);
	if ((tab[1] = IMG_Load("./xpm_textures/dark_wall.png")) == 0)
		return (0);
	if ((tab[2] = IMG_Load("./xpm_textures/stone3.png")) == 0)
		return (0);
	if ((tab[3] = IMG_Load("./xpm_textures/stone2.png")) == 0)
		return (0);
	if ((tab[4] = IMG_Load("./xpm_textures/ak47.png")) == 0)
		return (0);
	if ((tab[5] = IMG_Load("./xpm_textures/creeper.png")) == 0)
		return (0);
	if ((tab[6] = IMG_Load("./xpm_textures/barrel.png")) == 0)
		return (0);
	if ((tab[7] = IMG_Load("./xpm_textures/soldier.png")) == 0)
		return (0);
	if ((tab[8] = IMG_Load("./xpm_textures/heal.png")) == 0)
		return (0);
	if ((tab[9] = IMG_Load("./xpm_textures/balle.png")) == 0)
		return (0);
	if ((tab[10] = IMG_Load("./xpm_textures/dos_soldier.png")) == 0)
		return (0);
	if ((tab[11] = IMG_Load("./xpm_textures/portal.png")) == 0)
		return (0);
	return (1);
}

int			png_parse(void)
{
	int			i;
	SDL_Surface	*tab[12];
	Uint32		*pixels;
	int			fd;
	int			j;

	ft_putendl("Parsing textures...");
	if (!(tex_loader(tab)) || (fd = open("core", O_RDWR)) == -1)
		return (0);
	j = -1;
	while (++j < 12)
	{
		pixels = tab[j]->pixels;
		i = -1;
		ft_putnbr_fd(tab[j]->h, fd);
		ft_putstr_fd(";", fd);
		while (++i < tab[j]->h * tab[j]->w)
		{
			ft_putnbr_fd(pixels[i], fd);
			ft_putstr_fd(";", fd);
		}
		ft_putendl_fd("", fd);
		free(tab[j]);
	}
	return (0);
}

int			read_text_tool(char *line, SDL_Surface *text, int i)
{
	int		tmp;

	tmp = i;
	while (line[tmp] != ';')
		tmp++;
	line[tmp] = '\0';
	text->h = ft_atoi(line);
	text->w = text->h;
	if (!(text->pixels = (Uint32*)ft_memalloc(sizeof(Uint32)
		* text->w * text->h)))
		return (0);
	tmp++;
	return (tmp);
}

SDL_Surface	*read_text(char *line)
{
	SDL_Surface	*text;
	int			i;
	int			p;
	int			debut;
	int			len;

	len = ft_strlen(line);
	if (!(text = (SDL_Surface*)ft_memalloc(sizeof(SDL_Surface))))
		return (0);
	i = 0;
	p = 0;
	i = read_text_tool(line, text, i);
	while (i < len)
	{
		debut = i;
		while (line[i] != ';')
			i++;
		line[i] = '\0';
		((Uint32*)(text->pixels))[p] = ft_atoi(&(line[debut]));
		p++;
		i++;
	}
	return (text);
}

int			read_core_text(t_render *renderer)
{
	int		fd;
	int		i;

	if ((fd = open("core", O_RDWR)) == -1)
		return (0);
	i = -1;
	system("clear");
	while (++i < 12)
	{
		if (!(png_parser_iter(renderer, i, fd)))
			return (0);
	}
	ft_putendl("Textures loaded");
	ft_putendl("Game launched");
	ft_putendl("Arrows to look around\nWASD to move");
	ft_putendl("Mouse or Space to shoot");
	ft_putendl("Shift to sprint\nM to set mouse in/out");
	ft_putendl("V to switch between weapons");
	ft_putendl("P to enable rain\nEsc to quit");
	ft_putstr("Try to reach the portal ");
	ft_putstr("to escape the maze before they take you!");
	ft_putendl("");
	return (1);
}
