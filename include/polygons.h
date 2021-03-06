/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygons.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 17:26:10 by bsouchet          #+#    #+#             */
/*   Updated: 2016/05/11 13:25:20 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POLYGONS_H
# define POLYGONS_H

# include <math.h>
# include "../libft/include/libft.h"
# include "../libmlx/includes/mlx.h"

# define PI 3.14159265359
# define BG_COLOR 0x353535
# define BG2_COLOR 0x2D2D2D
# define UI_COLOR 0x84AC00
# define UI2_COLOR 0x647C15
# define OBJ_COLOR 0x777777
# define OBJ2_COLOR 0x373737
# define RADIUS 280
# define MIN_V 105
# define MAX_V 360
# define WIN_W 1280
# define WIN_H 720

# define MSG00 "usage: ./polygons number_of_sides"
# define MSG01 "error: Window size must be greater than 1024 x 576"
# define MSG02 "error : the number of sides as to be a value between 1 and 360"

typedef struct	s_var
{
	int			x;
	int			y;
	int			r;
	double		a;
	double		cx;
	double		cy;
	double		add;
	int			sl;
	int			len;
	int			nbr;
	int			num;
	int			bpp;
	int			end;
	int			rad;
	int			odd;
	int			tmp;
	int			even;
	int			fill;
	int			thickness;
	double		rot;
	double		width;
	double		height;
	int			**pts;
	char		*d;
	char		*nam;
	char		*size;
	char		**ftl;
	void		*img;
	void		*mlx;
	void		*win;
}				t_var;

int				expose_hook(t_var *v);
int				key_hook(int keycode, t_var *v);
int				close_hook(int button, t_var *v);

int				put_pixel(t_var *v, int color, int type);
t_var			*user_interface(t_var *v, int type);
void			user_interface_texts(t_var *v);

void			mlx_draw(t_var *v, int x, int y);

char			*dispatch_num(int num);

int				check_point(t_var *v, int start, int max);

void			draw_edge_polygon(t_var *v);
void			draw_full_polygon(t_var *v);

#endif
