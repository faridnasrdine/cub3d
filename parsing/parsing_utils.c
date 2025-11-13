#include "../cub3d.h"

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	normalize_spaces(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ' || map[i][j] == '\t')
				map[i][j] = '1';
			j++;
		}
		i++;
	}
}

int	line_last_visible(const char *s)
{
	int	i;
	int	last;

	i = 0;
	last = -1;
	while (s[i] && s[i] != '\n')
	{
		if (s[i] != ' ' && s[i] != '\t')
			last = i;
		i++;
	}
	return (last);
}

int	line_first_visible(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	if (!s[i] || s[i] == '\n')
		return (-1);
	return (i);
}

int	is_wall_line(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
	{
		if (s[i] != '1' && s[i] != ' ' && s[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

