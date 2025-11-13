#include "../cub3d.h"


void int_fill(t_data *data, char *av)
{
    int fd;

    fd = open(av, O_RDONLY);
    if(fd < 0)
    {
        return;
    }
    data->map->fd = fd;
}

int init_data(t_data *data)
{
    data->map = malloc(sizeof(t_map));
    if (!data->map)
        return -1;
    data->map->north = malloc(sizeof(t_texture));
    data->map->south = malloc(sizeof(t_texture));
    data->map->west = malloc(sizeof(t_texture));
    data->map->east = malloc(sizeof(t_texture));
    
    if (!data->map->north || !data->map->south || !data->map->west || 
        !data->map->east)
    {
       //cleanup function!!!!!!!!!!!!!!!
        return -1;
    }
    data->map->floor = 0;
    data->map->celling = 0;
    data->map->map = NULL;
    data->map->fd = -1;
    data->player.x = 0.0;
    data->player.y = 0.0;
    
    return 0;
}

