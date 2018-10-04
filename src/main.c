#include "wolf.h"

int  ft_esc(t_wolf *head)
{
    ft_putstr("Bye-bye\n");
    mlx_destroy_window(head->mlx, head->wind);
    exit(0);
    return (0); 
}

void ft_usage(void)
{
    ft_putstr("usage: \n");
    exit(1);
}

int le_hook(int key, t_wolf *e)
{
    if (key == 65307)
        ft_esc(e);
    if (key == 53)
        ft_esc(e);
    if (key == 125)
    {
      double oldDirX = e->dirx;
      e->dirx = e->dirx * cos(-(e->rotSpeed)) - e->diry * sin(-(e->rotSpeed));
      e->diry = oldDirX * sin(-(e->rotSpeed)) + e->diry * cos(-(e->rotSpeed));
      double oldPlaneX = e->planex;
      e->planex = e->planex * cos(-(e->rotSpeed)) - e->planey * sin(-(e->rotSpeed));
      e->planey = oldPlaneX * sin(-(e->rotSpeed)) + e->planey * cos(-(e->rotSpeed));
    }
    if (key == 126)
    {
      double oldDirX = e->dirx;
      e->dirx = e->dirx * cos(e->rotSpeed) - e->diry * sin(e->rotSpeed);
      e->diry = oldDirX * sin(e->rotSpeed) + e->diry * cos(e->rotSpeed);
      double oldPlaneX = e->planex;
      e->planex = e->planex * cos(e->rotSpeed) - e->planey * sin(e->rotSpeed);
      e->planey = oldPlaneX * sin(e->rotSpeed) + e->planey * cos(e->rotSpeed);
    }
    if (key == 123)
    {
      if(e->map[(int)(e->posx + e->dirx * e->moveSpeed)][(int)(e->posy)])
        e->posx = e->posx + e->dirx * e->moveSpeed;
      if(e->map[(int)(e->posx)][(int)(e->posy + e->diry * e->moveSpeed)])
        e->posy = e->posy + e->diry * e->moveSpeed;
    }
    //move backwards if no wall behind you
    if (key == 124)
    {
      if(e->map[(int)(e->posx - e->dirx * e->moveSpeed)][(int)(e->posy)])
        e->posx = e->posx - e->dirx * e->moveSpeed;
      if(e->map[(int)(e->posx)][(int)(e->posy - e->diry * e->moveSpeed)])
        e->posy = e->posy - e->diry * e->moveSpeed;
    }
    tata(e);
    return (0);
}

int main(int argc, char **argv)
{
    t_wolf *head;

    if (argc == 2)
    {
        head = malloc(sizeof(t_wolf));
        write_data(head, argv[1]);
        head->mlx = mlx_init();
        head->wind = mlx_new_window(head->mlx, WIDTH, HEIGHT, "wolf3d");
        head->posx = 2;
        head->posy = 4;
        head->dirx = 1;
        head->diry = 0;
        head->planex = 0;
        head->planey = 0.66;
        head->img = mlx_new_image(head->mlx, WIDTH, HEIGHT);
        head->addr = mlx_get_data_addr(head->img,
            &(head->bits_per_pixel), &(head->size_line), &(head->endian));
        tata(head);
        mlx_hook(head->wind, 17, 1L << 17, ft_esc, head);
        mlx_hook(head->wind, 2, 5, le_hook, head);
        mlx_loop(head->mlx);
    }
    else
        ft_usage();
    return (0);
}