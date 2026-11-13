#include "grim_fetcher.h"

static int		fill_map_lines(int fd, char **map, size_t height);
static int		get_map_height(int *fd, char *path);
static size_t	strlen_without_whitespaces(char *s);
static char		*strdup_without_whitespaces(char *s);

char	**copy_map(int *fd, char *path)
{
	char	**map;
	size_t	height;

	height = get_map_height(fd, path);
	if (*fd < 0)
	{
		put_error(E_MAP_READ, path, 0);
		return (0);
	}
	map = calloc(height + 1, sizeof(char *));
	if (!map)
	{
		put_error(E_FAIL_MEM, 0, 0);
		return (0);
	}
	if (fill_map_lines(*fd, map, height))
		return (map);
	free_map_data(map);
	put_error(E_FAIL_MEM, 0, 0);
	return (0);
}

static int	fill_map_lines(int fd, char **map, size_t height)
{
	char	*s;
	size_t	i;
	int		is_success;

	i = 0;
	is_success = 1;
	s = gnl(fd);
	while (s)
	{
		if (is_success && i < height && strlen_without_whitespaces(s))
		{
			map[i] = strdup_without_whitespaces(s);
			is_success = map[i++] != 0;
		}
		free(s);
		s = gnl(fd);
	}
	return (is_success);
}

static int	get_map_height(int *fd, char *path)
{
	char	*s;
	int		height;

	height = 0;
	s = gnl(*fd);
	while (s)
	{
		if (strlen_without_whitespaces(s))
			++height;
		free(s);
		s = gnl(*fd);
	}
	close(*fd);
	*fd = open(path, O_RDONLY);
	return (height);
}

static size_t	strlen_without_whitespaces(char *s)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (!isspace(s[i]))
			++len;
		++i;
	}
	return (len);
}

static char	*strdup_without_whitespaces(char *s)
{
	char	*dup;
	size_t	i;
	size_t	len;

	len = strlen_without_whitespaces(s);
	if (!len)
		return (0);
	dup = malloc((len + 1) * sizeof(char));
	if (!dup)
		return (0);
	i = 0;
	while (*s)
	{
		if (!isspace(*s))
			dup[i++] = *s;
		++s;
	}
	dup[i] = 0;
	return (dup);
}
