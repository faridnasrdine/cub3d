#include "../cub3d.h"


int is_allowd(char c)
{
	if(c == '1' || c == '0')
		return (1);
	if(is_player(c))
		return (1);
	if(c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}
int verify_chars(char **map)
{
	int i = 0;
	int j;

	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if(!is_allowd(map[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
char    *add_walls(char *s, int w)
{
    char    *new;
    int     i;

    new = malloc(w + 1);
    if (!new)
        return (NULL);
    i = 0;
    while (s[i] && s[i] != '\n')
    {
        new[i] = s[i];
        i++;
    }
    while (i < w)
    {
        new[i] = '1';
        i++;
    }
    new[w] = '\0';
    return (new);
}

int pad_map_right(char **map, int w)
{
    int     i;
    char    *new;

    i = 0;
    while (map[i])
    {
        new = add_walls(map[i], w);
        if (!new)
            return (1);
        free(map[i]);
        map[i] = new;
        i++;
    }
    return (0);
}

int	parsing(t_data *data)
{
	int	h;
	int	w;

	if (!data || !data->map || !data->map->map)
		return (1);
	if (verify_chars(data->map->map))
		return (1);
	normalize_spaces(data->map->map);
	if (verify_top_bottom(data->map->map))
		return (1);
	if (verify_left_right_walls(data->map->map))
		return (1);
	if (scan_player_and_dims(data->map->map, data, &h, &w))
		return (1);
	if(pad_map_right(data->map->map, w))
		return (1);
	data->map_width = w;
	data->map_height = h;
	return (0);
}