#include <stdio.h>
#include <math.h>

#define PI 3.14159265359

void         omg_bro(int num_points, int dimension)
{
    int i;
    double x;
    double y;
    double cx;
    double cy;
    double tmp;
    double angle;
    double rotz_x;
    double rotz_y;

    i = 0;
    tmp = 0.0f;
    x = (double)dimension / 2.0f;
    y = 0;
    cx = (double)dimension / 2.0f;
    cy = (double)dimension / 2.0f;
    angle = (num_points < 360) ? 360.0f / (double)num_points : 360;
    while (i++ < num_points)
    {
        rotz_x = cos(tmp * (PI / 180.0f)) * (x - cx) -
        sin(tmp * (PI / 180.0f)) * (y - cy) + cx;
        rotz_y = sin(tmp * (PI / 180.0f)) * (x - cx) +
        cos(tmp * (PI / 180.0f)) * (y - cy) + cy;
        //printf("angle : %f --- x : %f --- y : %f\n", tmp, rotz_x, rotz_y);
        tmp += angle;
    }
}

int         main(void)
{
    omg_bro(11, 10);
    printf("\n");
    //omg_bro(4, 10);
    return (0);
}
