#include "cub3d.h"


void flag(int *f)
{
    int i = 0;
    while(i < 8)
        f[i++] = 0;
}
void	map_setter(t_data *data, ssize_t j, char **map)
{
	ssize_t	i;

	i = 0;
	data->map->map = malloc(sizeof(char *) * (j + 1));
	while (map[i])
	{
		data->map->map[i] = ft_strdup(map[i]);
		free(map[i]);
		i++;
	}
	free(map);
	data->map->map[i] = NULL;
}
int	parse_rgb_string(char *str)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(str);
	while (*str && *str != ',')
		str++;
	if (*str == ',')
		str++;
	g = ft_atoi(str);
	while (*str && *str != ',')
		str++;
	if (*str == ',')
		str++;
	b = ft_atoi(str);
	if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0)
		return (-1);
	return (((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF));
}
int	texture_help(t_data *data, char *str)
{
	if (ft_strncmp(str, "NO ", 3) == 0)
		data->map->north->file = ft_strndup(str, 3);
	else if (ft_strncmp(str, "SO ", 3) == 0)
		data->map->south->file = ft_strndup(str, 3);
	else if (ft_strncmp(str, "WE ", 3) == 0)
		data->map->west->file = ft_strndup(str, 3);
	else if (ft_strncmp(str, "EA ", 3) == 0)
		data->map->east->file = ft_strndup(str, 3);
	else if (ft_strncmp(str, "F ", 2) == 0)
		data->map->floor = parse_rgb_string(str + 2);
	else if (ft_strncmp(str, "C ", 2) == 0)
		data->map->celling = parse_rgb_string(str + 2);
	else
		return (1);
	if (data->map->floor == -1 || data->map->celling == -1)
		return (-1);
	return (0);
}

int	check_attribute(char *str)
{
	char	*attr[7];
	ssize_t	i;

	i = 0;
	attr[0] = "NO ";
	attr[1] = "SO ";
	attr[2] = "WE ";
	attr[3] = "EA ";
	attr[4] = "F ";
	attr[5] = "C ";
	attr[6] = NULL;
	while (attr[i])
	{
		if (ft_strncmp(attr[i], str, ft_strlen(attr[i])) == 0)
			break ;
		i++;    
	}
	if (i < 6)
		return (i);
	else
		return (-1);
}

int	fun(t_data *data, char *str, int *flags)
{
	int	attr;

	attr = check_attribute(str);
	if (attr >= 0)
	{
		if (flags[attr] == 1)
			return (1);
		flags[attr] = 1;
		if (texture_help(data, str) == -1)
			return (1);
		free(str);
		return (2);
	}
	return (0);
}

int loop_map(t_data *data, char *line, int *f)
{
    int i = 0;
    if(!line)
        return 1;
    if(!line[0])
    {
        free(line);
        return 2;
    }
    i = fun(data, line, f);
    if(i == 1)
    {
        free(line);
        return 1;
    }
    else if(i == 2)
        return 2;
    return 0;
}

int check_char(char *ptr, char c, int len)
{
    int i = 0;
    int count = 0;
    while(i < len)
    {
        if(ptr[i] == c)
            count++;
        i++;
    }
    return(count);
}

int check_flag(int *flag)
{
    int i = 0;
    while(i < 6)
    {
        if(flag[i] != 1)
        {
            return 1;
        }
            
        i++;
    }
    return 0;
}

int get_line(char **av)
{
    int fd;
    int read_byts;
    char *ptr;
    int len = 0;

    fd = open(av[1], O_RDONLY);
    if(fd < 0)
        return -1;
    
    ptr = malloc(BUFFER_SIZE + 1);
    if(!ptr)
    {
        close(fd);
        return -1;
    }
    
    while(ptr)
    {
        read_byts = read(fd, ptr, BUFFER_SIZE);
        if(read_byts <= 0)
            break;
        ptr[read_byts] = '\0';
        len += check_char(ptr, '\n', read_byts);
    }
    len++;
    free(ptr);
    close(fd);
    return(len + 1);
}

void map_str(t_data *data, int j, char **map)
{
    int i = 0;
    int x = 0;
    data->map->map = malloc(sizeof(char *) * (j + 1));
    if(!data->map->map)
        return;
    
    while (map[i][0] == '\0' || map[i][0] == '\n')
        i++;
    while(map[i])
    {
        data->map->map[x++] = ft_strdup(map[i]);
        free(map[i]);
        i++;
    }
    data->map->map[x] = NULL;  
    free(map);
}

int get_map(t_data *data, char **av)
{
    int i;
    char *line;
    char **map;
    int ret = 0;
    int f[7];
    
    i = 0;
    line = ft_strdup("");
    map = malloc(sizeof(char *) * get_line(av));
    if(!map)
    {
        if(line)
            free(line);
        return -1;
    }
    
    flag(f);
    while(line)
    {
        line = get_next_line(data->map->fd);
        ret = loop_map(data, line, f);
        if(ret == 1)
            break;
        else if(ret == 2)
            continue;
        map[i++] = ft_strdup(line);
        free(line);
    }
    map[i] = NULL;
    map_str(data, i, map);
    return(check_flag(f));
}
void int_fill(t_data *data, char *av)
{
    int fd;

    fd = open(av, O_RDONLY);
    if(fd < 0)
    {
        return;
    }
   
    data->map->fd = fd;
}
int init_data(t_data *data)
{
    data->map = malloc(sizeof(t_map));
    if (!data->map)
        return -1;
    data->map->north = malloc(sizeof(t_texture));
    data->map->south = malloc(sizeof(t_texture));
    data->map->west = malloc(sizeof(t_texture));
    data->map->east = malloc(sizeof(t_texture));
    data->map->door = malloc(sizeof(t_texture));
    data->map->door_1 = malloc(sizeof(t_texture));
    data->map->door_2 = malloc(sizeof(t_texture));
    data->map->door_3 = malloc(sizeof(t_texture));
    
    if (!data->map->north || !data->map->south || !data->map->west || 
        !data->map->east || !data->map->door || !data->map->door_1 || 
        !data->map->door_2 || !data->map->door_3)
    {
       //cleanup function!!!!!!!!!!!!!!!
        return -1;
    }
    data->player = malloc(sizeof(t_player));
    data->map->floor = 0;
    data->map->celling = 0;
    data->map->map = NULL;
    data->map->fd = -1;
    data->player->x = 0.0;
    data->player->y = 0.0;
    // data->player->dir = 0;
    
    return 0;
}

int main(int ac, char **av)
{
    t_data *data;
    if(ac == 2)
    {
        data = malloc(sizeof(t_data));
        if (!data)
            return -1;
        if (init_data(data) == -1)
        {
            free(data);
            return -1;
        }
        int_fill(data, av[1]);
        
        if (get_map(data, av) || parsing(data))
        {
            printf("Error\nInvalid map.\n");
            free(data);
            return -1;
        }
   
        set_mlx(data);
    }
    return 0;
}