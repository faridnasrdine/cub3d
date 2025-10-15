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

void draw_line(t_data *data, int c_x, int c_y, int line_end_x, int line_end_y, int color)
{
	int dx = line_end_x - c_x;
	int dy = line_end_y - c_y;
	int steps;
	float x_inc;
	float y_inc;
	float x;
	float y;
	int i;

	if (dx < 0)
		dx = -dx;
	if (dy < 0)
		dy = -dy;
	
	steps = dx;
	if (dy > dx)
		steps = dy;

	x_inc = (float)(line_end_x - c_x) / (float)steps;
	y_inc = (float)(line_end_y - c_y) / (float)steps;

	x = c_x;
	y = c_y;
	i = 0;
	while (i <= steps)
	{
		my_mlx_pixel_put(data, (int)x, (int)y, color);
		x += x_inc;
		y += y_inc;
		i++;
	}
}

void draw_player_on_map(t_data *data)
{
	int player_center_x;
	int player_center_y;
	int line_end_x;
	int line_end_y;
	double line_length;
	int x;
	int y;

	x = 0;
	while (x < 15)
	{
		y = 0;
		while (y < 15)
		{
			my_mlx_pixel_put(data, 
				x + (int)(data->player->x * 32), 
				(int)(data->player->y * 32) + y, 
				0xFF0000);
			y++;
		}
		x++;
	}

	player_center_x = (int)(data->player->x * 32) + 7;
	player_center_y = (int)(data->player->y * 32) + 7;
	line_length = 100.0;
	line_end_x = player_center_x + (int)(data->player->dir_x * line_length);
	line_end_y = player_center_y + (int)(data->player->dir_y * line_length);
	draw_line(data, player_center_x, player_center_y, 
			 line_end_x, line_end_y, 0xFF0000);
}

void get_draw_map(char p, int x, int y, t_data *data)
{
	int color;

	color = 0;
	if (p == '1')
		color = 0x0000FF;	
	else
		color = 0xFFFFFF;
	draw_block(data, x, y, color);
}

void clean_player_from_map(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (j < data->map_length)
		{
			if (data->map->map[i][j] == 'N' || 
				data->map->map[i][j] == 'S' ||
				data->map->map[i][j] == 'E' || 
				data->map->map[i][j] == 'W')
			{
				data->map->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}

void get_game(t_data *data)
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
	clean_player_from_map(data);
	
	// Destroy old image if it exists
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	
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
	draw_player_on_map(data);
	cub_raycast(data);
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
	
	if (is_valid_position(data, new_x, data->player->y) == 1)
		data->player->x = new_x;
	if (is_valid_position(data, data->player->x, new_y) == 1)
		data->player->y = new_y;
}

void move_down(t_data *data)
{
	double new_x;
	double new_y;

	new_x = data->player->x - data->player->dir_x * data->player->move_speed;
	new_y = data->player->y - data->player->dir_y * data->player->move_speed;
	
	if (is_valid_position(data, new_x, data->player->y) == 1)
		data->player->x = new_x;
	if (is_valid_position(data, data->player->x, new_y) == 1)
		data->player->y = new_y;
}

void move_right(t_data *data)
{
	double new_x;
	double new_y;

	new_x = data->player->x - data->player->dir_y * data->player->move_speed;
	new_y = data->player->y + data->player->dir_x * data->player->move_speed;
	
	if (is_valid_position(data, new_x, data->player->y))
		data->player->x = new_x;
	if (is_valid_position(data, data->player->x, new_y))
		data->player->y = new_y;
}

void move_left(t_data *data)
{
	double new_x;
	double new_y;

	new_x = data->player->x + data->player->dir_y * data->player->move_speed;
	new_y = data->player->y - data->player->dir_x * data->player->move_speed;
	
	if (is_valid_position(data, new_x, data->player->y))
		data->player->x = new_x;
	if (is_valid_position(data, data->player->x, new_y))
		data->player->y = new_y;
}

void rotate_left(t_data *data)
{
	double old_dir_x;
	double rot;

	old_dir_x = data->player->dir_x;
	rot = data->player->rot_speed;
	
	data->player->dir_x = data->player->dir_x * cos(rot) - data->player->dir_y * sin(rot);
	data->player->dir_y = old_dir_x * sin(rot) + data->player->dir_y * cos(rot);
}

void rotate_right(t_data *data)
{
	double old_dir_x;
	double rot;

	old_dir_x = data->player->dir_x;
	rot = -data->player->rot_speed;
	
	data->player->dir_x = data->player->dir_x * cos(rot) - data->player->dir_y * sin(rot);
	data->player->dir_y = old_dir_x * sin(rot) + data->player->dir_y * cos(rot);
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
	else if (keycode == 65361)
		rotate_right(data);
	else if (keycode == 65363)
		rotate_left(data);
	else if (keycode == 65307)
		exit(0);
	else
		return (0);
	// get_game(data);

	render_3d_view(data);
	
	return (0);
}

void init_ray(t_data *g)
{
	g->ray.hfov = 60.0;
	g->ray.incre_angle = g->ray.hfov / (g->map_length * 32);
	g->ray.precision = 64;
	g->ray.max_depth = 20.0;
}

float degree_to_radians(float degree)
{
	return (degree * M_PI / 180.0);
}

float get_angle_from_direction(double dir_x, double dir_y)
{
	return atan2(dir_y, dir_x);
}

float distance_to_wall(t_data *g, float ray_angle)
{
	float x = g->player->x;
	float y = g->player->y;
	float ray_cos = cos(ray_angle) / g->ray.precision;
	float ray_sin = sin(ray_angle) / g->ray.precision;
	float distance = 0;
	int map_x;
	int map_y;

	while (distance < g->ray.max_depth)
	{
		x += ray_cos;
		y += ray_sin;
		distance += 1.0 / g->ray.precision;
		
		map_x = (int)x;
		map_y = (int)y;
		
		if (map_x < 0 || map_x >= g->map_length || 
			map_y < 0 || map_y >= g->map_height)
			return (g->ray.max_depth);
			
		if (g->map->map[map_y][map_x] == '1')
			return (distance);
	}
	
	return (g->ray.max_depth);
}

void draw_ceiling_floor(t_data *g)
{
	int x, y;
	int screen_width = g->map_length * 32;
	int screen_height = g->map_height * 32;
	int ceiling_color = 0x87CEEB;
	int floor_color = 0x8B7355;

	y = 0;
	while (y < screen_height / 2)
	{
		x = 0;
		while (x < screen_width)
		{
			my_mlx_pixel_put(g, x, y, ceiling_color);
			x++;
		}
		y++;
	}
	while (y < screen_height)
	{
		x = 0;
		while (x < screen_width)
		{
			my_mlx_pixel_put(g, x, y, floor_color);
			x++;
		}
		y++;
	}
}

void cub_draw(t_data *g, int ray_count, float dist)
{
	int line_height;
	int start;
	int end;
	int color;
	int screen_height = g->map_height * 32;

	if (dist < 0.01)
		dist = 0.01;

	line_height = (int)(screen_height / dist);
	start = screen_height / 2 - line_height / 2;
	end = screen_height / 2 + line_height / 2;

	if (start < 0)
		start = 0;
	if (end > screen_height)
		end = screen_height;

	int brightness = 255 - (int)(dist * 12);
	if (brightness < 0)
		brightness = 0;
	if (brightness > 255)
		brightness = 255;
	
	color = (brightness << 16) | (brightness << 8) | brightness;

	for (int y = start; y < end; y++)
		my_mlx_pixel_put(g, ray_count, y, color);
}

void cub_raycast(t_data *g)
{
	float player_angle;
	float ray_angle;
	int screen_width = g->map_length * 32;
	int ray_count = 0;
	float dist;
	float angle_offset;

	player_angle = get_angle_from_direction(g->player->dir_x, g->player->dir_y);
	
	ray_angle = player_angle - degree_to_radians(g->ray.hfov / 2.0);
	
	while (ray_count < screen_width)
	{
		dist = distance_to_wall(g, ray_angle);
		
		angle_offset = ray_angle - player_angle;
		dist = dist * cos(angle_offset);
		cub_draw(g, ray_count, dist);
		ray_angle += degree_to_radians(g->ray.incre_angle);
		ray_count++;
	}
}

void render_3d_view(t_data *data)
{
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	
	data->img = mlx_new_image(data->mlx, data->map_length * 32, data->map_height * 32);
	data->addr = mlx_get_data_addr(data->img, &data->pixel, &data->len, &data->endian);
	
	draw_ceiling_floor(data);
	
	cub_raycast(data);
	
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void set_mlx(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->map_length * 32, data->map_height * 32, "CUB3D 42");
	init_ray(data);
	render_3d_view(data);
	mlx_hook(data->win, 2, 1L << 0, key_move, data);
	mlx_loop(data->mlx);
}
