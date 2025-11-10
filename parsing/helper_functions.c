#include "cub3d.h"

void  render_frame(t_data *data)
{
  draw_map(data);
  mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}


char	*ft_strcpy(char *dst, const char *src)
{
	int	i;

	if (!dst || !src)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

void  add_back(t_cub3d **list, t_cub3d *new)
{
  t_cub3d *current;

  if (!list || !new)
    return;
  if (!*list)
  {
    *list = new;
    return;
  }
  current = *list;
  while (current->next)
  {
    current = current->next;
  }
  current->next = new;
}

t_cub3d *new_node(char *content)
{
  t_cub3d *node = malloc(sizeof(*node));
  if (!node) return NULL;

  size_t n = ft_strlen(content);
  node->data = malloc(n + 1);
  if (!node->data) { free(node); return NULL; }

  ft_memcpy(node->data, content, n + 1);
  node->next = NULL;
  return node;
}


