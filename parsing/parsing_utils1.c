#include "../cub3d.h"

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
                data->player.x = (double)j + 0.5;
                data->player.y = (double)i + 0.5;
        
                
                data->map_width = get_big_line(data->map->map);
                data->map_height = get_height_line(data->map->map);
                return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}

static int get_line_len(char *line)
{
    int len = 0;
    int i = 0;
    
    while(line[i] != '\0' && line[i] != '\n')
    {
        if(line[i] != ' ' && line[i] != '\t')
            len = i + 1;
        i++;
    }
    return (len);
}
char	*ft_strndup(char *s, int n)
{
	unsigned int	i;
	char			*ptr;

	i = 0;
	while (s[i] != '\0')
		i++;
	ptr = (char *)malloc((i - n + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[i + n] != '\0' && s[i + n] != '\n')
	{
		ptr[i] = s[i + n];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
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




