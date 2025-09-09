#include "../cub3d.h"

void update_walls(char *line, char *upper_wall, char *lower_wall, int line_number)
{
    int i = 0;
    while(i < line_number)
    {
        if((!upper_wall[i] && line[i] != ' ' && line[i] != '\t') || (upper_wall[i] == ' ' || upper_wall[i] == '\t'))
            upper_wall[i] = line[i];
        if(line[i] != ' ' && line[i] != '\t')
            lower_wall[i] = line[i];
        i++;
    }
}

int check_walls(char *line)
{
    int i = 0;
    while(line[i] == ' ' || line[i] == '\t')
        i++;
    if(line[i] == '\0')
    {
        free(line);
        return (1);
    }
    while(line[i])
    {
        if (line[i] != '1')
        {
            free(line);
            return (1);
        }
        i++;
    }
    free(line);
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
        update_walls(map[i++], upper_wall, lower_wall, big_line);
        upper_wall[big_line] = '\0';
        lower_wall[big_line] = '\0';
        ret = 0;
        if(check_walls(upper_wall) || check_walls(lower_wall))
            ret = 1;
    }
    return (ret);
}

int parsing(t_data *data)
{
    if(verify_upper_lower_walls(data->map))
        return (1);
    return (0);
}