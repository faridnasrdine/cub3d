#include "cub3d.h"



int main(int ac, char **av)
{
    t_data *data;
    if(ac == 2)
    {
        data = malloc(sizeof(t_data));
        if (parsing(data))
        {
            // Handle parsing error
        }
    }
    return 0;
}