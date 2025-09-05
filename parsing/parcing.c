#include "../cub3d.h"

int get_big_line(char **map)
{
    int max_length = 0;
    int i = 0;
    int line_length;
    while (i < data->map_height)
    {
        line_length = strlen(map[i]);
        if (line_length > max_length)
            max_length = line_length;
        i++;
    }
    return (max_length);
}
void update_upper_wall(char *upper_wall, char *map_line, int line_number)
{
    int i = 0;
    while (map_line[i])
    {
        if (line_number == 0)
            upper_wall[i] = map_line[i];
        i++;
    }
    upper_wall[i] = '\0';
}
void update_lower_wall(char *lower_wall, char *map_line, int line_number)
{
    int i = 0;
    while (map_line[i])
    {
        if (line_number == data->map_height - 1)
            lower_wall[i] = map_line[i];
        i++;
    }
    lower_wall[i] = '\0';
}

int check_walls(char *wall)
{
    int i = 0;
    while (wall[i])
    {
        if (wall[i] != '1' && wall[i] != ' ')
            return (1);
        i++;
    }
    return (0);
}

static int verify_upper_lower_walls(char **map)
{
    int big_line;
    char *upper_wall;
    char *lower_wall;
    int i = 0;
    int ret;

    big_line = get_big_line(map);
    upper_wall = malloc(sizeof(char) * (big_line + 1));
    lower_wall = malloc(sizeof(char) * (big_line + 1));
    while(map[i])
    {
        update_upper_wall(upper_wall, map[i], i);
        update_lower_wall(lower_wall, map[i], i);
        upper_wall[i] = '\0';
        lower_wall[i] = '\0';
        ret = 0;
        if(check_walls(upper_wall) || check_walls(lower_wall))
            ret = 1;
        i++;
    }
    return (ret);
}

int parsing(t_data *data)
{
    if(verify_upper_lower_walls(data->map))
        return (1);
    return (0);
}