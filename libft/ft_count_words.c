/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:52:27 by lbonnete          #+#    #+#             */
/*   Updated: 2018/11/16 16:19:42 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_count_words(const char *s, char c)
{
	int i;
	int cap;
	int cpt;

	cap = 0;
	i = 0;
	cpt = 0;
	while (s[i])
	{
		if ((s[i] != c) && !cap)
		{
			cpt++;
			cap = 1;
		}
		if (s[i] == c)
			cap = 0;
		i++;
	}
	return (cpt);
}
