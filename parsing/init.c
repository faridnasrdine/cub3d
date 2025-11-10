#include "cub3d.h"

void  my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
  char *dst;

  int win_width = data->map_width * data->tile_size;
  int win_height = data->map_height * data->tile_size;

  if (y < 0 || y >= win_height || x < 0 || x >= win_width)
    return ;
  dst = data->addr + (y * data->line_length + x * (data->bits_per_pixels / 8));
  *(unsigned int*)dst = color;
}

void draw_square(t_data *data, int x, int y, int size, int color)
{
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      my_mlx_pixel_put(data, x + j, y + i, color);
    }
  }
}

void  draw_map(t_data *data)
{
  int i;
  int j;

  i = 0;
  while (i <  data->map_width * data->tile_size)
  {
    j = 0;
    while (j < data->map_height * data->tile_size)
    {
      my_mlx_pixel_put(data, i, j, 0x000000);
      j++;
    }
    i++;
  }

  i = 0;
  while (i < data->map_height)
  {
    j = 0;
    while (j < data->map_width)
    {
      int x = i * 64;
      int y = j * 64;

      if (data->map->map[i][j] == '1')
        draw_square(data, y, x, data->tile_size, 0xFF0000);
      // else {
      //   draw_square(data, x, y, data->tile_size, 0x00FF00);
      // }

      for (int k = 0; k < data->tile_size; k++)
      {
        my_mlx_pixel_put(data, y + k, x, 0xFFFF00);
        my_mlx_pixel_put(data, y, x + k, 0xFFFF00);
      }
      j++;
    }
    i++;
  }
  draw_player(data);
}


int check_collision(t_data *data, double new_x, double new_y)
{
  int map_x = (int)new_x;
  int map_y = (int)new_y;

  // Check boundaries
  if (map_x < 0 || map_x >= data->map_width || 
    map_y < 0 || map_y >= data->map_height)
    return (1); // Collision with boundary

  // Check if position is a wall
  if (data->map->map[map_y][map_x] == '1')
    return (1); // Collision with wall

  return (0); // No collision
}

int key_press(int keycode, t_data *data)
{
  double move_speed = 0.4;
  double new_x = data->player.x;
  double new_y = data->player.y;

  // === ROTATION (a/d + arrows) ===
  if (keycode == 'd' || keycode == 65363)  // D or Right arrow - rotate right
  {
    data->player.angle += ROT_SPEED;
    if (data->player.angle >= 2 * M_PI)
      data->player.angle -= 2 * M_PI;
    render_frame(data);
    return (0);
  }
  else if (keycode == 'a' || keycode == 65361)  // A or Left arrow - rotate left
  {
    data->player.angle -= ROT_SPEED;
    if (data->player.angle < 0)
      data->player.angle += 2 * M_PI;
    render_frame(data);
    return (0);
  }

  // === FORWARD/BACKWARD (w/s or k/j) ===
  else if (keycode == 'w' || keycode == 'k' || keycode == 65362)  // Forward (W/K/Up)
  {
    new_x += cos(data->player.angle) * move_speed; 
    new_y += sin(data->player.angle) * move_speed;
  }
  else if (keycode == 's' || keycode == 'j' || keycode == 65364)  // Backward (S/J/Down)
  {
    new_x -= cos(data->player.angle) * move_speed;
    new_y -= sin(data->player.angle) * move_speed;
  }

  else if (keycode == 'h')  
  {
    new_x += cos(data->player.angle - M_PI/2) * move_speed;
    new_y += sin(data->player.angle - M_PI/2) * move_speed;
  }
  else if (keycode == 'l')
  {
    new_x += cos(data->player.angle + M_PI/2) * move_speed;
    new_y += sin(data->player.angle + M_PI/2) * move_speed;
  }

  // === EXIT ===
  else if (keycode == 65307)  // ESC
  {
    mlx_destroy_window(data->mlx, data->win);
    exit(0);
  }

  // Apply movement if no collision
  if (!check_collision(data, new_x, new_y))
  {
    data->player.x = new_x;
    data->player.y = new_y;
    render_frame(data);
  }

  return (0);
}

void draw_player(t_data *data)
{
  int player_screen_x = (int)(data->player.x * data->tile_size);
  int player_screen_y = (int)(data->player.y * data->tile_size);
  int player_size = data->tile_size / 3; 

  draw_fov_with_walls(data);
  for (int i = -player_size/2; i < player_size/2; i++)
  {
    for (int j = -player_size/2; j < player_size/2; j++)
    {
      my_mlx_pixel_put(data, player_screen_x + j, player_screen_y + i, 0xFF0270); 
    }
  }
}

void init_mlx(t_data *data)
{
  data->mlx = mlx_init();
  int size = data->tile_size = 64;
  int window_width = data->map_width * size;
  int window_height = data->map_height * size;
  data->win = mlx_new_window(data->mlx, window_width, window_height, "Hicham el fatihi");
  data->img = mlx_new_image(data->mlx, window_width, window_height);
  data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixels, &data->line_length, &data->endian);
}

