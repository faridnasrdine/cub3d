#include "../cub3d.h"

void update_walls(char *line, char *first_wall, char *last_wall, size_t line_number)
{
    size_t i = 0;
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
    size_t big_line;
    char *first_wall;
    char *last_wall;
    int i = 0;
    int ret;

    big_line = get_big_line(map);
    first_wall = ft_calloc(big_line + 1, sizeof(char));
    last_wall = ft_calloc(big_line + 1, sizeof(char));
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
        last = strlen(map[i]) - 1;
        while(last >= 0 && (map[i][last] == ' ' || map[i][last] == '\t' || map[i][last] == '\n'))
            last--;
        if(last < 0 || map[i][last] != '1')
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
            if(ft_strchr(player, map[i][j]))
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
int init_location_player(t_data *data)
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
                data->player->x = (double)j + 0.5;  // Center of the cell
                data->player->y = (double)i + 0.5;
                data->player->orientation = data->map->map[i][j];
                
                // Set direction vectors based on orientation
                if (data->map->map[i][j] == 'N')
                {
                    data->player->dir_x = 0;
                    data->player->dir_y = -1;
                }
                else if (data->map->map[i][j] == 'S')
                {
                    data->player->dir_x = 0;
                    data->player->dir_y = 1;
                }
                else if (data->map->map[i][j] == 'E')
                {
                    data->player->dir_x = 1;
                    data->player->dir_y = 0;
                }
                else if (data->map->map[i][j] == 'W')
                {
                    data->player->dir_x = -1;
                    data->player->dir_y = 0;
                }
                
                data->player->move_speed = 0.1;
                data->player->rot_speed = 0.05;
                
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
    return (c == '0' || c == '1');
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
            if (map[i][j] == '0') {
                if (check_next(map, i, j))
                    return 1;
            }
            j++;
        }
        i++;
    }
    return 0;
}

// int validate_map_closed(t_data *data)
// {
//     if (data->x < 0 || data->x >= data->map_length ||
//         data->y < 0 || data->y >= data->map_height)
//         return (1);    
//     char player_tile = data->map->map[data->y][data->x];
//     if (player_tile != '0' && player_tile != 'N' && player_tile != 'S' && 
//         player_tile != 'E' && player_tile != 'W')
//         return (1);    
//     return (flood_fill_timed(data));
// }

// int check_door(char **map)
// {
//     int i;
//     int j;

//     i = 0;
//     while(map[i])
//     {
//         j = 0;
//         while(map[i][j])
//         {
//             if(map[i][j] == '2')
//             {
//                 if(fun(map))
//             }
//         }
//     }
// }


void funn(char **map)
{
    int i;
    int j;

    i = 0;
    while(map[i])
    {
        j = 0;
        while(map[i][j])
        {
            if(map[i][j] == '\t' || map[i][j] == ' ')
                map[i][j] = '1';
            j++;
        }
        i++;
    }
}
int parsing(t_data *data)
{
    // if(verify_first_last_walls(data->map->map))
    //     return (1);
    if(verify_line(data->map->map))
        return (1);
    if(check_player(data->map->map))
        return (1);
    if(init_location_player(data))
        return (1);
    // if (verify_map(data->map->map))
    //     return 1;
    funn(data->map->map);
    for(int i = 0; data->map->map[i]; i++)
    {
        printf("%s", data->map->map[i]);
    }
    // exit(1);
    return (0);
}