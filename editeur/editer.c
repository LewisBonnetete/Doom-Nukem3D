/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/02/19 15:40:22 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem_edit.h"

int		editer(t_var *info)
{
	t_input_edit input_edit;
	int fd;

	if (-1 == (fd = open_package()))
	{
		ft_putendl("Package error");
		return (0);
	}
	while (dealers_edit(info, &input_edit))
	{
		

		

	}
	return (1);
}