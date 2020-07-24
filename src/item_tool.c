/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_tool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:04:28 by lewis             #+#    #+#             */
/*   Updated: 2020/07/15 17:41:25 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		item(t_item *dest, int a)
{
	if (a == 0)
	{
		dest->h = 128;
		dest->w = 128;
		dest->text_id = 0;
		dest->mun = 50;
		dest->hold = 0;
		return (1);
	}
	if (a == 1)
	{
		dest->h = 350;
		dest->w = 350;
		dest->text_id = 1;
		dest->pv = 20;
		return (1);
	}
	return (0);
}

int		item2(t_item *dest, int a)
{
	if (a == 0)
	{
		dest->h = 250;
		dest->w = 250;
		dest->text_id = 4;
		return (1);
	}
	if (a == 1)
	{
		dest->h = 100;
		dest->w = 100;
		dest->text_id = 5;
		return (1);
	}
	if (a == 2)
	{
		dest->h = 400;
		dest->w = 400;
		dest->text_id = 3;
		dest->pv = 40;
		return (1);
	}
	return (0);
}

int		item3(t_item *dest, int a)
{
	if (a == 0)
	{
		dest->h = 300;
		dest->w = 300;
		dest->text_id = 2;
		return (1);
	}
	if (a == 1)
	{
		dest->h = 400;
		dest->w = 400;
		dest->text_id = 7;
		return (1);
	}
	return (0);
}

int		item_reader(t_item *dest)
{
	if (dest->name[0] == 'a')
		item(dest, 0);
	else if (dest->name[0] == 'c')
		item(dest, 1);
	else if (dest->name[0] == 'b')
		item3(dest, 0);
	else if (dest->name[0] == 'h')
		item2(dest, 0);
	else if (dest->name[0] == 'm')
		item2(dest, 1);
	else if (dest->name[0] == 's')
		item2(dest, 2);
	else if (dest->name[0] == 'p')
		item3(dest, 1);
	else
		return (1);
	return (0);
}

t_item	*init_item(t_render *render, t_item *src, int i)
{
	t_item	*dest;

	if (!(dest = (t_item *)ft_memalloc(sizeof(t_item))))
		return (0);
	dest->name = ft_strdup(src->name);
	dest->x = src->x;
	dest->y = src->y;
	dest->cap = 0;
	dest->id = i;
	render->nbr_items++;
	if (item_reader(dest))
	{
		render->nbr_items--;
		if (src->next_item)
			dest = init_item(render, src->next_item, i);
		else
			dest = NULL;
		return (dest);
	}
	if (src->next_item)
		dest->next_item = init_item(render, src->next_item, i + 1);
	else
		dest->next_item = NULL;
	return (dest);
}
