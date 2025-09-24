#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "get_next_line/get_next_line.h"
typedef struct s_texture
{
    char	*file;
    void	*img;
    char	*addr;
    int		bpp;
    int		endian;
}				t_texture;
typedef struct s_map
{
    t_texture	*north;
    t_texture	*south;
    t_texture	*west;
    t_texture	*east;
    t_texture	*door;
    t_texture	*door_1;
    t_texture	*door_2;
    t_texture	*door_3;
	int			fd;
	int			celling;
	int			floor;
	int			map_height;
	int			map_lenght;
	char		**map;
}				t_map;

typedef struct s_player
{
    double x;
    double y;
    int dir;
}   t_player;


typedef struct s_data {
    t_map		*map;
    t_player    *player;
    int x;
    int y;
    int map_height;
    int map_length;

} t_data;

int parsing(t_data *data);
int get_big_line(char **map);
char	*ft_strdup(const char *s);
char	*ft_strndup(char *s, int n);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int rgb(char *str);
int get_height_line(char **map);
#endif