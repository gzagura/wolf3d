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
	head->addr[count_pxl] = head->rgb.color & 0x0000ff;
	head->addr[count_pxl + 1] = (head->rgb.color >> 8) & 0xff;
	head->addr[count_pxl + 2] = (head->rgb.color >> 16);
}

void	floor_put(t_wolf *e, int textx, int texty, int y, int x)
{
	int count_pxl;

	texty++;
	textx++;
	count_pxl = pixels(x, y);
	e->addr[count_pxl] = 0;
	e->addr[count_pxl + 1] = 124;
	e->addr[count_pxl + 2] = 124;
}

void	draw_floor(t_wolf *e, int end, int x)
{
	double	curr_dist;
	int 	y;
	double	curr_floor_x;
	double	curr_floor_y;
	int textx;
	int	texty;

	y = end + 1;
	while (y < HEIGHT)
	{
		curr_dist = (double)HEIGHT / (2 * (double)y - (double)HEIGHT);
		curr_floor_x = curr_dist / e->perpwalldist * x + (1 - (curr_dist / e->perpwalldist)) * e->posx;
		curr_floor_y = curr_dist / e->perpwalldist * y + (1 - (curr_dist / e->perpwalldist)) * e->posy;
		textx = (int)(curr_floor_x * TT) % TT;
		texty = (int)(curr_floor_y * TT) % TT;
		floor_put(e, textx, texty, y, x);
		y++;
	}
}

void	verLine(t_wolf *head, int x, int st, int end, int side, int i)
{
	int y;

	y = st;
	if (side == 0 && head->camx >= 0)
	{
		i = 0;
	}
	else if (side == 0 && head->camx < 0)
	{
		i = 1;
	}
	else if (side == 1 && head->camy >= 0)
	{
		i = 2;
	}
	else
	{
		i = 3;
	}
	while (y < end)
	{

		int d = y * 256 - HEIGHT * 128 + head->lineHeight * 128;  //256 and 128 factors to avoid floats
        // TODO: avoid the division to speed this up
        int texY = ((d * 64) / head->lineHeight) / 256;
        int temp = head->texX * 4 + texY * head->text[i].sl;
        head->rgb.color = head->text[i].addr[temp + 2] << 16;
        head->rgb.color += head->text[i].addr[temp + 1] << 8;
        head->rgb.color += head->text[i].addr[temp];
        if(side == 1)
        {
        	head->rgb.color = (head->rgb.color >> 1) & 8355711;
        } 
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

		e->camx = e->dirx + e->planex * e->camerax;
		e->camy = e->diry + e->planey * e->camerax;

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
	    e->lineHeight = (int)(HEIGHT / e->perpwalldist);
	    drawStart = (((e->lineHeight) * (-1)) / 2) + HEIGHT / 2;
	    if (drawStart < 0)
	    	drawStart = 0;
	    drawEnd = e->lineHeight / 2 + HEIGHT / 2;
	    if (drawEnd >= HEIGHT)
	    	drawEnd = HEIGHT - 1;
	    int		texnum = e->map[e->mapx][e->mapy] - 1;
      	if (side == 0) e->wallX = e->posy + e->perpwalldist * e->raydiry;
      	else           e->wallX = e->posx + e->perpwalldist * e->raydirx;
      	e->wallX -= floor((e->wallX));
	   	e->texX = (int)(e->wallX * (double)(64));
      	if(side == 0 && e->raydirx > 0) e->texX = 64 - e->texX - 1;
      	if(side == 1 && e->raydiry < 0) e->texX = 64 - e->texX - 1;
     	verLine(e, x, drawStart, drawEnd, side, texnum);
     	draw_floor(e, drawEnd, x);
      	x++;
    }
}
