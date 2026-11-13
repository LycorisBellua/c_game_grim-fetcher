#include "grim_fetcher.h"

static int	get_map_fd(char *path);
static int	is_valid_map_file(const char *path);

char	**get_map_data(char *path)
{
	int		fd;
	char	**map;

	fd = get_map_fd(path);
	if (fd < 0)
		return (0);
	map = copy_map(&fd, path);
	close(fd);
	if (!are_symbols_valid(map) || !is_map_rectangular_and_closed_off(map))
	{
		free_map_data(map);
		return (0);
	}
	return (map);
}

void	free_map_data(char **map)
{
	char	**ptr;

	if (!map)
		return ;
	ptr = map;
	while (*map)
	{
		free(*map);
		++map;
	}
	free(ptr);
	return ;
}

static int	get_map_fd(char *path)
{
	int	fd;

	if (!is_valid_map_file(path))
		return (-1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (put_error(E_MAP_READ, path, -1));
	return (fd);
}

static int	is_valid_map_file(const char *path)
{
	struct stat	st;
	const char	*name;

	if (!path || access(path, R_OK) < 0 || stat(path, &st) < 0
		|| !S_ISREG(st.st_mode))
		return (put_error(E_MAP_READ, path, 0));
	name = get_filename(path);
	if (!strcmp(name, ".map"))
		return (put_error(E_MAP_NAME, path, 0));
	if (!has_extension(name, ".map"))
		return (put_error(E_MAP_TYPE, path, 0));
	return (1);
}
