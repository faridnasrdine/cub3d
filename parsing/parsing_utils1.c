#include "../cub3d.h"

static int get_line_len(char *line)
{
    int len = 0;
    int i = 0;
    while(line[i])
    {
        if(line[i] != ' ' && line[i] != '\t')
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
   while(map[i])
   {
        len = get_line_len(map[i]);
        if(len > max)
            max = len;
        i++;
   }
   return (max);
}