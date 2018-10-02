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

int le_hook(int key, t_wolf *head)
{
    if (key == 65307)
        ft_esc(head);
    return (0);
}

int main(int argc, char **argv)
{
    t_wolf *head;

    printf("test   %d %s\n", argc, argv[0]);
    if (argc == 2)
    {
        head = malloc(sizeof(t_wolf));
        write_data(head, argv[1]);
        head->mlx = mlx_init();
        head->wind = mlx_new_window(head->mlx, WIDTH, HEIGHT, "wolf3d");
        mlx_hook(head->wind, 17, 1L << 17, ft_esc, head);
        mlx_hook(head->wind, 2, 5, le_hook, head);
        mlx_loop(head->mlx);
    }
    else
        ft_usage();
    return (0);
}