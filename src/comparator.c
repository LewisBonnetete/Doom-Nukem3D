/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trabut <trabut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:47:46 by lbonnete          #+#    #+#             */
/*   Updated: 2020/07/09 15:33:48 by trabut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		comparator1(t_point new, t_point old, t_point w1, t_point w2)
{
	if (w1.x != new.x)
		return (1);
	if (w1.x == new.x && w2.x == old.x && w1.y == new.y && w2.y == old.y)
		return (1);
	if (w2.x == new.x && w1.x == old.x && w2.y == new.y && w1.y == old.y)
		return (1);
	if (w1.y == new.y && w2.y == old.y && w1.x == w2.x && new.x == old.x)
		return (1);
	if (w1.y == old.y && w2.y == new.y && w1.x == w2.x && new.x == old.x)
		return (1);
	if (is_both_inferior_y(new, old, w1, w2)
	|| is_both_superior_y(new, old, w1, w2))
		return (1);
	return (0);
}

int		comparator2(t_point new, t_point old, t_point w1, t_point w2)
{
	if (w1.y != new.y)
		return (1);
	if (w1.x == new.x && w2.x == old.x && w1.y == new.y && w2.y == old.y)
		return (1);
	if (w2.x == new.x && w1.x == old.x && w2.y == new.y && w1.y == old.y)
		return (1);
	if (w1.x == new.x && w2.x == old.x && w1.y == w2.y && new.y == old.y)
		return (1);
	if (w1.x == old.x && w2.x == new.x && w1.y == w2.y && new.y == old.y)
		return (1);
	if (is_both_inferior_x(new, old, w1, w2)
	|| is_both_superior_x(new, old, w1, w2))
		return (1);
	return (0);
}
