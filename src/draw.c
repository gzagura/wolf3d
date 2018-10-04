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
	ft_bzero(head->addr, ft_strlen(head->addr));
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
	printf("111\n");
	while (y < end)
	{
		//mlx_pixel_put(head->mlx, head->wind, x, y, head->rgb.color);
		wrip(head, pixels(x, y));
		y++;
	}
}

void	draw(t_wolf *e)
{
	int x;
	int y;
	int	stepx;
	int	stepy;
	int hit = 0;
	int side;

	x = 0;
	y = 0;
	while (x < WIDTH)
	{
		e->camerax = 2 * x / (double)(WIDTH) - 1;
		e->raydirx = e->dirx + e->planex * e->camerax;
		e->raydiry = e->diry + e->planey * e->camerax;

		e->mapx = (int)e->posx;
		e->mapy = (int)e->posy;

		e->deltadistx = fabs(1 / e->raydirx);
		e->deltadisty = fabs(1 / e->raydiry);
		if (e->raydirx < 0)
		{
			stepx = -1;
			e->sidedistx = (e->posx - e->mapx) * e->deltadistx;
		}
		else
		{
			stepx = 1;
			e->sidedistx = (e->mapx + 1.0 - e->posx) * e->deltadistx;
		}
		if (e->raydiry < 0)
		{
			stepy = -1;
			e->sidedisty = (e->posy - e->mapy) * e->deltadisty;
		}
		else
		{
			stepy = 1;
			e->sidedisty = (e->mapy + 1.0 - e->posy) * e->deltadisty;
		}
		while (hit == 0)
		{
			if (e->sidedistx < e->sidedisty)
			{
	      		e->sidedistx = e->sidedistx + e->deltadistx;
	      		e->mapx = e->mapx + stepx;
	      		side = 0;
	      	}
	      	else
	      	{
	      		e->sidedisty = e->sidedisty + e->deltadisty;
	      		e->mapy = e->mapy + stepy;
	      		side = 1;
	      	}
	      	if (e->map[(int)e->mapx][(int)e->mapy] > 0)
	      		hit = 1;
	    }
	    if (side == 0)
	    {
	    	e->perpwalldist = (e->mapx - e->posx + (1 - stepx) / 2) / e->raydirx;
	    }
	    else
	    {
	    	e->perpwalldist = (e->mapy - e->posy + (1 - stepy) / 2) / e->raydiry;
	    }
	    int lineHeight = (int)(HEIGHT / e->perpwalldist);
	    printf("%f\n", e->perpwalldist);
	    int drawStart = -lineHeight / 2 + HEIGHT / 2;
	    if (drawStart < 0)
	    	drawStart = 0;
	    int drawEnd = lineHeight / 2 + HEIGHT / 2;
	    if (drawEnd >= HEIGHT)
	    	drawEnd = HEIGHT - 1;
      	if (e->map[e->mapx][e->mapy] == 0)
      	{
      		e->rgb.r = 255;
      		e->rgb.g = 0;
      		e->rgb.b = 0;
      		e->rgb.color = 16711680;
      	}
      	if (e->map[(int)e->mapx][(int)e->mapy] == 1)
      	{
      		e->rgb.r = 0;
      		e->rgb.g = 255;
      		e->rgb.b = 0;
      		e->rgb.color = 65280;
      	}
      	if (e->map[(int)e->mapx][(int)e->mapy] == 2)
      	{
      		e->rgb.r = 255;
      		e->rgb.g = 255;
      		e->rgb.b = 0;
      		e->rgb.color =16776960;
      	}
      	if (e->map[(int)e->mapx][(int)e->mapy] == 3)
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
      	printf("st %d end %d\n", drawStart, drawEnd);
      //draw the pixels of the stripe as a vertical line
      verLine(e, x, drawStart, drawEnd);
      x++;
    }
    //timing for input and FPS counter
    // e->oldtime = e->time;
    // time = getTicks();
    // e->frameTime = (e->time - e->oldtime) / 1000.0; //frameTime is the time this frame has taken, in seconds
    // mlx_string_put(e->mlx, e->wind, 10, 10, 255, ft_itoa(1.0 / e->frameTime));; //FPS counter
    e->moveSpeed = 0.1; //the constant value is in squares/second
    e->rotSpeed = 0.1; //the constant value is in radians/second
    
	}
