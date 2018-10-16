#include "wolf.h"

#include <stdlib.h>

char        *ft_strjoinfree(char const *s1, char const *s2)
{
    char    *string;

    if (!s1 || !s2)
        return (NULL);
    string = (char *)malloc(sizeof(char) * (ft_strlen(s1) +
                                            ft_strlen(s2) + 1));
    if (!string)
        return (NULL);
    ft_strcpy(string, s1);
    ft_strcpy(string + ft_strlen(s1), s2);
    return (string);
}


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
		tmp = ft_strjoinfree(tmp, buffer);
		tmp = ft_strjoinfree(tmp, "\n");
		free(buffer);
	}
    valid(head, tmp);
    head->map = transform_data(head, tmp);

//     int i;
//     int j;

//     i = 0;
//     while (i < head->map_h)
//     {
//         j = 0;
//         while ( j < head->map_w)
//         {
//             printf("%i", head->map[i][j]);
//             j++;
//         }
//         printf("\n");
//         i++;
//     }
}