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
        (v->x <= (v->pts[j][0] - v->pts[i][0]) * (double)(v->y - v->pts[i][1]) /
        (double)(v->pts[j][1] - v->pts[i][1]) + v->pts[i][0]))
            c = !c;
    }
    return c;
}

static void     draw_point(t_var *v)
{
    int i;
    int j;
    int c;

    c = 0;
    for (i = 0, j = v->num-1; i < v->num; j = i++)
    {
        if (((v->pts[j][0] - v->pts[i][0]) * (v->y - v->pts[i][1])
        - (v->x - v->pts[i][0]) * (v->pts[j][1] - v->pts[i][1])) == 0)
            put_pixel(v, OBJ_COLOR, 0);
    }
}

int     odd_polygon_check(t_var *v, int test)
{
    int i;
    int size; 
    int add; 
    int start;

    size = trunc(v->num / 2);
    add = (test > size) ? 1 : 0;
    start = (size % 2) ? 1 : 2;
    i = start;
    if (i > test)
        return (0);
    while (i <= v->num)
    {
        if (test == start)
            return (1);
        start += 2;
        if (i == ceil(size / 2) + 1)
            start++;
        i++;
    }
    return (0);
}

static void     apply_transforms(t_var *v, int i)
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

static void     get_vertex(t_var *v, int i, double x, double y)
{
    v->a = 0.0;
    v->add = (2 * PI) / v->num;
    while (i < v->num)
    {
        x = cosf(v->a) * (cosf(PI / v->num) / cosf(2.0 * (PI / v->num) *
        ((v->a / (2.0 * (PI / v->num))) - floor(v->a / (2.0 * (PI / v->num)))) -
        (PI / v->num)));
        y = sinf(v->a) * (cosf(PI / v->num) / cosf(2.0 * (PI / v->num) *
        ((v->a / (2.0 * (PI / v->num))) - floor(v->a / (2.0 * (PI / v->num)))) -
        (PI / v->num)));
        if (v->num % 2)
        {
            if (odd_polygon_check(v, i + 1) == 1)
            {
                v->pts[i][0] = (round((v->rad + (v->odd * v->rad / 100)) * x) + v->cx);
                v->pts[i][1] = (round((v->rad + (v->odd * v->rad / 100)) * y) + v->cy);
            }
            else
            {
                v->pts[i][0] = (round((v->rad + (v->even * v->rad / 100)) * x) + v->cx);
                v->pts[i][1] = (round((v->rad + (v->even * v->rad / 100)) * y) + v->cy);
            }
        }
        else
        {
            v->pts[i][0] = ((i + 1) % 2) ? (round((v->rad + (v->odd * v->rad / 100)) * x) + v->cx) :
            (round((v->rad + (v->even * v->rad / 100)) * x) + v->cx);
            v->pts[i][1] = ((i + 1) % 2) ? (round((v->rad + (v->odd * v->rad / 100)) * y) + v->cy) :
            (round((v->rad + (v->even * v->rad / 100)) * y) + v->cy);
        }
        v->a += v->add;
        apply_transforms(v, i);
        i++;
    }
}

void            draw_full_polygon(t_var *v)
{
    int i;

    i = 0;
    v->y = 0;
    v->pts = (int **)malloc(sizeof(int *) * v->num);
    while (i < v->num)
        v->pts[i++] = (int *)malloc(sizeof(int) * 2);
    get_vertex(v, 0, 0.0, 0.0);
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

void            draw_edge_polygon(t_var *v)
{
    int i;

    i = 0;
    v->y = 0;
    v->pts = (int **)malloc(sizeof(int *) * v->num);
    while (i < v->num)
        v->pts[i++] = (int *)malloc(sizeof(int) * 2);
    get_vertex(v, 0, 0.0, 0.0);
    i = -1;
    while (++i < v->num)
        apply_transforms(v, i);
    while (++v->y <= WIN_H - 1)
    {
        v->x = 213;
        while (++v->x <= WIN_W - 1)
            draw_point(v);
    }
    i = 0;
    while (i < v->num)
        free(v->pts[i++]);
    free(v->pts);
}
