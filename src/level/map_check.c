#include "grim_fetcher.h"

static int	are_symbols_in_right_amount(char **map);
static void	put_symbol_amount_errors(int amount[3]);
static int	is_map_closed_off_by_walls(char **map);

int	are_symbols_valid(char **map)
{
	size_t	i;
	size_t	j;
	char	symbol[2];

	if (!map)
		return (0);
	symbol[1] = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!strchr("01BCEGP", map[i][j]))
			{
				symbol[0] = map[i][j];
				return (put_error(E_MAP_SYMBOL, symbol, 0));
			}
			++j;
		}
		++i;
	}
	return (are_symbols_in_right_amount(map));
}

static int	are_symbols_in_right_amount(char **map)
{
	int		amount[3];
	char	*s;

	amount[0] = 0;
	amount[1] = 0;
	amount[2] = 0;
	while (*map)
	{
		s = *map;
		while (*s)
		{
			amount[0] += *s == 'C';
			amount[1] += *s == 'E';
			amount[2] += *s == 'P';
			++s;
		}
		++map;
	}
	if (amount[0] >= 1 && amount[1] == 1 && amount[2] == 1)
		return (1);
	put_symbol_amount_errors(amount);
	return (0);
}

static void	put_symbol_amount_errors(int amount[3])
{
	if (!amount[0])
		put_error(E_MAP_NO_COLLEC, 0, 0);
	if (!amount[1])
		put_error(E_MAP_NO_EXIT, 0, 0);
	else if (amount[1] > 1)
		put_error(E_MAP_EXITS, 0, 0);
	if (!amount[2])
		put_error(E_MAP_NO_PLAYER, 0, 0);
	else if (amount[2] > 1)
		put_error(E_MAP_PLAYERS, 0, 0);
	return ;
}

int	is_map_rectangular_and_closed_off(char **map)
{
	size_t	i;
	size_t	len;
	size_t	curr_len;

	i = 0;
	len = 0;
	while (map[i])
	{
		curr_len = strlen(map[i]);
		if (!len)
			len = curr_len;
		else if (curr_len && len != curr_len)
			return (put_error(E_MAP_RECT, 0, 0));
		++i;
	}
	if (!is_map_closed_off_by_walls(map))
		return (put_error(E_MAP_WALLS, 0, 0));
	return (1);
}

static int	is_map_closed_off_by_walls(char **map)
{
	size_t	i;
	size_t	j;
	size_t	width;

	i = 0;
	width = map[0] ? strlen(map[0]) : 0;
	while (map[i])
	{
		if (map[i][0] != '1' || map[i][width - 1] != '1')
			return (0);
		if (i == 0 || !map[i + 1])
		{
			j = 0;
			while (j < width)
			{
				if (map[i][j] != '1')
					return (0);
				++j;
			}
		}
		++i;
	}
	return (1);
}
