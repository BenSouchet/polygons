/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 18:03:16 by bsouchet          #+#    #+#             */
/*   Updated: 2016/05/04 18:04:37 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "polygons.h"

void	draw_circle(t_var *v, int radius)
{
	double x;
	double y;
	double degree;

	degree = 0.0f;
	x = v->cx;
	y = v->cy - radius;
	while (degree <= 360.0)
	{
		v->x = cos(degree * (PI / 180.0f)) * (x - v->cx) -
		sin(degree * (PI / 180.0f)) * (y - v->cy) + v->cx;
		v->y = sin(degree * (PI / 180.0f)) * (x - v->cx) +
		cos(degree * (PI / 180.0f)) * (y - v->cy) + v->cy;
		put_pixel(v, OBJ2_COLOR, 1);
		degree += 0.1;
	}
}

void	draw_polygon(t_var *v, int radius)
{
	int		count;
	int		max;
	double	x;
	double	y;
	double	tmp_x;
	double	tmp_y;
	double	tmp2_x;
	double	tmp2_y;
	double	angle;
	double	total;

	count = 0;
	max = (v->num < 3) ? 3600 : v->num;
	x = v->cx;
	y = v->cy - (radius - 14);
	total = 0.0;
	angle = (v->num < 3) ? 0.1 : 360.0 / (double)v->num;
	if (!(v->num % 2))
	{
		v->x = cos((angle / 2.0) * (PI / 180.0f)) * (x - v->cx) -
		sin((angle / 2.0) * (PI / 180.0f)) * (y - v->cy) + v->cx;
		v->y = sin((angle / 2.0) * (PI / 180.0f)) * (x - v->cx) +
		cos((angle / 2.0) * (PI / 180.0f)) * (y - v->cy) + v->cy;
		x = v->x;
		y = v->y;
	}
	tmp_x = x;
	tmp_y = y;
	while (count++ <= max)
	{
		v->x = cos(total * (PI / 180.0f)) * (x - v->cx) -
		sin(total * (PI / 180.0f)) * (y - v->cy) + v->cx;
		v->y = sin(total * (PI / 180.0f)) * (x - v->cx) +
		cos(total * (PI / 180.0f)) * (y - v->cy) + v->cy;
		tmp2_x = v->x;
		tmp2_y = v->y;
		draw_line(v, tmp_x, tmp_y);
		total += angle;
		tmp_x = tmp2_x;
		tmp_y = tmp2_y;
	}
}
