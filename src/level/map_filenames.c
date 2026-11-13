#include "grim_fetcher.h"

static int	is_map_file(const char *name);
static int	populate_array(t_man *man);
static void	sort_strings(char **arr, int (*cmp)(const char *, const char *));

void	set_map_filenames(t_man *man)
{
	DIR				*dir;
	struct dirent	*entry;
	size_t			count;

	dir = opendir(MAP_DIR);
	if (!dir)
		return ;
	count = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (is_map_file(entry->d_name))
			++count;
		entry = readdir(dir);
	}
	closedir(dir);
	if (!count)
		return ;
	man->map_filenames = calloc(count + 1, sizeof(char *));
	if (!man->map_filenames || !populate_array(man))
		free_map_filenames(man);
	return ;
}

void	free_map_filenames(t_man *man)
{
	size_t	i;

	if (!man->map_filenames)
		return ;
	i = 0;
	while (man->map_filenames[i])
		free(man->map_filenames[i++]);
	free(man->map_filenames);
	man->map_filenames = 0;
	return ;
}

static int	populate_array(t_man *man)
{
	DIR				*dir;
	struct dirent	*entry;
	size_t			i;

	dir = opendir(MAP_DIR);
	if (!dir)
		return (0);
	i = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (is_map_file(entry->d_name))
		{
			man->map_filenames[i] = strjoin(MAP_DIR "/", entry->d_name);
			if (!man->map_filenames[i++])
				break ;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	if (i && !man->map_filenames[i - 1])
		return (0);
	sort_strings(man->map_filenames, strcmp);
	return (1);
}

static int	is_map_file(const char *name)
{
	char		*path;
	struct stat	st;
	int			is_map;

	if (name[0] == '.' || !has_extension(name, ".map"))
		return (0);
	path = strjoin(MAP_DIR "/", name);
	if (!path)
		return (0);
	is_map = !stat(path, &st) && S_ISREG(st.st_mode);
	free(path);
	return (is_map);
}

static void	sort_strings(char **arr, int (*cmp)(const char *, const char *))
{
	size_t	i;
	char	*tmp;
	int		swap_performed;

	if (!arr)
		return ;
	i = 0;
	swap_performed = 0;
	while (arr[i])
	{
		if (arr[i + 1] && cmp(arr[i], arr[i + 1]) > 0)
		{
			tmp = arr[i];
			arr[i] = arr[i + 1];
			arr[i + 1] = tmp;
			swap_performed = 1;
		}
		++i;
		if (swap_performed && !arr[i + 1])
		{
			swap_performed = 0;
			i = 0;
		}
	}
	return ;
}
