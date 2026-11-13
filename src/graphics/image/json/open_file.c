#include "grim_fetcher.h"

static char	**get_line_arr(const char *filepath, size_t *line_count);
static char	*trim_line(char *s);
static void	fill_lines(int fd, char **lines, size_t count);

char	**get_json_content(const char *filepath)
{
	size_t	count;
	int		fd;
	char	**lines;

	lines = get_line_arr(filepath, &count);
	if (!lines)
		return (0);
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
	{
		free(lines);
		return (0);
	}
	fill_lines(fd, lines, count);
	close(fd);
	return (lines);
}

void	free_json_content(char **content)
{
	size_t	i;

	if (!content)
		return ;
	i = 0;
	while (content[i])
	{
		free(content[i]);
		++i;
	}
	free(content);
	return ;
}

static char	**get_line_arr(const char *filepath, size_t *line_count)
{
	int		fd;
	char	*line;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return (0);
	*line_count = 0;
	line = gnl(fd);
	while (line)
	{
		++*line_count;
		free(line);
		line = gnl(fd);
	}
	close(fd);
	if (!*line_count)
		return (0);
	return (calloc(*line_count + 1, sizeof(char *)));
}

static char	*trim_line(char *s)
{
	size_t	whitespaces_len;
	size_t	len;

	if (!s)
		return (0);
	len = strlen(s);
	if (len && s[len - 1] == '\n')
		s[len - 1] = 0;
	whitespaces_len = 0;
	while (isspace(s[whitespaces_len]))
		++whitespaces_len;
	memmove(s, s + whitespaces_len, strlen(s + whitespaces_len) + 1);
	return (s);
}

static void	fill_lines(int fd, char **lines, size_t count)
{
	size_t	i;
	char	*line;

	i = 0;
	line = gnl(fd);
	while (line)
	{
		if (i < count)
			lines[i++] = trim_line(line);
		else
			free(line);
		line = gnl(fd);
	}
	return ;
}
