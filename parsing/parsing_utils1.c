#include "../cub3d.h"

static int get_line_len(char *line)
{
    int len = 0;
    int i = 0;
    
    while(line[i])
    {
        if(line[i] != ' ' && line[i] != '\t' && line[i] != '\r')
            len = i + 1;
        i++;
    }
    return (len);
}

int get_big_line(char **map)
{
    int max = 0;
    int i = 0;
    int len;
    
    if (!map)
        return (0);
        
    while(map[i])
    {
        len = get_line_len(map[i]);
        if(len > max)
            max = len;
        i++;
    }
    return (max);
}

int get_height_line(char **map)
{
    int map_height;

    map_height = 0;
    while (map[map_height])
        map_height++;
    return map_height;
}
