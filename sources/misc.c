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

static int     check_point(t_var *v)
{
    int i;
    int j;
    int c;

    c = 0;
    for (i = 0, j = v->num-1; i < v->num; j = i++)
    {
        if (((v->pts[i][1] >= v->y) != (v->pts[j][1] >= v->y)) &
        (v->x <= (v->pts[j][0] - v->pts[i][0]) * (float)(v->y - v->pts[i][1]) /
        (float)(v->pts[j][1] - v->pts[i][1]) + v->pts[i][0]))
            c = !c;
    }
    return c;
}

static void     get_vertex(t_var *v, int i)
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
        v->pts[i][0] = (round((v->rad) * x) + (v->cx));
        v->pts[i++][1] = (round((v->rad) * y) + (v->cy));
        a += god;
    }
}

void            apply_transforms(t_var *v, int i)
{
    double  x_new;
    double  y_new;

    x_new = cos(v->rot * (PI / 180.0)) * (v->pts[i][0] - v->cx) -
    sin(v->rot * (PI / 180.0)) * (v->pts[i][1] - v->cy) + v->cx;
    y_new = sin(v->rot * (PI / 180.0)) * (v->pts[i][0] - v->cx) +
    cos(v->rot * (PI / 180.0)) * (v->pts[i][1] - v->cy) + v->cy;
    v->pts[i][0] = x_new + (v->width * (x_new - v->cx) / 100);
    v->pts[i][1] = y_new + (v->height * (y_new - v->cy) / 100);
}

void            draw_polygon(t_var *v)
{
    int i;

    i = -1;
    v->y = 0;
    v->pts = (int **)malloc(sizeof(int *) * v->num);
    while (i < v->num)
        v->pts[i++] = (int *)malloc(sizeof(int) * 2);
    get_vertex(v, 0);
    i = -1;
    while (++i < v->num)
        apply_transforms(v, i);
    while (++v->y <= WIN_H - 1)
    {
        v->x = 213;
        while (++v->x <= WIN_W - 1)
            if (check_point(v) == 1)
                put_pixel(v, OBJ_COLOR, 0);
    }
    i = 0;
    while (i < v->num)
        free(v->pts[i++]);
    free(v->pts);
}
