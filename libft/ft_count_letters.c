/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_letters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:53:48 by lbonnete          #+#    #+#             */
/*   Updated: 2018/12/05 14:09:16 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_count_letters(const char *w, char c)
{
	int cpt;

	if (!w)
		return (0);
	cpt = 0;
	while (w[cpt] != c)
		cpt++;
	return (cpt);
}
