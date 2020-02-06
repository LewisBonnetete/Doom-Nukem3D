/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 17:54:54 by lbonnete          #+#    #+#             */
/*   Updated: 2018/11/24 15:31:09 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static	void	fill_it(char const *s, char c, int *it)
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
			it[cpt] = i;
			cpt++;
			cap = 1;
		}
		if (s[i] == c)
			cap = 0;
		i++;
	}
}

static	char	**fill_tab(int *nofw, char **tab, char const *s, char c)
{
	int		i;
	int		j;
	int		nofl;
	int		*it;

	i = 0;
	if (!(it = (int *)malloc(sizeof(int) * (*nofw))))
		return (0);
	fill_it(s, c, it);
	while (i < *nofw)
	{
		j = 0;
		nofl = ft_count_letters(&s[it[i]], c);
		if (!(tab[i] = malloc(sizeof(char) * (nofl + 1))))
			return (0);
		tab[i][nofl] = 0;
		while (j < nofl)
			tab[i][j++] = s[it[i]++];
		i++;
	}
	free(it);
	return (tab);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		nofw;

	if (!(s))
		return (0);
	nofw = ft_count_words(s, c);
	if (!(tab = (char **)malloc(sizeof(char *) * (nofw + 1))))
		return (0);
	tab[nofw] = 0;
	return (fill_tab(&nofw, tab, s, c));
}
