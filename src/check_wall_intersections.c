/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall_intersections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/09 15:30:29 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	calculator1(t_point new, t_point old,
t_wall wall, t_intersec *its)
{
	t_point		w1;
	t_point		w2;

	(void)old;
	w1 = wall.a;
	w2 = wall.b;
	its->a2 = (w2.y - w1.y) / (w2.x - w1.x);
	its->b2 = w1.y - (its->a2 * w1.x);
	its->y = its->a2 * new.x + its->b2;
}

void	calculator2(t_point new, t_point old,
t_wall wall, t_intersec *its)
{
	t_point		w1;
	t_point		w2;

	w1 = wall.a;
	w2 = wall.b;
	its->a1 = (new.y - old.y) / (new.x - old.x);
	its->b1 = old.y - (its->a1 * old.x);
	its->y = its->a1 * w1.x + its->b1;
}

int		check_wall_intersections2(t_point new, t_point old,
t_wall wall, t_intersec *its)
{
	t_point		w1;
	t_point		w2;

	w1 = wall.a;
	w2 = wall.b;
	if (is_same_point(new, w1) || is_same_point(old, w1)
	|| is_same_point(new, w2) || is_same_point(old, w2))
		return (1);
	if (new.x == old.x && w1.x != w2.x)
	{
		calculator1(new, old, wall, its);
		if (is_between(its->y, (float)old.y, (float)new.y)
		&& is_between(its->y, (float)w1.y, (float)w2.y))
			return (0);
		return (1);
	}
	else if (w1.x == w2.x && new.x != old.x)
	{
		calculator2(new, old, wall, its);
		if (is_between(its->y, (float)old.y, (float)new.y)
		&& is_between(its->y, (float)w1.y, (float)w2.y))
			return (0);
		return (1);
	}
	return (-1);
}

void	calculator3(t_point new, t_point old,
t_wall wall, t_intersec *its)
{
	t_point		w1;
	t_point		w2;

	w1 = wall.a;
	w2 = wall.b;
	its->a1 = (float)(new.y - old.y) / (float)(new.x - old.x);
	its->a2 = (float)(w2.y - w1.y) / (float)(w2.x - w1.x);
	its->b1 = (float)old.y - (its->a1 * (float)old.x);
	its->b2 = (float)w1.y - (its->a2 * (float)w1.x);
}

int		check_wall_intersections(t_point new, t_point old, t_wall wall)
{
	t_point		w1;
	t_point		w2;
	t_intersec	its;

	its.x = 0.0;
	its.y = 0.0;
	w1 = wall.a;
	w2 = wall.b;
	if (check_wall_intersections2(new, old, wall, &its) != -1)
		return (check_wall_intersections2(new, old, wall, &its));
	else if (w1.x == w2.x && new.x == old.x)
		return (comparator1(new, old, w1, w2));
	else if (w1.y == w2.y && new.y == old.y)
		return (comparator2(new, old, w1, w2));
	else
	{
		calculator3(new, old, wall, &its);
		if (its.a1 == its.a2)
			return (1);
		its.x = (its.b2 - its.b1) / (its.a1 - its.a2);
		if (is_between(its.x, (float)old.x, (float)new.x)
		&& is_between(its.x, (float)w1.x, (float)w2.x))
			return (0);
	}
	return (1);
}
