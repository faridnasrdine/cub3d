#include "cub3d.h"

void draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
  int dx = abs(x1 - x0);
  int dy = abs(y1 - y0);
  int sx = x0 < x1 ? 1 : -1;
  int sy = y0 < y1 ? 1 : -1;
  int err = dx - dy;

  while (1)
  {
    my_mlx_pixel_put(data, x0, y0, color);

    if (x0 == x1 && y0 == y1)
      break;

    int e2 = 2 * err;
    if (e2 > -dy)
    {
      err -= dy;
      x0 += sx;
    }
    if (e2 < dx)
    {
      err += dx;
      y0 += sy;
    }
  }
}

// Draw direction line showing where player is facing
void draw_direction_line(t_data *data)
{
  int player_screen_x = (int)(data->player.x * data->tile_size);
  int player_screen_y = (int)(data->player.y * data->tile_size);

  // Calculate end point of direction line
  
  // int line_length = data->tile_size;  // Length of direction indicator
  int end_x = player_screen_x + (int)(cos(data->player.angle) * 60);
  int end_y = player_screen_y + (int)(sin(data->player.angle) * 60);

  // Draw the direction line
  draw_line(data, player_screen_x, player_screen_y, end_x, end_y, 0x00FF00);
}
