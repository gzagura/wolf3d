/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzagura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 14:07:24 by gzagura           #+#    #+#             */
/*   Updated: 2018/10/18 14:07:26 by gzagura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		pixels(int x, int y)
{
	int		count_pix;

	count_pix = 0;
	count_pix = (x * 4) + ((WIDTH * 4) * y);
	return (count_pix);
}

void	wrip(t_wolf *head, int count_pxl)
{
	head->addr[count_pxl] = head->rgb.col & 0x0000ff;
	head->addr[count_pxl + 1] = (head->rgb.col >> 8) & 0xff;
	head->addr[count_pxl + 2] = (head->rgb.col >> 16);
}

void	verline(t_wolf *e, int x)
{
	int y;
	int i;

	e->camx = e->dirx + e->planex * e->camerax;
	e->camy = e->diry + e->planey * e->camerax;
	y = e->drawstart - 1;
	if (e->side == 0 && e->camx >= 0)
		i = 0;
	else if (e->side == 0 && e->camx < 0)
		i = 1;
	else if (e->side == 1 && e->camy >= 0)
		i = 2;
	else
		i = 3;
	while (++y < e->drawend)
	{
		e->tmp = y * 256 - HEIGHT * 128 + e->lineheight * 128;
		e->texy = ((e->tmp * 64) / e->lineheight) / 256;
		e->rgb.col = e->t[i].addr[e->texx * 4 + e->texy * e->t[i].sl + 2] << 16;
		e->rgb.col += e->t[i].addr[e->texx * 4 + e->texy * e->t[i].sl + 1] << 8;
		e->rgb.col += e->t[i].addr[e->texx * 4 + e->texy * e->t[i].sl];
		if (e->side == 1)
			e->rgb.col = (e->rgb.col >> 1) & 8355711;
		wrip(e, pixels(x, y));
	}
}
