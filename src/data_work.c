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

void    transform_data(t_wolf *head, char *str)
{
    int i;
    int j;
    int k;

    i = 0;
    j = -1;
    k = 1;
    while (str[i])
    {
        if (str[i] == '\n')
        {
            j = 0;
            k++;
        }
        if ((str[i] < '0' || str[i] > '9') && str[i] != '\n')
            invalid();
        if (str[i] >= '0' && str[i] <= '9')
            coord(head, j, k, (int)(str[i] - 48));
        i++;
        j++;
    }
}

void    write_data(t_wolf *head, char *str)
{
    char	*buffer;
	char	*tmp;
	int		fd;

	head->vector = ft_add_new(NULL);
	head->curr = head->vector;
    if (str)
    {
        if ((fd = open(str, O_RDONLY)) < 0)
            ft_esc(head);
    }
	buffer = NULL;
	tmp = ft_strnew(1);
	while (get_next_line(fd, &buffer) > 0)
	{
		tmp = ft_strjoin(tmp, buffer);
		tmp = ft_strjoin(tmp, "\n");
		free(buffer);
	}
    valid(head, tmp);
    transform_data(head, tmp);
    head->curr = head->vector;
    while (head->curr->next)
    {
        printf("x = %d y = %d val = %d\n", head->curr->x, head->curr->y, head->curr->val);
        head->curr = head->curr->next;
    }
}