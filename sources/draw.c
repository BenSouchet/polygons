/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 18:39:52 by bsouchet          #+#    #+#             */
/*   Updated: 2016/05/11 13:20:07 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "polygons.h"

int		put_pixel(t_var *v, int color, int type)
{
	int		i;
	int		x;
	int		y;
	char	*rgb;

	x = v->x;
	y = v->y;
	if (((type == 1 && x > 213) || (type != 1 && x >= 0))
			&& x < WIN_W && y >= 0 && y < WIN_H)
	{
		i = ((int)v->x * (v->bpp / 8)) + ((int)v->y * v->sl);
		rgb = (char*)&color;
		v->d[i] = rgb[0];
		v->d[++i] = rgb[1];
		v->d[++i] = rgb[2];
	}
	return (0);
}

t_var	*user_interface(t_var *v, int type)
{
	v->y = -1;
	if (type == 1)
		while (++v->y < WIN_H && (v->x = 214) > -1)
			while (v->x < WIN_W && put_pixel(v, BG2_COLOR, 0) == 0)
				v->x++;
	else if (type == 2)
	{
		while (++v->y < WIN_H && (v->x = 0) > -1)
			while (v->x <= 213 && put_pixel(v, BG_COLOR, 0) == 0)
				v->x++;
		v->nam = ft_strjoin("Name : ", dispatch_num(v->num), 1);
		v->len = WIN_W - 50 - ft_strlen(v->nam) * 10;
		v->x = 25;
		v->y = 25;
		mlx_draw(v, 188, 173);
		v->y = 198;
		mlx_draw(v, 188, 286);
		v->y = 311;
		mlx_draw(v, 188, 399);
		v->y = (WIN_H - 65);
		mlx_draw(v, 188, (WIN_H - 25));
		v->x = v->len - 1;
		mlx_draw(v, (WIN_W - 25), (WIN_H - 25));
	}
	return (v);
}

void	user_interface_texts(t_var *v)
{
	mlx_string_put(v->mlx, v->win, 41, 35, UI_COLOR, "Generals Keys");
	mlx_string_put(v->mlx, v->win, 37, 63, UI_COLOR, "Zoom = + and -");
	mlx_string_put(v->mlx, v->win, 37, 83, UI_COLOR, "Edit = ^ v < >");
    mlx_string_put(v->mlx, v->win, 37, 103, UI_COLOR, "Rot8 = X and Z");
	mlx_string_put(v->mlx, v->win, 37, 123, UI_COLOR, "Fill = SHIFT");
	mlx_string_put(v->mlx, v->win, 37, 143, UI_COLOR, "Reset = CLEAR");
	mlx_string_put(v->mlx, v->win, 37, 208, UI_COLOR, "Control Vertex");
	mlx_string_put(v->mlx, v->win, 37, 236, UI_COLOR, "Odd  = W and Q");
	mlx_string_put(v->mlx, v->win, 37, 256, UI_COLOR, "Even = S and A");
	mlx_string_put(v->mlx, v->win, 41, 321, UI_COLOR, "Poly Explorer");
	if (v->num > 1)
		mlx_string_put(v->mlx, v->win, 37, 349, UI_COLOR, "Prev = PAGE UP");
	else
		mlx_string_put(v->mlx, v->win, 37, 349, UI2_COLOR, "Prev = PAGE UP");
	if (v->num < MAX_V)
		mlx_string_put(v->mlx, v->win, 37, 369, UI_COLOR, "Next = PAGE DW");
	else
		mlx_string_put(v->mlx, v->win, 37, 369, UI2_COLOR, "Next = PAGE DW");
	mlx_string_put(v->mlx, v->win, v->len + 11, (WIN_H - 55), UI_COLOR, v->nam);
	free(v->nam);
	v->size = ft_strjoin("Sides : ", ft_itoa(v->num), 1);
	mlx_string_put(v->mlx, v->win, 37, (WIN_H - 55), UI_COLOR, v->size);
	free(v->size);
}

void	mlx_draw(t_var *v, int x, int y)
{
	int tmp1;
	int tmp2;

	tmp1 = v->x;
	tmp2 = v->y;
	while (v->x <= x && put_pixel(v, UI_COLOR, 0) == 0)
		v->x++;
	while (v->y <= y && put_pixel(v, UI_COLOR, 0) == 0)
		v->y++;
	while (v->x >= tmp1 && put_pixel(v, UI_COLOR, 0) == 0)
		v->x--;
	while (v->y >= tmp2 && put_pixel(v, UI_COLOR, 0) == 0)
		v->y--;
}

int		check_point(t_var *v, int start, int max)
{
	int i;
	int j;
	int c;

	c = 0;
	i = start;
	j = (max - 1);
	while (i < max)
	{
		if (((v->pts[i][1] >= v->y) != (v->pts[j][1] >= v->y)) &
		(v->x <= (v->pts[j][0] - v->pts[i][0]) * (double)(v->y - v->pts[i][1]) /
		(double)(v->pts[j][1] - v->pts[i][1]) + v->pts[i][0]))
			c = !c;
		j = i++;
	}
	return (c);
}
