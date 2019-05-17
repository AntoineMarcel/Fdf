/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 18:42:11 by amarcel           #+#    #+#             */
/*   Updated: 2019/05/17 18:42:15 by amarcel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_init.h"

t_point		**ft_switch_iso(t_fdf *ptr)
{
	int i;
	int j;

	j = 0;
	while (j < ptr->nb_line)
	{
		i = 0;
		while (i < ptr->nb_col)
		{
			ptr->tab[j][i].x2 = ((sqrt(2) / 2)\
			* (ptr->tab[j][i].x - ptr->tab[j][i].y));
			ptr->tab[j][i].y2 = (sqrt(2.0 / 3.0) * ptr->tab[j][i].z)\
			- ((ptr->tab[j][i].x + ptr->tab[j][i].y) / sqrt(6));
			i++;
		}
		j++;
	}
	return (ptr->tab);
}

int			key_function_part_1(int keycode, t_fdf *ptr)
{
	char *str;

	str = ft_strdup("\nTUTO\n\nR : red\nG : green\nB : blue\n\
	W : white\narrows : moove\n+ : higher\n- : lower\n");
	if (keycode == 1)
		ft_putendl(str);
	free(str);
	if (keycode == 35)
	{
		mlx_clear_window(ptr->mlx_ptr, ptr->win_ptr);
		if (ptr->current_proj == ISOMETRIC_PROJECTION)
		{
			set_proj(ptr);
			ptr->current_proj = PARALLEL_PROJECTION;
		}
		else if (ptr->current_proj == PARALLEL_PROJECTION)
		{
			ft_switch_iso(ptr);
			ptr->current_proj = ISOMETRIC_PROJECTION;
		}
		testprint(ptr);
	}
	return (0);
}

int			key_function_part_2(int keycode, t_fdf *ptr)
{
	if (keycode == 69)
	{
		ptr->high += 5;
		set_high(ptr);
		mlx_clear_window(ptr->mlx_ptr, ptr->win_ptr);
		ft_switch_iso(ptr);
		testprint(ptr);
	}
	if (keycode == 78)
	{
		ptr->high -= 5;
		set_high(ptr);
		mlx_clear_window(ptr->mlx_ptr, ptr->win_ptr);
		ft_switch_iso(ptr);
		testprint(ptr);
	}
	if (keycode == 53)
	{
		free(ptr);
		exit(0);
	}
	return (0);
}

int			key_function(int keycode, t_fdf *ptr)
{
	key_function_part_1(keycode, ptr);
	key_function_part_2(keycode, ptr);
	set_color(keycode, ptr);
	set_offset_x(keycode, ptr);
	set_offset_y(keycode, ptr);
	return (0);
}

void		ft_init_window(t_fdf *ptr)
{
	ptr->mlx_ptr = mlx_init();
	ptr->win_ptr = mlx_new_window(ptr->mlx_ptr, ptr->res_width\
	, ptr->res_height, "fdf");
	if (ptr->current_proj == ISOMETRIC_PROJECTION)
		ft_switch_iso(ptr);
	else if (ptr->current_proj == PARALLEL_PROJECTION)
		set_proj(ptr);
	testprint(ptr);
	mlx_key_hook(ptr->win_ptr, key_function, ptr);
	mlx_loop(ptr->mlx_ptr);
}
