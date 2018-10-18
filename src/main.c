/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzagura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 19:24:09 by gzagura           #+#    #+#             */
/*   Updated: 2018/10/17 19:24:12 by gzagura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	position(t_wolf *e)
{
	int		i;
	int		j;

	i = 0;
	while (i < e->map_h)
	{
		j = 0;
		while (j < e->map_w)
		{
			if (e->map[i][j] == 0)
			{
				e->posx = j;
				e->posy = i;
				return ;
			}
			j++;
		}
		i++;
	}
	invalid();
}

void	ft_usage(void)
{
	ft_putstr("usage: ./wolf3d <map>\nexample: ./wolf3d map\n");
	exit(1);
}

void	init2(t_wolf *e)
{
	e->t[0].addr = mlx_get_data_addr(e->t[0].img, &e->t[0].bpp,
		&e->t[0].sl, &e->t[0].endl);
	e->t[1].addr = mlx_get_data_addr(e->t[1].img, &e->t[1].bpp,
		&e->t[1].sl, &e->t[1].endl);
	e->t[2].addr = mlx_get_data_addr(e->t[2].img, &e->t[2].bpp,
		&e->t[2].sl, &e->t[2].endl);
	e->t[3].addr = mlx_get_data_addr(e->t[3].img, &e->t[3].bpp,
		&e->t[3].sl, &e->t[3].endl);
	e->t[4].addr = mlx_get_data_addr(e->t[4].img, &e->t[4].bpp,
		&e->t[4].sl, &e->t[4].endl);
	e->t[5].addr = mlx_get_data_addr(e->t[5].img, &e->t[5].bpp,
		&e->t[5].sl, &e->t[5].endl);
}

void	init(t_wolf *e)
{
	int		lar;
	int		lon;

	e->dirx = 1;
	e->diry = 0;
	e->planex = 0;
	e->planey = 0.66;
	e->move = 0.32;
	e->rot = 0.09;
	e->t[0].img = mlx_xpm_file_to_image(e->mlx,
		"./img/redbrick.xpm", &lar, &lon);
	e->t[1].img = mlx_xpm_file_to_image(e->mlx,
		"./img/bluestone.xpm", &lar, &lon);
	e->t[2].img = mlx_xpm_file_to_image(e->mlx,
		"./img/eagle.xpm", &lar, &lon);
	e->t[3].img = mlx_xpm_file_to_image(e->mlx,
		"./img/colorstone.xpm", &lar, &lon);
	e->t[4].img = mlx_xpm_file_to_image(e->mlx,
		"./img/purplestone.xpm", &lar, &lon);
	e->t[5].img = mlx_xpm_file_to_image(e->mlx,
		"./img/greystone.xpm", &lar, &lon);
	init2(e);
}

int		main(int argc, char **argv)
{
	t_wolf *head;

	if (argc == 2)
	{
		head = malloc(sizeof(t_wolf));
		bzero(head, sizeof(t_wolf));
		write_data(head, argv[1]);
		head->mlx = mlx_init();
		position(head);
		system("afplay ./src/GTA.mp3 &");
		head->wind = mlx_new_window(head->mlx, WIDTH, HEIGHT, "wolf3d");
		head->img = mlx_new_image(head->mlx, WIDTH, HEIGHT);
		head->addr = mlx_get_data_addr(head->img,
			&(head->bits_per_pixel), &(head->size_line), &(head->endian));
		init(head);
		le_hook(124, head);
		le_hook_help(head, 126);
		mlx_hook(head->wind, 17, 1L << 17, ft_esc, head);
		mlx_hook(head->wind, 2, 5, le_hook, head);
		mlx_loop(head->mlx);
	}
	else
		ft_usage();
	return (0);
}
