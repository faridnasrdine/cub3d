#include "../cub3d.h"

void update_walls(char *line, char *first_wall, char *last_wall, int line_number)
{
    int i = 0;
    while(i < line_number)
    {
        if(i < ft_strlen(line) && line[i])
        {
            if((!first_wall[i] && line[i] != ' ' && line[i] != '\t') || (first_wall[i] == ' ' || first_wall[i] == '\t'))
                first_wall[i] = line[i];
            if(line[i] != ' ' && line[i] != '\t')
                last_wall[i] = line[i];
        }
        i++;
    }
}



int check_walls(char *walls)
{
	size_t	i;

	i = 0;
	while (walls[i] == ' ' || walls[i] == '\t')
		i++;
	if (walls[i] == '\0')
	{
		free(walls);
		return (1);
	}
	while (walls[i])
	{
		if (walls[i] != '1')
		{
			free(walls);
			return (1);
		}
		i++;
	}
	free(walls);
	return (0);
}


int verify_first_last_walls(char **map)
{
    int big_line;
    char *first_wall;
    char *last_wall;
    int i = 0;
    int ret;

    big_line = get_big_line(map);
    first_wall = calloc(big_line + 1, sizeof(char));
    last_wall = calloc(big_line + 1, sizeof(char));
    while(map[i])
        update_walls(map[i++], first_wall, last_wall, big_line);
    first_wall[big_line] = '\0';
    last_wall[big_line] = '\0';
    ret = 0;
    if(check_walls(first_wall) == 1)
        ret = 1;
    if(check_walls(last_wall) == 1)
        ret = 1;
    return (ret);
}

int check_last(char *map)
{
    int i;

    i = 0;
    while(map[i])
        i++;
    if(i > 0)
        i--;
    while(i >= 0 && (map[i] == ' '  || map[i] == '\t'))
        i--;
    if(i < 0 || map[i] != '1')
        return (1);
    return (0);
}

int verify_line(char **map)
{
    int i;
    int j;

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
        if(map[i][j] != '1' || check_last(map[i]) == 1)
            return (1);
        i++;
    }
    return (0);
}
int check_player(char **map)
{
    int i;
    int j;
    int player_count;
    char player[4];

    i = 0;
    player_count = 0;
    player[0] = 'N';
    player[1] = 'S';
    player[2] = 'E';
    player[3] = 'W';
    while(map[i])
    {
        j = 0;
        while(map[i][j])
        {
            if(strchr(player, map[i][j]))
                player_count++;
            j++;
        }
        if(player_count > 1)
            return (1);
        i++;
    }
    if(player_count == 0)
        return (1);
    return (0);
}
int find_spawn(t_data *data)
{
    int i;
    int j;

    i = 0;
    while(data->map->map[i])
    {
        j = 0;
        while(data->map->map[i][j])
        {
            if(data->map->map[i][j] == 'N' || data->map->map[i][j] == 'S' || 
               data->map->map[i][j] == 'E' || data->map->map[i][j] == 'W')
            {
                data->player->x = j + 0.5;
                data->player->y = i + 0.5;
                data->x = i;
                data->y = j;
                data->player->dir = data->map->map[i][j];
                data->map->map[i][j] = '0';
                data->map_length = get_big_line(data->map->map);
                data->map_height = get_height_line(data->map->map);
                return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}

int is_valid_tile(char c) 
{
    return (c == '0' || c == '1' || c == '2');
}

int check_next(char **map, int i, int j) {
    if (map[i + 1] && map[i + 1][j] && !is_valid_tile(map[i + 1][j]))
        return 1;
    if (i > 0 && map[i - 1][j] && !is_valid_tile(map[i - 1][j]))
        return 1;
    if (map[i][j + 1] && !is_valid_tile(map[i][j + 1]))
        return 1;
    if (j > 0 && map[i][j - 1] && !is_valid_tile(map[i][j - 1]))
        return 1;
    return 0;
}

int verify_map(char **map) {
    int i = 0;
    int j;

    while (map[i]) {
        j = 0;
        while (map[i][j]) {
            if (map[i][j] == '0' || map[i][j] == '2') {
                if (check_next(map, i, j))
                    return 1;
            }
            j++;
        }
        i++;
    }
    return 0;
}

// Global variable to track if map has errors
int g_map_error = 0;

void flood_fill(t_data *data, int x, int y, char **map_copy) 
{
    if (x < 0 || x >= data->map_length || y < 0 || y >= data->map_height)
        return;    
    if (map_copy[y][x] == 'S' || map_copy[y][x] == '1')
        return;    
    if (map_copy[y][x] == ' ' || map_copy[y][x] == '\t' || map_copy[y][x] == '\0')
    {
        g_map_error = 1;
        return;
    }
    map_copy[y][x] = 'S';
    flood_fill(data, x + 1, y, map_copy);
    flood_fill(data, x - 1, y, map_copy);
    flood_fill(data, x, y + 1, map_copy);
    flood_fill(data, x, y - 1, map_copy);
}

int flood_fill_timed(t_data *data)
{
    int i;
    char **map_copy;

    i = 0;
    g_map_error = 0;    
    map_copy = malloc(sizeof(char *) * (data->map_height + 1));
    if (!map_copy)
        return (1);    
    map_copy[data->map_height] = NULL;    
    while (i < data->map_height)
    {
        map_copy[i] = ft_strdup(data->map->map[i]);
        if (!map_copy[i])
        {
            while (--i >= 0)
                free(map_copy[i]);
            free(map_copy);
            return (1);
        }
        i++;
    }    
    flood_fill(data, data->x, data->y, map_copy);    
    int is_valid = !g_map_error;    
    i = 0;
    while (i < data->map_height)
    {
        free(map_copy[i]);
        i++;
    }
    free(map_copy);    
    return (!is_valid);
}

int validate_map_closed(t_data *data)
{
    if (data->x < 0 || data->x >= data->map_length ||
        data->y < 0 || data->y >= data->map_height)
        return (1);    
    char player_tile = data->map->map[data->y][data->x];
    if (player_tile != '0' && player_tile != 'N' && player_tile != 'S' && 
        player_tile != 'E' && player_tile != 'W')
        return (1);    
    return (flood_fill_timed(data));
}
int parsing(t_data *data)
{
    if(verify_first_last_walls(data->map->map))
        return (1);
    if(verify_line(data->map->map))
        return (1);
    if(check_player(data->map->map))
        return (1);
    if(find_spawn(data))
        return (1);
    if (verify_map(data->map->map))
        return 1;
    if (flood_fill_timed(data))
        return 1;
    return (0);
}