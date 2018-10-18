/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_work.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzagura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 12:17:30 by gzagura           #+#    #+#             */
/*   Updated: 2018/10/18 12:17:32 by gzagura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	valid2(t_wolf *e)
{
	int		i;
	int		j;

	i = 0;
	if (e->map_h < 3 || e->map_w < 3)
		invalid();
	while (i < e->map_h)
	{
		j = 0;
		if (e->map[i][0] < 1)
			invalid();
		if (e->map[i][e->map_w - 1] < 1)
			invalid();
		while (j < e->map_w)
		{
			if (e->map[0][j] < 1)
				invalid();
			if (e->map[e->map_h - 1][j] < 1)
				invalid();
			j++;
		}
		i++;
	}
}

void	invalid(void)
{
	ft_putstr("invalid map\n");
	exit(1);
}

void	valid(t_wolf *head, char *str)
{
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	head->map_w = i;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			if (j != head->map_w)
				invalid();
			j = -1;
			head->map_h += 1;
		}
		j++;
		i++;
	}
}

void	transform_data(t_wolf *head, char *str, int i)
{
	int		j;
	int		w;

	j = 0;
	head->map = (int**)malloc(sizeof(int*) * (head->map_h));
	w = -1;
	while (++w < head->map_h)
		head->map[w] = (int*)malloc(sizeof(int) * head->map_w);
	w = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			j = -1;
			w++;
		}
		if ((str[i] < '0' || str[i] > '9') && str[i] != '\n')
			invalid();
		if (str[i] >= '0' && str[i] <= '9')
		{
			head->map[w][j] = (int)(str[i] - 48);
		}
		i++;
		j++;
	}
}

void	write_data(t_wolf *head, char *str)
{
	char	*buffer;
	char	*tmp;
	int		fd;

	if ((fd = open(str, O_RDONLY)) < 0)
		ft_usage();
	buffer = NULL;
	tmp = ft_strnew(1);
	while (get_next_line(fd, &buffer) > 0)
	{
		tmp = ft_strjoinfree(tmp, buffer, 3);
		tmp = ft_strjoinfree(tmp, "\n", 1);
	}
	valid(head, tmp);
	transform_data(head, tmp, 0);
	free(tmp);
	valid2(head);
}
