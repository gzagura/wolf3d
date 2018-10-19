/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzagura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 13:18:28 by gzagura           #+#    #+#             */
/*   Updated: 2018/10/18 13:21:12 by gzagura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include <mlx.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <math.h>

# define WIDTH 800
# define HEIGHT 800
# define TT 64

typedef struct			s_images
{
	void				*img;
	char				*addr;
	int					bpp;
	int					sl;
	int					endl;
}						t_img;

typedef struct			s_rgb
{
	int					r;
	int					g;
	int					b;
	int					col;
}						t_rgb;

typedef struct			s_wolf
{
	t_img				t[6];
	double				wallx;
	double				floor_x;
	double				floor_y;
	int					texx;
	int					texy;
	int					lineheight;
	double				camx;
	double				camy;
	void				*mlx;
	void				*wind;
	int					**map;
	double				posx;
	double				posy;
	double				dirx;
	double				diry;
	double				planex;
	double				planey;
	double				camerax;
	double				raydirx;
	double				raydiry;
	int					mapx;
	int					mapy;
	int					side;
	int					hit;
	int					stepx;
	int					stepy;
	int					drawstart;
	int					drawend;
	double				sidedistx;
	double				sidedisty;
	double				deltadistx;
	double				deltadisty;
	double				walld;
	double				move;
	double				rot;
	int					tetx;
	int					tety;
	int					tmp;
	int					map_w;
	int					map_h;
	char				*addr;
	int					bits_per_pixel;
	int					size_line;
	int					endian;
	void				*img;
	t_rgb				rgb;
}						t_wolf;

void					valid2(t_wolf *e);
void					invalid(void);
void					valid(t_wolf *head, char *str);
void					transform_data(t_wolf *head, char *str, int i);
void					write_data(t_wolf *head, char *str);
void					prep_dda(t_wolf *e);
void					dda(t_wolf *e);
void					math(t_wolf *e, int x);
void					floor_put(t_wolf *e, int y, int x);
void					floor_calc(t_wolf *e);
void					ceiling(t_wolf *e, int y, int x);
void					verline(t_wolf *e, int x);
void					wrip(t_wolf *head, int count_pxl);
void					draw_floor(t_wolf *e, int x);
void					position(t_wolf *e);
void					ft_usage(void);
void					init2(t_wolf *e);
void					init(t_wolf *e);
int						le_hook(int key, t_wolf *e);
int						pixels(int x, int y);
void					invalid(void);
char					*ft_strjoinfree(const char *s1, const char *s2, int n);
int						ft_esc(t_wolf *head);
void					ft_usage(void);
void					le_hook_help(t_wolf *e, int key);
void					tata(t_wolf *head);
void					draw(t_wolf *e);

#endif
