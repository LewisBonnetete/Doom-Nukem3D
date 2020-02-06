/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 15:56:45 by lbonnete          #+#    #+#             */
/*   Updated: 2019/10/02 13:52:33 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	int		read_and_fill(int fd, char **str)
{
	char	*buff;
	char	*tp1;
	int		ret;

	if (!(buff = (char *)malloc(BUFF_SIZE + 1)))
		return (-1);
	if (!(ret = read(fd, buff, BUFF_SIZE)))
	{
		free(buff);
		return (ret);
	}
	else
	{
		buff[ret] = 0;
		if (!(tp1 = ft_strdup(*str)))
			return (-1);
		ft_strdel(str);
		if (!(*str = ft_strjoin(tp1, buff)))
			return (-1);
		ft_strdel(&tp1);
		free(buff);
	}
	return (ret);
}

static	char	*ft_strclrcpy(char **str)
{
	int		n;
	char	*tmp;
	char	*ret;

	n = 0;
	if (!(tmp = ft_strdup(*str)))
		return (0);
	n = ft_count_letters(tmp, CHAR);
	if (!(ret = (char *)malloc(n + 1)))
		return (0);
	ft_strncpy(ret, tmp, n);
	ret[n] = 0;
	ft_strdel(&tmp);
	if (!(tmp = (ft_strdup(*str + n + 1))))
		return (0);
	ft_strdel(str);
	*str = tmp;
	return (ret);
}

int				get_next_line(int fd, char **line)
{
	static	char	*str[OPEN_MAX + 1];
	int				ret;

	if (line == 0 || BUFF_SIZE <= 0 || fd < 0 || fd >= OPEN_MAX)
		return (-1);
	while (!(ft_strchr(str[fd], CHAR)))
	{
		if ((ret = read_and_fill(fd, &str[fd])) == -1)
			return (-1);
		if (ret == 0)
		{
			if (str[fd] == 0)
				return (0);
			if (str[fd][0] == 0)
				return (0);
			if (!(*line = ft_strdup(str[fd])))
				return (-1);
			ft_strclr(str[fd]);
			return (1);
		}
	}
	if (!(*line = ft_strclrcpy(&str[fd])))
		return (-1);
	return (1);
}
