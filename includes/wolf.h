#ifndef WOLF_H
# define WOLF_H

# include "mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "get_next_line.h"
# include <fcntl.h>

#define WIDTH 500
#define HEIGHT 500

typedef struct			s_vector
{
	int					x;
	int					y;
    int                 val;
	struct s_vector		*next;
}						t_vector;

typedef struct  s_wolf
{
    void        *mlx;
    void        *wind;
    int         **cords;
    double      posx;
    double      posy;
    double      dirx;
    double      diry;
    double      planex;
    double      planey;
    int         map_w;
    int         map_h;
    t_vector	*vector;
	t_vector	*curr;

}               t_wolf;

void    write_data(t_wolf *head, char *str);
t_vector	*ft_add_new(t_vector *head);
int  ft_esc(t_wolf *head);
void ft_usage(void);

#endif