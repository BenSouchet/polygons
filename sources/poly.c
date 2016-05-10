#include "polygons.h"

static int     check_point(t_var *v, int start, int max)
{
    int i;
    int j;
    int c;

    c = 0;
    for (i = start, j = (max - 1); i < max; j = i++)
    {
        if (((v->pts[i][1] >= v->y) != (v->pts[j][1] >= v->y)) &
        (v->x <= (v->pts[j][0] - v->pts[i][0]) * (double)(v->y - v->pts[i][1]) /
        (double)(v->pts[j][1] - v->pts[i][1]) + v->pts[i][0]))
            c = !c;
    }
    return c;
}

static int     odd_polygon_check(t_var *v, int test)
{
    int i;
    int size;
    int add;
    int start;

    test -= (test > v->num) ? v->num : 0 ;
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

static void     apply_transforms(t_var *v, int i, double x, double y)
{
    double  x_new;
    double  y_new;

    if ((v->num % 2) == 0)
    {
        v->pts[i][0] = ((i + 1) % 2) ?
        (round((v->r + (v->odd * v->r / 100)) * x) + v->cx) :
        (round((v->r + (v->even * v->r / 100)) * x) + v->cx);
        v->pts[i][1] = ((i + 1) % 2) ?
        (round((v->r + (v->odd * v->r / 100)) * y) + v->cy) :
        (round((v->r + (v->even * v->r / 100)) * y) + v->cy);
    }
    x_new = cos(v->rot * (PI / 180.0)) * (v->pts[i][0] - v->cx) -
    sin(v->rot * (PI / 180.0)) * (v->pts[i][1] - v->cy) + v->cx;
    y_new = sin(v->rot * (PI / 180.0)) * (v->pts[i][0] - v->cx) +
    cos(v->rot * (PI / 180.0)) * (v->pts[i][1] - v->cy) + v->cy;
    v->pts[i][0] = x_new + (v->width * (x_new - v->cx) / 100);
    v->pts[i][1] = y_new + (v->height * (y_new - v->cy) / 100);
}

static void     get_vertex(t_var *v, int i, double x, int r)
{
    int max;
    int god;
    double y;

    y = 0.0;
    v->a = 0.0;
    max = i + 1;
    v->add = (2 * PI) / v->num;
    while (++i < (max + v->num))
    {
        x = cosf(v->a) * (cosf(PI / v->num) / cosf(2.0 * (PI / v->num) *
        ((v->a / (2.0 * (PI / v->num))) -
        floor(v->a / (2.0 * (PI / v->num)))) - (PI / v->num)));
        y = sinf(v->a) * (cosf(PI / v->num) / cosf(2.0 * (PI / v->num) *
        ((v->a / (2.0 * (PI / v->num))) -
        floor(v->a / (2.0 * (PI / v->num)))) - (PI / v->num)));
        god = (odd_polygon_check(v, i + 1) == 1) ? v->odd : v->even;
        if (v->num % 2)
        {
            v->pts[i][0] = (round((r + (god * r / 100)) * x) + v->cx);
            v->pts[i][1] = (round((r + (god * r / 100)) * y) + v->cy);
        }
        apply_transforms(v, i, x, y);
        v->a += v->add;
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
    v->r = v->rad;
    get_vertex(v, -1, 0.0, v->r);
    while (++v->y <= WIN_H - 1 && (v->x = 213) == 213)
        while (++v->x <= WIN_W - 1)
            if (check_point(v, 0, v->num) == 1)
                put_pixel(v, OBJ_COLOR, 0);
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
    v->pts = (int **)malloc(sizeof(int *) * (v->num * 2));
    while (i < (v->num * 2))
        v->pts[i++] = (int *)malloc(sizeof(int) * 2);
    v->r = v->rad;
    get_vertex(v, -1, 0.0, v->r);
    v->r = v->rad - v->thickness;
    get_vertex(v, (v->num - 1), 0.0, v->r);
    while (++v->y <= WIN_H - 1 && (v->x = 213) == 213)
        while (++v->x <= WIN_W - 1)
            if (check_point(v, 0, v->num) == 1 &&
            check_point(v, v->num, (v->num * 2)) != 1)
                put_pixel(v, OBJ_COLOR, 0);
    i = 0;
    while (i < (v->num * 2))
        free(v->pts[i++]);
    free(v->pts);
}
