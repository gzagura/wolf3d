#include "wolf.h"

int  ft_esc(t_wolf *head)
{
    ft_putstr("Bye-bye\n");
    mlx_destroy_window(head->mlx, head->wind);
    // system("killall afplay");
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
    if (key == 123) // right
    {
      double oldDirX = e->dirx;
      e->dirx = e->dirx * cos(-(e->rotSpeed)) - e->diry * sin(-(e->rotSpeed));
      e->diry = oldDirX * sin(-(e->rotSpeed)) + e->diry * cos(-(e->rotSpeed));
      double oldPlaneX = e->planex;
      e->planex = e->planex * cos(-(e->rotSpeed)) - e->planey * sin(-(e->rotSpeed));
      e->planey = oldPlaneX * sin(-(e->rotSpeed)) + e->planey * cos(-(e->rotSpeed));
    }
    if (key == 124) // left
    {
      double oldDirX = e->dirx;
      e->dirx = e->dirx * cos(e->rotSpeed) - e->diry * sin(e->rotSpeed);
      e->diry = oldDirX * sin(e->rotSpeed) + e->diry * cos(e->rotSpeed);
      double oldPlaneX = e->planex;
      e->planex = e->planex * cos(e->rotSpeed) - e->planey * sin(e->rotSpeed);
      e->planey = oldPlaneX * sin(e->rotSpeed) + e->planey * cos(e->rotSpeed);
    }
    if (key == 126) // up
    {
      if(e->map[(int)(e->posx + e->dirx * e->moveSpeed)][(int)(e->posy)] == 0)
        e->posx += e->dirx * e->moveSpeed;
      if(e->map[(int)(e->posx)][(int)(e->posy + e->diry * e->moveSpeed)] == 0)
        e->posy += e->diry * e->moveSpeed;
    }
    if (key == 125) // black
    {
      if(e->map[(int)(e->posx - e->dirx * e->moveSpeed)][(int)(e->posy)] == 0)
        e->posx -= e->dirx * e->moveSpeed;
      if(e->map[(int)(e->posx)][(int)(e->posy - e->diry * e->moveSpeed)] == 0)
        e->posy -= e->diry * e->moveSpeed;
    }
    tata(e);
    return (0);
}

int   PlaySound()
{
    int status;

    status = 0;
    system("afplay -t 10000 ./test1.mp3 &");

    return status;
}


void  init_text(t_wolf *head)
{
    int     lar;
    int     lon;

    head->text[0] = (unsigned int*)mlx_get_data_addr(mlx_xpm_file_to_image(head->mlx, "redbrick.xpm", &lar, &lon), &(head->bpp), &(head->sl), &(head->e));
}


int main(int argc, char **argv)
{
    t_wolf *head;

    if (argc == 2)
    {
        head = malloc(sizeof(t_wolf));
        write_data(head, argv[1]);
        head->mlx = mlx_init();
        // PlaySound();
        head->wind = mlx_new_window(head->mlx, WIDTH, HEIGHT, "wolf3d");
        head->posx = 2;
        head->posy = 2;
        head->dirx = 1;
        head->diry = 0;
        head->planex = 0;
        head->planey = 0.66;
        head->moveSpeed = 0.22;
        head->rotSpeed = 0.05;
        head->img = mlx_new_image(head->mlx, WIDTH, HEIGHT);
        head->addr = mlx_get_data_addr(head->img,
            &(head->bits_per_pixel), &(head->size_line), &(head->endian));
        // init_text(head);
        tata(head);
        mlx_hook(head->wind, 17, 1L << 17, ft_esc, head);
        mlx_hook(head->wind, 2, 5, le_hook, head);
        mlx_loop(head->mlx);
    }
    else
        ft_usage();
    return (0);
}