/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealers_edit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/02/19 15:55:58 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem_edit.h"

int		dealers_edit(t_var *info, t_input_edit *input_edit)
{
	SDL_Event		event;

	(void)info;
	(void)input_edit;
	if (SDL_PollEvent(&event) == 1)
	{
		if (event.type == SDL_QUIT)
			return (0);
		if (event.key.keysym.sym == SDLK_ESCAPE && event.type == SDL_KEYDOWN)
			return (0);
		if (event.key.keysym.sym == SDLK_s)
		{
			if (event.key.state == SDL_PRESSED)
				input_edit->t_s = 1;
			else
				input_edit->t_s = 0;
		}
		if (event.key.keysym.sym == SDLK_p)
		{
			if (event.key.state == SDL_PRESSED)
				input_edit->t_p = 1;
			else
				input_edit->t_p = 0;
		}
	}
	return (1);

}