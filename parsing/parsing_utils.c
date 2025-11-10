#include "../cub3d.h"

static int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

static int	is_empty_line(const char *s)
{
	int i = 0;
	if (!s) return 1;
	while (s[i] && (is_space(s[i]) || s[i] == '\n' || s[i] == '\r'))
		i++;
	return (s[i] == '\0');
}

static int	is_wall_line(const char *s)
{
	int i = 0;
	if (!s) return 0;
	while (s[i])
	{
		if (s[i] == '\n' || s[i] == '\r' || is_space(s[i]))
		{
			i++;
			continue;
		}
		if (s[i] != '1')
			return 0; 
		i++;
	}
	return 1;
}

int	verify_first_last_walls(char **map)
{
	int top = 0;
	int bottom;

	if (!map) return 1;

	while (map[top] && is_empty_line(map[top]))
		top++;
	if (!map[top]) 
		return 1;

	bottom = top;
	while (map[bottom])
		bottom++;
	bottom--;                      
	while (bottom > top && is_empty_line(map[bottom]))
		bottom--;
	if (!is_wall_line(map[top]))
		return 1;
	if (!is_wall_line(map[bottom]))
		return 1;

	return 0;
}

int verify_line(char **map)
{
    int i;
    int j;
    int last;

    i = 0;
    while(map[i])
    {
        j = 0;
        while(map[i][j] == ' ' || map[i][j] == '\t')
            j++;
        if(map[i][j] == '\0')
        {
            i++;
            continue;
        }
        if(map[i][j] != '1')
            return (1);
        last = ft_strlen(map[i]) - 1;
        while(last >= 0 && (map[i][last] == ' ' || map[i][last] == '\t' || map[i][last] == '\n'))
            last--;
        if(last < 0 || map[i][last] != '1')
            return (1);
        i++;
    }
    return (0);
}

