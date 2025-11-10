
#include "cub3d.h"

// void draw_fov(t_data *data)
// {
//   int player_screen_x = (int)(data->player.x * data->tile_size);
//   int player_screen_y = (int)(data->player.y * data->tile_size);
//
//   // Calculate starting and ending angles
//   double start_angle = data->player.angle - (FOV / 2);
//   // double end_angle = data->player.angle + (FOV / 2);
//
//   // Calculate angle increment between rays
//   double angle_step = FOV / NUM_RAYS;
//
//   // Draw each ray
//   for (int i = 0; i < NUM_RAYS; i++)
//   {
//     double ray_angle = start_angle + (i * angle_step);
//
//     // Calculate end point of this ray
//     int ray_length = data->tile_size * 2;  // Length of visualization
//     int end_x = player_screen_x + (int)(cos(ray_angle) * ray_length);
//     int end_y = player_screen_y + (int)(sin(ray_angle) * ray_length);
//
//     // Draw the ray
//     draw_line(data, player_screen_x, player_screen_y, end_x, end_y, 0x00FF00);
//   }
// }
//
// void draw_fov_cone(t_data *data)
// {
//   int player_screen_x = (int)(data->player.x * data->tile_size);
//   int player_screen_y = (int)(data->player.y * data->tile_size);
//
//   int ray_length = data->tile_size * 3;
//
//   // Left edge of FOV
//   double left_angle = data->player.angle - (FOV / 2);
//   int left_x = player_screen_x + (int)(cos(left_angle) * ray_length);
//   int left_y = player_screen_y + (int)(sin(left_angle) * ray_length);
//   draw_line(data, player_screen_x, player_screen_y, left_x, left_y, 0xFFFF00);
//
//   // Right edge of FOV
//   double right_angle = data->player.angle + (FOV / 2);
//   int right_x = player_screen_x + (int)(cos(right_angle) * ray_length);
//   int right_y = player_screen_y + (int)(sin(right_angle) * ray_length);
//   draw_line(data, player_screen_x, player_screen_y, right_x, right_y, 0xFFFF00);
//
//   // Center direction line (brighter color)
//   int center_x = player_screen_x + (int)(cos(data->player.angle) * ray_length);
//   int center_y = player_screen_y + (int)(sin(data->player.angle) * ray_length);
//   draw_line(data, player_screen_x, player_screen_y, center_x, center_y, 0x00FFFF);
// }

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
  int max_steps = 1000;  // Prevent infinite loops
  for (int i = 0; i < max_steps; i++)
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
  double start_angle = data->player.angle - (FOV / 2);
  double angle_step = FOV / NUM_RAYS;
  
  for (int i = 0; i < NUM_RAYS; i++)
  {
    double ray_angle = start_angle + (i * angle_step);
    
    // Different colors for better visualization
    int color = (i == NUM_RAYS / 2) ? 0xF0FFFF : 0x004400;  // Center ray brighter
    
    cast_ray_to_wall(data, ray_angle, color);
  }
}
