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
#include <stdio.h>

/*int     point_in_polygon(t_var *v, int i, int r)
{
    int j;

    j = v->num - 1;
    while (i < v->num)
    {
        if (((v->pts[i][1] >= v->y) != (v->pts[j][1] >= v->y)) &&
        (v->x <= (v->pts[j][0] - v->pts[i][0]) * (v->y - v->pts[i][1]) /
        (v->pts[j][1] - v->pts[i][1]) + v->pts[i][0]))
            r = 1;
        j = i++;
    }
    return (r);
}*/

static int     check_point(t_var *v)
{
    int i, j, c = 0;
    for (i = 0, j = v->num-1; i < v->num; j = i++) {
    if (((v->pts[i][1] >= v->y) != (v->pts[j][1] >= v->y)) &
    (v->x <= (v->pts[j][0] - v->pts[i][0]) * (float)(v->y - v->pts[i][1]) /
    (float)(v->pts[j][1] - v->pts[i][1]) + v->pts[i][0]))
        c = !c;
    }
    return c;
}

static void     get_vertex(t_var *v, int radius, int i)
{
    double x;
    double y;
    double a;
    double god;

    a = 0.0;
    god = (2 * PI) / v->num;
    while (i < v->num)
    {
        x = cosf(a) * (cosf(PI / v->num) / cosf(2.0 * (PI / v->num) *
        ((a / (2.0 * (PI / v->num))) - floor(a / (2.0 * (PI / v->num)))) -
        (PI / v->num)));
        y = sinf(a) * (cosf(PI / v->num) / cosf(2.0 * (PI / v->num) *
        ((a / (2.0 * (PI / v->num))) - floor(a / (2.0 * (PI / v->num)))) -
        (PI / v->num)));
        v->pts[i][0] = (round((radius) * x) + (v->cx));
        v->pts[i++][1] = (round((radius) * y) + (v->cy));
        a += god;
    }
}

void            draw_polygon(t_var *v, int radius)
{
    int i;

    i = 0;
    v->y = v->cy - radius - 1;
    v->pts = (int **)malloc(sizeof(int *) * v->num);
    while (i < v->num)
        v->pts[i++] = (int *)malloc(sizeof(int) * 2);
    get_vertex(v, radius, 0);
    while (++v->y <= (v->cy + radius))
    {
        v->x = v->cx - radius - 1;
        while (++v->x <= (v->cx + radius))
            if (check_point(v) == 1)
                put_pixel(v, OBJ_COLOR, 0);
    }
    i = 0;
    while (i < v->num)
        free(v->pts[i++]);
    free(v->pts);
}
