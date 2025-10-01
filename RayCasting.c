#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	int i;

	if (x < 0 || y < 0 || x >= data->map_length * 32 || y >= data->map_height * 32)
		return;
	i = y * data->len + x * (data->pixel / 8);
	data->addr[i] = color & 0xFF;
	data->addr[i + 1] = (color >> 8) & 0xFF;
	data->addr[i + 2] = (color >> 16) & 0xFF;
}

void	draw_block(t_data *data, int x, int y, int color)
{
	int	j;
	int	i;

	i = y;
	while (i < y + 32)
	{
		j = x;
		while (j < x + 32)
		{
			my_mlx_pixel_put(data, j, i, color);
			j++;
		}
		i++;
	}
}

void draw_player(char p, t_data *data, int color)
{
	int	j;
	int	i;

	i = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (j < data->map_length)
		{
			if (p != '1' && p != '0' && p != ' ')
			{
				for (int x = 0; x < 15; x++)
				{
					for (int y = 0; y < 15; y++)
					{
						my_mlx_pixel_put(data, x + (data->player->x * 32), (data->player->y * 32) + y, color);
					}
				}
			}
			j++;
		}
		i++;
	}
}

void get_draw_map(char p, int x, int y, t_data *data)
{
	int color;

	color = 0;
	if (p == '1')
		color = 0x0000FF;	
	else if (p == '0' || p == 'N')		
		color = 0xFFFFFF;
	draw_block(data, x, y, color);
	if (p == 'N' || p == 'S' || p == 'E' || p == 'W')
	{
		color = 0xFF0000;	
		draw_player(p, data, color);
	}
}
void    get_game(t_data *data)
{
	int x;
	int y;
	int i;
	int j;

	if (!data || !data->map || !data->map->map)
	{
		printf("Error: Invalid map data\n");
		return;
	}
	data->img = mlx_new_image(data->mlx, data->map_length * 32, data->map_height * 32);
	data->addr = mlx_get_data_addr(data->img, &data->pixel, &data->len, &data->endian);

	y = 0;
	i = 0;
	while(i < data->map_height)
	{
		x = 0;
		j = 0;
		while(j < data->map_length)
		{
			if (data->map->map[i][j] != '\0')
				get_draw_map(data->map->map[i][j], x, y, data);
			j++;
			x += 32;
		}
		i++;
		y += 32;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
int is_valid_position(t_data *data, double x, double y)
{
    int map_x = (int)x;
    int map_y = (int)y;
    
    if (map_x < 0 || map_x >= data->map_length || 
        map_y < 0 || map_y >= data->map_height)
        return (0);
    
    if (data->map->map[map_y][map_x] == '1')
        return (0);
    
    return (1);
}
void move_up(t_data *data)
{
    double new_x = data->player->x + data->player->dir_x * data->player->move_speed;
    double new_y = data->player->y + data->player->dir_y * data->player->move_speed;
    
    if (is_valid_position(data, new_x, data->player->y))
        data->player->x = new_x;
    if (is_valid_position(data, data->player->x, new_y))
        data->player->y = new_y;
}
void move_down(t_data *data)
{
	double new_x = data->player->x - data->player->dir_x * data->player->move_speed;
    double new_y = data->player->y - data->player->dir_y * data->player->move_speed;
    
    if (is_valid_position(data, new_x, data->player->y))
        data->player->x = new_x;
    if (is_valid_position(data, data->player->x, new_y))
        data->player->y = new_y;
	
}

void move_right(t_data *data)
{
    double new_x = data->player->x - data->player->dir_y * data->player->move_speed;
    double new_y = data->player->y + data->player->dir_x * data->player->move_speed;
    
    if (is_valid_position(data, new_x, data->player->y))
        data->player->x = new_x;
    if (is_valid_position(data, data->player->x, new_y))
        data->player->y = new_y;
}

void move_left(t_data *data)
{
	double new_x = data->player->x + data->player->dir_y * data->player->move_speed;
    double new_y = data->player->y - data->player->dir_x * data->player->move_speed;
    
    if (is_valid_position(data, new_x, data->player->y))
        data->player->x = new_x;
    if (is_valid_position(data, data->player->x, new_y))
        data->player->y = new_y;
	
}
int key_move(int keycode, t_data *data)
{
    if (keycode == 119)   
        move_up(data);
    else if (keycode == 115) 
        move_down(data);
    else if (keycode == 100) 
        move_right(data);
    else if (keycode == 97)  
        move_left(data);
    else if (keycode == 65307)
        exit(0);
    else
        return (0);
    get_game(data);
    
    return (0);
}
void	set_mlx(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->map_length * 32, data->map_height * 32, "CUB3D 42");
	get_game(data);
	mlx_hook(data->win, 2, 1L << 0, key_move, data);
	mlx_loop(data->mlx);
}