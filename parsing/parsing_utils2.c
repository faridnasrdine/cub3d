#include "../cub3d.h"
void	flag(int *flags)
{
	ssize_t	i;

	i = 0;
	while (i < 10)
		flags[i++] = 0;
}
ssize_t	find_char(const char *str, char c, ssize_t len)
{
	ssize_t	i;
	ssize_t	found;

	i = 0;
	found = 0;
	while (i < len)
	{
		if (str[i] == c)
			found++;
		i++;
	}
	return (found);
}
int	loop_help(t_data *data, char *str, int *flags)
{
	int	res;

	res = 0;
	if (!str)
		return (1);
	if (str[0] == '\n')
	{
		free(str);
		return (2);
	}
	res = attr_check(data, str, flags);
	if (res == 1)
	{
		free(str);
		return (1);
	}
	else if (res == 2)
		return (2);
	else
		return (0);
}
ssize_t	get_file_lines(char **argv)
{
	int		fd;
	char	*str;
	ssize_t	bytes_read;
	ssize_t	lines;

	fd = open(argv[1], O_RDONLY);
	str = malloc(BUFFER_SIZE + 1);
	lines = 0;
	while (str)
	{
		bytes_read = read(fd, str, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		str[bytes_read] = '\0';
		lines += find_char(str, '\n', bytes_read);
	}
	lines++;
	free(str);
	close(fd);
	return (lines + 1);
}
void	map_setter(t_data *data, ssize_t j, char **map)
{
	ssize_t	i;

	i = 0;
	data->map->map = malloc(sizeof(char *) * (j + 1));
	while (map[i])
	{
		data->map->map[i] = ft_strdup(map[i]);
		free(map[i]);
		i++;
	}
	free(map);
	data->map->map[i] = NULL;
}
int	get_textures(t_data *data, char **argv)
{
	char	*str;
	char	**map;
	ssize_t	i;
	int		flags[10];
	int		help;

	i = 0;
	help = 0;
	str = "";
	map = malloc(sizeof(char *) * get_file_lines(argv));
	flag(flags);
	while (str)
	{
		str = get_next_line(data->map->fd);
		help = loop_help(data, str, flags);
		if (help == 1)
			break ;
		else if (help == 2)
			continue ;
		map[i++] = ft_strndup(str, 0);
		free(str);
	}
	map[i] = NULL;
	map_setter(data, i, map);
	return (check_flag(flags));
}