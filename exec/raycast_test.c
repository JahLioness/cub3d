/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:25:19 by ede-cola          #+#    #+#             */
/*   Updated: 2025/01/30 13:00:17 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	ft_get_player_pos(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < ft_tab_len(data->map->map_tab))
	{
		j = 0;
		while (j < ft_strlen(data->map->map_tab[i]))
		{
			if (data->map->map_int[i][j] == 3)
			{
				data->player->pos_y = (double)i;
				data->player->pos_x = (double)j;
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	draw_floor(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (data->map->map_tab[y] && y < data->map->height)
	{
		while (data->map->map_tab[y][x] && x < data->map->width)
		{
			if ((data->map->map_int[y][x] == 0 || data->map->map_int[y][x] == 3)
				&& data->map->map_int[y][x] != 1
				&& data->map->map_int[y][x] != 2)
				mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
					data->mlx->img[0]->img, x * (PIXEL + 2), y * (PIXEL + 2));
			x++;
		}
		x = 0;
		y++;
	}
}

void	draw_wall(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (data->map->map_tab[y] && y < data->map->height)
	{
		while (data->map->map_tab[y][x] && x < data->map->width)
		{
			if (data->map->map_int[y][x] == 1)
				mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
					data->mlx->img[1]->img, x * (PIXEL + 2), y * (PIXEL + 2));
			x++;
		}
		x = 0;
		y++;
	}
}
void	draw_player(t_data *data)
{
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
		data->mlx->img[2]->img, data->player->pos_x * (PIXEL + 2),
		data->player->pos_y * (PIXEL + 2));
}

void	draw_ray(t_data *data)
{
	double	ray_angle;
	int		i;

	i = 0;
	ray_angle = data->player->player_angle - (60 / 2);
	while (i < 50)
	{
		while (data->player->pos_x >= 0
			&& data->player->pos_x < data->map->width
			&& data->player->pos_y >= 0
			&& data->player->pos_y < data->map->height)
		{
			data->player->delta_x += cos(data->player->player_angle) * 0.1;
			data->player->delta_y += sin(data->player->player_angle) * 0.1;
			if (data->map->map_int[(int)data->player->delta_y][(int)data->player->delta_x] == 1)
			{
				mlx_pixel_put(data->mlx->mlx, data->mlx->win,
					(data->player->pos_x * PIXEL) + data->player->delta_x, (data->player->pos_y * PIXEL) + data->player->delta_y, 0xFFFF00);
				break ;
			}
		}
		i++;
		ray_angle += 0.1;
	}
}

int	press_key(unsigned int keycode, t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = 0;
	new_y = 0;
	printf("pos_x = %f\n", data->player->pos_x);
	printf("pos_y = %f\n", data->player->pos_y);
	printf("player[%d][%d] = %d\n", (int)data->player->pos_y,
		(int)data->player->pos_x,
		data->map->map_int[(int)data->player->pos_y][(int)data->player->pos_x]);
	mlx_clear_window(data->mlx->mlx, data->mlx->win);
	if (keycode == KEY_ESC)
	{
		ft_free_data(data);
		exit(0);
	}
	if (keycode == KEY_A)
	{
		if (data->player->player_angle < 0)
			data->player->player_angle += PI;
		data->player->delta_x = cos(data->player->player_angle) * 0.1;
		data->player->delta_y = sin(data->player->player_angle) * 0.1;
		new_x = data->player->pos_x - data->player->delta_x * 5;
		new_y = data->player->pos_y + data->player->delta_y * 5;
		if (data->map->map_int[(int)new_y][(int)new_x] != 1)
		{
			data->player->pos_x = new_x;
			data->player->pos_y = new_y;
		}
	}
	if (keycode == KEY_D)
	{
		if (data->player->player_angle > PI)
			data->player->player_angle -= PI;
		data->player->delta_x = cos(data->player->player_angle) * 0.1;
		data->player->delta_y = sin(data->player->player_angle) * 0.1;
		new_x = data->player->pos_x + data->player->delta_x * 5;
		new_y = data->player->pos_y - data->player->delta_y * 5;
		if (data->map->map_int[(int)new_y][(int)new_x] != 1)
		{
			data->player->pos_x = new_x;
			data->player->pos_y = new_y;
		}
	}
	if (keycode == KEY_W)
	{
		data->player->delta_x = cos(data->player->player_angle) * 0.1;
		data->player->delta_y = sin(data->player->player_angle) * 0.1;
		new_x = data->player->pos_x + data->player->delta_y * 5;
		new_y = data->player->pos_y - data->player->delta_x * 5;
		if (data->map->map_int[(int)new_y][(int)new_x] != 1)
		{
			data->player->pos_x = new_x;
			data->player->pos_y = new_y;
		}
	}
	if (keycode == KEY_S)
	{
			data->player->delta_x = cos(data->player->player_angle) * 0.1;
		data->player->delta_y = sin(data->player->player_angle) * 0.1;
		new_x = data->player->pos_x - data->player->delta_y * 5;
		new_y = data->player->pos_y + data->player->delta_x * 5;
		if (data->map->map_int[(int)new_y][(int)new_x] != 1)
		{
			data->player->pos_x = new_x;
			data->player->pos_y = new_y;
		}
	}
	draw_floor(data);
	draw_wall(data);
	draw_player(data);
	draw_ray(data);
	return (0);
}
