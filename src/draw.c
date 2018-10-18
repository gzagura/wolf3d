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

void	prep_dda(t_wolf *e)
{
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
}

void	dda(t_wolf *e)
{
	while (e->hit == 0)
	{
		if (e->sidedistx < e->sidedisty)
		{
			e->sidedistx += e->deltadistx;
			e->mapx += e->stepx;
			e->side = 0;
		}
		else
		{
			e->sidedisty += e->deltadisty;
			e->mapy += e->stepy;
			e->side = 1;
		}
		if (e->map[e->mapx][e->mapy] > 0)
			e->hit = 1;
	}
	if (e->side == 0)
		e->walld = (e->mapx - e->posx + (1 - e->stepx) / 2) / e->raydirx;
	else
		e->walld = (e->mapy - e->posy + (1 - e->stepy) / 2) / e->raydiry;
	e->lineheight = (int)(HEIGHT / e->walld);
	e->drawstart = (((e->lineheight) * (-1)) / 2) + HEIGHT / 2;
	if (e->drawstart < 0)
		e->drawstart = 0;
}

void	math(t_wolf *e, int x)
{
	e->hit = 0;
	e->side = 0;
	e->camerax = 2 * x / (double)(WIDTH) - 1;
	e->raydirx = e->dirx + e->planex * e->camerax;
	e->raydiry = e->diry + e->planey * e->camerax;
	e->mapx = (int)e->posx;
	e->mapy = (int)e->posy;
	e->deltadistx = fabs(1 / e->raydirx);
	e->deltadisty = fabs(1 / e->raydiry);
}

void	draw(t_wolf *e)
{
	int x;

	x = -1;
	while (++x < WIDTH)
	{
		math(e, x);
		prep_dda(e);
		dda(e);
		e->drawend = e->lineheight / 2 + HEIGHT / 2;
		if (e->drawend >= HEIGHT)
			e->drawend = HEIGHT - 1;
		if (e->side == 0)
			e->wallx = e->posy + e->walld * e->raydiry;
		else
			e->wallx = e->posx + e->walld * e->raydirx;
		e->wallx -= floor((e->wallx));
		e->texx = (int)(e->wallx * (double)(64));
		if (e->side == 0 && e->raydirx > 0)
			e->texx = 64 - e->texx - 1;
		if (e->side == 1 && e->raydiry < 0)
			e->texx = 64 - e->texx - 1;
		verline(e, x);
		draw_floor(e, x);
	}
}
