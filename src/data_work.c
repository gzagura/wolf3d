#include "wolf.h"

void    invalid()
{
    ft_putstr("invalid map\n");
    exit(1);
}

void    valid(t_wolf *head, char *str)
{
    int i;
    int j;

    i = 0;
    while (str[i] && str[i] != '\n')
        i++;
    head->map_w = i;
    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] == '\n')
        {
            if (j != head->map_w)
                invalid();
            j = -1;
            head->map_h += 1;
        }
        j++;
        i++;
    }
}

void    coord(t_wolf *head, int x, int y, int val)
{
    head->curr->x = x;
    head->curr->y = y;
    head->curr->val = val;
    head->curr = ft_add_new(head->vector);
}

int   **transform_data(t_wolf *head, char *str)
{
    int i;
    int j;
    int k;
    int w;
    int **cor;

    i = 0;
    j = 0;
    k = 0;
    cor = (int**)malloc(sizeof(int*) * (head->map_h + 1));
    w = -1;
    while (++w < head->map_w)
        cor[w] = (int*)malloc(sizeof(int) * head->map_w);
    while (str[i])
    {
        if (str[i] == '\n')
        {
            cor[k][j] = '\0';
            j = -1;
            k++;
        }
        if ((str[i] < '0' || str[i] > '9') && str[i] != '\n')
            invalid();
        if (str[i] >= '0' && str[i] <= '9')
        {
            cor[k][j] = (int)(str[i] - 48);
        }
        i++;
        j++;
    }
    return (cor);
}

void    write_data(t_wolf *head, char *str)
{
    char	*buffer;
	char	*tmp;
	int		fd;

    if ((fd = open(str, O_RDONLY)) < 0)
        ft_usage();
	buffer = NULL;
	tmp = ft_strnew(1);
	while (get_next_line(fd, &buffer) > 0)
	{
		tmp = ft_strjoin(tmp, buffer);
		tmp = ft_strjoin(tmp, "\n");
		free(buffer);
	}
    valid(head, tmp);
    head->cords = transform_data(head, tmp);
}