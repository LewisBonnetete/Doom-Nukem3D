/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealers4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:04:28 by lewis             #+#    #+#             */
/*   Updated: 2020/07/07 16:05:39 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	move_diag(t_input *input)
{
	input->diag = 0;
	if (input->up && input->straf_right && !input->down && !input->straf_left)
	{
		input->diag = 1;
	}
	else if (input->up && input->straf_left && !input->down && !input->straf_right)
	{
		input->diag = 2;
	}
	else if (input->down && input->straf_left && !input->up && !input->straf_right)
	{
		input->diag = 3;
	}
	else if (input->down && input->straf_right && !input->up && !input->straf_left)
	{
		input->diag = 4;
	}
}

void	diag(t_var *info, t_input input)
{
	if (input.diag == 1)
	{
		diag1(info, input);
	}
	if (input.diag == 2)
	{
		diag2(info, input);
	}
	if (input.diag == 3)
	{
		diag3(info, input);
	}
	if (input.diag == 4)
	{
		diag4(info, input);
	}
}
