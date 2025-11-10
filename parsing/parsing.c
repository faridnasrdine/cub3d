#include "../cub3d.h"



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
    if(verify_first_last_walls(data->map->map))
        return (1);
    if(verify_line(data->map->map))
        return (1);
    if(check_player(data->map->map))
        return (1);
    if(init_location_player(data))
        return (1);
    return (0);
}