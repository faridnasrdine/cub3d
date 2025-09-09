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

typedef struct s_data {
    char **map;
    int map_height;
} t_data;

int parsing(t_data *data);
int get_big_line(char **map);

#endif