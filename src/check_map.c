int	check_map_2(char *the_map, int i)
{
	if (the_map[i] == 'm')
                if (the_map[i + 1] != 'b')
			return (0);
        if (the_map[i] == 'b')
                if (the_map[i + 1] != 'w')
                        return (0);
        if (the_map[i] == 'w')
                if (the_map[i + 1] != 'p')
                        return (0);
        if (the_map[i] == 's')
                if (the_map[i + 1] != 'i')
                        return (0);
        if (the_map[i] == 'p')
                if (the_map[i + 1] != 'i')
                        return (0);
        if (the_map[i] == 'x')
                if (the_map[i + 1] != 'w')
                        return (0);
        if (the_map[i] == 'd')
                if (the_map[i + 1] != 'i')
                        return (0);
	return (1);
}

int	check_map(char *the_map)
{
	int	i;

	i = -1;
	while (the_map[++i])
	{
		if ((the_map[i] > '9' || the_map[i] < '0')
			&& the_map[i] != 'm' && the_map[i] != 'b'
			&& the_map[i] != 'w' && the_map[i] != 's'
			&& the_map[i] != 'p' && the_map[i] != 'x'
			&& the_map[i] != 'd' && the_map[i] != 'e'
			&& the_map[i] != 'c' && the_map[i] != 'i')
			return (0);
		if (the_map[i] == 'i')
			if (the_map[i + 1] > '9' || the_map[i + 1] < '0')
				return (0);
		if (check_map_2(the_map, i) == 0)
			return (0);
	}
	return (1);
}
