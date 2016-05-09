/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 17:30:09 by bsouchet          #+#    #+#             */
/*   Updated: 2016/05/04 18:06:36 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "polygons.h"

static int		error(int type)
{
	if (type == 0)
		write(2, MSG00, 33);
	else if (type == 1)
		write(2, MSG01, 51);
	else if (type == 2)
		write(2, MSG02, 62);
	write(2, "\n", 1);
	return (-1);
}

static int		check(t_var *v, int err)
{
	v->rad = 280;
    v->odd = 280;
    v->even = 280;
    v->width = 0;
    v->height = 0;
	v->cx = (213.0 + ((WIN_W - 213.0) / 2.0));
	v->cy = (35.0 + ((WIN_H - 116.0) / 2.0));
	if (v->nbr == 1 || (v->nbr == 2 && ft_atoi(v->ftl[1]) > 0 &&
		ft_atoi(v->ftl[1]) < 361))
		;
	else if (v->nbr == 2 && (v->ftl[1][0] < 48 || v->ftl[1][0] > 57)
		&& ++err > 0)
		error(0);
	else if (++err > 0)
		error(2);
	return (err);
}

static int		init_win(t_var v)
{
	v.mlx = mlx_init();
	v.num = (v.nbr == 2) ? ft_atoi(v.ftl[1]) : 1;
    v.img = mlx_new_image(v.mlx, WIN_W, WIN_H);
	v.win = mlx_new_window(v.mlx, -1, -1, WIN_W, WIN_H, "polygons - bsouchet");
	v.d = mlx_get_data_addr(v.img, &v.bpp, &v.sl, &v.end);
	mlx_expose_hook(v.win, expose_hook, &v);
	mlx_hook(v.win, 17, 0, close_hook, &v);
	mlx_hook(v.win, 2, 0, key_hook, &v);
	mlx_do_key_autorepeaton(v.mlx);
	mlx_loop(v.mlx);
	exit(0);
	return (0);
}

int				main(int ac, char **av)
{
	t_var v;

	v.num = 1;
	v.nbr = ac;
	v.ftl = av;
	if (ac > 2)
		return (error(0));
	else if (WIN_W < 1024 || WIN_H < 576)
		return (error(1));
	else if (check(&v, 0) > 0)
		return (-1);
	else
		init_win(v);
	return (0);
}
