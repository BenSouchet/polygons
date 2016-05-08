/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 18:35:58 by bsouchet          #+#    #+#             */
/*   Updated: 2016/05/05 19:30:22 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "polygons.h"

int				expose_hook(t_var *v)
{
    v->rot = (v->num % 2) ? -90.0 : 0.0;
	v->img = mlx_new_image(v->mlx, WIN_W, WIN_H);
	v->d = mlx_get_data_addr(v->img, &v->bpp, &v->sl, &v->end);
	v = user_interface(v, 1);
	draw_polygon(v);
	v = user_interface(v, 2);
	mlx_put_image_to_window(v->mlx, v->win, v->img, 0, 0);
	user_interface_texts(v);
	return (0);
}

int				key_hook(int keycode, t_var *v)
{
	if (keycode == 53)
	{
		mlx_destroy_image(v->mlx, v->img);
		mlx_destroy_window(v->mlx, v->win);
		exit(0);
	}
	else
	{
		if (keycode == 69)
			v->rad += 10;
		else if (keycode == 78 && v->rad > 30)
			v->rad -= 10;
		else if (keycode == 121 && v->num < 360)
			v->num++;
		else if (keycode == 71 && (v->rad = 280) == 280)
			v->num = (v->nbr == 2) ? ft_atoi(v->ftl[1]) : 1;
		else if (keycode == 116 && v->num > 1)
			v->num--;
        else if (keycode == 123 && v->width > -100)
            v->width -= 5;
        else if (keycode == 124)
            v->width += 5;
        else if (keycode == 125 && v->height > -100)
            v->height -= 5;
        else if (keycode == 126)
            v->height += 5;
		/*if (keycode >= 0 && keycode < 80)
			v = key_hook_rotate(v, keycode);
		else if (keycode > 110 && keycode < 130)
			v = key_hook_translate(v, keycode);*/
		mlx_destroy_image(v->mlx, v->img);
		mlx_clear_window(v->mlx, v->win);
		expose_hook(v);
	}
	return (0);
}

int				close_hook(int button, t_var *v)
{
	(void)button;
	(void)v;
	exit(0);
	return (0);
}
