#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->len + x * (data->pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_block(t_data *data, int start_x, int start_y, int color)
{
	int	x;
	int	y;

	y = start_y;
	while (y < start_y + 32)
	{
		x = start_x;
		while (x < start_x + 32)
		{
			my_mlx_pixel_put(data, x, y, color);
			x++;
		}
		y++;
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

	data->img = mlx_new_image(data->mlx, data->map_height * 32, data->map_length * 32);
	data->addr = mlx_get_data_addr(data->img, &data->pixel, &data->len, &data->endian);

	y = 0;
	i = 0;
	while(i < data->map_length)
	{
		x = 0;
		j = 0;
		while(j < data->map_height)
		{
			get_draw_map(data->map->map[i][j], x, y, data);
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
	data->win = mlx_new_window(data->mlx, 800, 800, "CUB3D 42");
	// get_game(data);
	mlx_loop(data->mlx);
}