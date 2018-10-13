/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzagura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 15:26:27 by gzagura           #+#    #+#             */
/*   Updated: 2018/10/03 15:26:28 by gzagura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	tata(t_wolf *head)
{
	ft_bzero(head->addr, WIDTH * HEIGHT * 4);
	draw(head);
	mlx_put_image_to_window(head->mlx, head->wind, head->img, 0, 0);
}

int		pixels(int x, int y)
{
	int		count_pix;

	count_pix = 0;
	count_pix = (x * 4) + ((WIDTH * 4) * y);
	return (count_pix);
}

void	wrip(t_wolf *head, int count_pxl)
{
	head->addr[count_pxl] = head->rgb.r;
	head->addr[count_pxl + 1] = head->rgb.g;
	head->addr[count_pxl + 2] = head->rgb.b;
}


void	verLine(t_wolf *head, int x, int st, int end)
{
	int y;

	y = st;
	while (y < end)
	{
		wrip(head, pixels(x, y));
		y++;
	}
}

void	draw(t_wolf *e)
{
	int x = 0;
	int y = 0;
	int hit = 0;
	int side = 0;
	int lineHeight;
	int drawStart;
	int drawEnd;

	x = 0;
	y = 0;
	while (x < WIDTH)
	{
		hit = 0;
     	side = 0;
		e->camerax = 2 * x / (double)(WIDTH) - 1;
		e->raydirx = e->dirx + e->planex * e->camerax;
		e->raydiry = e->diry + e->planey * e->camerax;

		e->mapx = (int)e->posx;
		e->mapy = (int)e->posy;

		e->deltadistx = fabs(1 / e->raydirx);
		e->deltadisty = fabs(1 / e->raydiry);
		if (e->raydirx < 0)
		{
			e->stepx = -1;
			e->sidedistx = (e->posx - e->mapx) * e->deltadistx;
		}
		else
		{
			e->stepx = 1;
			e->sidedistx = (e->mapx + 1.0 - e->posx) * e->deltadistx;
		}
		if (e->raydiry < 0)
		{
			e->stepy = -1;
			e->sidedisty = (e->posy - e->mapy) * e->deltadisty;
		}
		else
		{
			e->stepy = 1;
			e->sidedisty = (e->mapy + 1.0 - e->posy) * e->deltadisty;
		}
		while (hit == 0)
		{
			if (e->sidedistx < e->sidedisty)
			{
	      		e->sidedistx += e->deltadistx;
	      		e->mapx += e->stepx;
	      		side = 0;
	      	}
	      	else
	      	{
	      		e->sidedisty += e->deltadisty;
	      		e->mapy += e->stepy;
	      		side = 1;
	      	}
	      	if (e->map[e->mapx][e->mapy] > 0)
	      		hit = 1;
	    }
	    if (side == 0)
	    {
	    	e->perpwalldist = (e->mapx - e->posx + (1 - e->stepx) / 2) / e->raydirx;
	    }
	    else
	    {
	    	e->perpwalldist = (e->mapy - e->posy + (1 - e->stepy) / 2) / e->raydiry;
	    }
	    lineHeight = (int)(HEIGHT / e->perpwalldist);
	    drawStart = (((lineHeight) * (-1)) / 2) + HEIGHT / 2;
	    if (drawStart < 0)
	    	drawStart = 0;
	    drawEnd = lineHeight / 2 + HEIGHT / 2;
	    if (drawEnd >= HEIGHT)
	    	drawEnd = HEIGHT - 1;
      	if (e->map[e->mapx][e->mapy] == 0)
      	{
      		e->rgb.r = 255;
      		e->rgb.g = 0;
      		e->rgb.b = 0;
      		e->rgb.color = 16711680;
      	}
      	if (e->map[e->mapx][e->mapy] == 1)
      	{
      		e->rgb.r = 0;
      		e->rgb.g = 255;
      		e->rgb.b = 0;
      		e->rgb.color = 65280;
      	}
      	if (e->map[e->mapx][e->mapy] == 2)
      	{
      		e->rgb.r = 255;
      		e->rgb.g = 255;
      		e->rgb.b = 0;
      		e->rgb.color = 16776960;
      	}
      	if (e->map[e->mapx][e->mapy] == 3)
      	{
      		e->rgb.r = 0;
      		e->rgb.g = 0;
      		e->rgb.b = 255;
      		e->rgb.color = 255;
      	}
      	if (side == 1)
      	{
      		e->rgb.r = e->rgb.r / 2;
      		e->rgb.g = e->rgb.g / 2;
      		e->rgb.b = e->rgb.b / 2;
      	}
      	// printf("%d\n", drawStart);
     	verLine(e, x, drawStart, drawEnd);
      	x++;
    }
	}
