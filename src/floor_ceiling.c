/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzagura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 13:15:21 by gzagura           #+#    #+#             */
/*   Updated: 2018/10/18 13:15:24 by gzagura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	floor_put(t_wolf *e, int y, int x)
{
	int count_pxl;

	count_pxl = pixels(x, y);
	e->addr[count_pxl] = e->t[4].addr[4 * (TT * e->tety + e->tetx)];
	e->addr[count_pxl + 1] = e->t[4].addr[4 * (TT * e->tety + e->tetx) + 1];
	e->addr[count_pxl + 2] = e->t[4].addr[4 * (TT * e->tety + e->tetx) + 2];
}

void	floor_calc(t_wolf *e)
{
	if (e->side == 0 && e->raydirx > 0)
	{
		e->floor_x = (double)e->mapx;
		e->floor_y = (double)e->mapy + e->wallx;
	}
	else if (e->side == 0 && e->raydirx < 0)
	{
		e->floor_x = (double)e->mapx + 1.0;
		e->floor_y = (double)e->mapy + e->wallx;
	}
	else if (e->side == 1 && e->raydiry > 0)
	{
		e->floor_x = (double)e->mapx + e->wallx;
		e->floor_y = (double)e->mapy;
	}
	else
	{
		e->floor_x = (double)e->mapx + e->wallx;
		e->floor_y = (double)e->mapy + 1.0;
	}
}

void	ceiling(t_wolf *e, int y, int x)
{
	int count_pxl;

	count_pxl = pixels(x, y);
	e->addr[count_pxl] = e->t[5].addr[4 * (TT * e->tety + e->tetx)];
	e->addr[count_pxl + 1] = e->t[5].addr[4 * (TT * e->tety + e->tetx) + 1];
	e->addr[count_pxl + 2] = e->t[5].addr[4 * (TT * e->tety + e->tetx) + 2];
}

void	draw_floor(t_wolf *e, int x)
{
	int		y;
	double	d;
	double	fl_x;
	double	fl_y;

	if (e->drawend < 0)
		e->drawend = HEIGHT;
	y = e->drawend + 1;
	floor_calc(e);
	while (y < HEIGHT)
	{
		d = HEIGHT / (2.0 * y - HEIGHT);
		fl_x = d / e->walld * e->floor_x + (1.0 - (d / e->walld)) * e->posx;
		fl_y = d / e->walld * e->floor_y + (1.0 - (d / e->walld)) * e->posy;
		e->tetx = (int)(fl_x * TT) % TT;
		e->tety = (int)(fl_y * TT) % TT;
		floor_put(e, y, x);
		ceiling(e, HEIGHT - y, x);
		y++;
	}
}
