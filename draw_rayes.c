
#include "cub3d.h"


void cast_ray_to_wall(t_data *data, double ray_angle, int color)
{
  int player_screen_x = (int)(data->player.x * data->tile_size);
  int player_screen_y = (int)(data->player.y * data->tile_size);
  
  // Ray starting position (in map coordinates)
  double ray_x = data->player.x;
  double ray_y = data->player.y;
  
  // Ray direction
  double ray_dir_x = cos(ray_angle);
  double ray_dir_y = sin(ray_angle);
  
  // Step size (how much to move per iteration)
  double step = 0.01;  // Smaller = more accurate but slower
  
  // Cast the ray until it hits a wall
  // int max_steps = 1000;  // Prevent infinite loops
  // for (int i = 0; i < max_steps; i++)
  while(1)
  {
    // Move ray forward
    ray_x += ray_dir_x * step;
    ray_y += ray_dir_y * step;
    
    // Check if ray is out of bounds
    if (ray_x < 0 || ray_x >= data->map_width || 
        ray_y < 0 || ray_y >= data->map_height)
      break;
    
    // Check if ray hit a wall
    if (data->map->map[(int)ray_y][(int)ray_x] == '1')
      break;
  }
  
  // Draw line from player to hit point
  int end_x = (int)(ray_x * data->tile_size);
  int end_y = (int)(ray_y * data->tile_size);
  draw_line(data, player_screen_x, player_screen_y, end_x, end_y, color);
}

void draw_fov_with_walls(t_data *data)
{
  printf("var = %f\n", data->player.angle);
  double start_angle = data->player.angle - (FOV / 2);
  double angle_step = FOV / NUM_RAYS;
  int color;

  for (int i = 0; i < NUM_RAYS; i++)
  {
    double ray_angle = start_angle + (i * angle_step);
    
    // Different colors for better visualization
    if (i <= NUM_RAYS / 2) {
      color = 0x004400;
    }
    else {
      color = 0xF0FFFF;
    }
    cast_ray_to_wall(data, ray_angle, color);
  }
}
