/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 18:03:16 by bsouchet          #+#    #+#             */
/*   Updated: 2016/05/05 19:33:19 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "polygons.h"

int		draw_new_algo(t_var *v, int radius)
{
	double x;
	double y;
	double a;
	double god;

	a = 0.0;
	god = (2 * PI) / v->num;
	while (a <= (2 * PI))
	{
		x = cosf(a) * (cosf(PI / v->num) / cosf(2.0 * (PI / v->num) *
		((a / (2.0 * (PI / v->num))) - floor(a / (2.0 * (PI / v->num)))) -
		(PI / v->num)));
		y = sinf(a) * (cosf(PI / v->num) / cosf(2.0 * (PI / v->num) *
		((a / (2.0 * (PI / v->num))) - floor(a / (2.0 * (PI / v->num)))) -
		(PI / v->num)));
		v->x = (round((radius) * x) + (v->cx));
		v->y = (round((radius) * y) + (v->cy));
		put_pixel(v, OBJ_COLOR, 1);
		a += god;
	}
	return (0);
}
