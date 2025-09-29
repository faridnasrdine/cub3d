#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->len + x * (data->pixel / 8));
	*(unsigned int*)dst = color;
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

void get_draw_map(char p, int x, int y, t_data *data)
{
	int color;

	color = 0;
	if (p == '1')
		color = 0x0000FF;	
	else if (p == '0')		
		color = 0xFFFFFF;	
	else if (p == 'N' || p == 'S' || p == 'E' || p == 'W')
		color = 0xFF0000;	
	else if (p == ' ')
		color = 0x808080;
	draw_block(data, x, y, color);
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
		if (!data->map->map[i])
		{
			printf("Error: Row %d is NULL\n", i);
			i++;
			y += 32;
			continue;
		}
		
		x = 0;
		j = 0;
		while(j < data->map_length)
		{
			if (data->map->map[i][j] != '\0')
				get_draw_map(data->map->map[i][j], x, y, data);
			else
				draw_block(data, x, y, 0x808080);
			j++;
			x += 32;
		}
		i++;
		y += 32;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void	set_mlx(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->map_length * 32, data->map_height * 32, "CUB3D 42");
	get_game(data);
	mlx_loop(data->mlx);
}