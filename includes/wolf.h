#ifndef WOLF_H
# define WOLF_H

# include "mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <math.h>

#define WIDTH 500
#define HEIGHT 500

typedef struct			s_vector
{
	int					x;
	int					y;
    int                 val;
	struct s_vector		*next;
}						t_vector;

typedef struct          s_rgb
{
    int                 r;
    int                 g;
    int                 b;
    int                 color;
}                       t_rgb;

typedef struct  s_wolf
{
    void        *mlx;
    void        *wind;
    int         **map;
    double      posx;
    double      posy;
    double      dirx;
    double      diry;
    double      planex;
    double      planey;
    double      oldtime;
    double      newtime;
    double      camerax;
    double      raydirx;
    double      raydiry;
    int      mapx;
    int      mapy;
    double      sidedistx;
    double      sidedisty;
    double      deltadistx;
    double      deltadisty;
    double      perpwalldist;
    double      moveSpeed;
    double      rotSpeed;
    double      frameTime;
    int         map_w;
    int         map_h;
    char                *addr;
    int                 bits_per_pixel;
    int                 size_line;
    int                 endian;
    void                *img;
    t_vector	*vector;
	t_vector	*curr;
    t_rgb       rgb;

}               t_wolf;

void    write_data(t_wolf *head, char *str);
t_vector	*ft_add_new(t_vector *head);
int  ft_esc(t_wolf *head);
void ft_usage(void);
void    tata(t_wolf *head);
void    draw(t_wolf *e);

#endif