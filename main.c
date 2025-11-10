
#include "cub3d.h"
#include <threads.h>



void print_list(t_cub3d *cur)
{
  t_cub3d *current = cur;
  while (current)
  {
    printf("%s", current->data);
    current = current->next;
  }
}

void clear_list(t_cub3d **list)
{
  t_cub3d *current;
  t_cub3d *next;

  if (!list || !*list)
    return;
  current = *list;
  while (current)
  {
    next = current->next;
    free(current->data);
    free(current);
    current = next;
  }
  current = NULL;
}



int main(int ac, char **av)
{
  if(ac != 2)
  {
    printf("invalide args! \n");
    return 1;
  }
  t_data *data = malloc(sizeof(*data));
  if (!data)
    return EXIT_FAILURE;

  if (init_data(data) == -1) {
    free(data);
    return EXIT_FAILURE;
  }

  int_fill(data, av[1]);
  if (get_map(data, av) || parsing(data)) {
    fprintf(stderr, "Error\nInvalid map.\n");
    free_all(data);
    return EXIT_FAILURE;
  }

  init_mlx(data);
  render_frame(data);
  mlx_key_hook(data->win, key_press, data);
  mlx_loop(data->mlx);

  free_all(data);
  return EXIT_SUCCESS;
}
