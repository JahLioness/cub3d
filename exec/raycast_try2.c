/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_try2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:38:22 by ede-cola          #+#    #+#             */
/*   Updated: 2025/02/07 06:26:18 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int ft_get_player_dir(t_data *data)
{
	size_t i;
	size_t j;

	i = 0;
	while (i < ft_tab_len(data->map->map_tab))
	{
		j = 0;
		while (j < ft_strlen(data->map->map_tab[i]))
		{
			if (data->map->map_tab[i][j] == 'N')
			{
				data->raycast->dir_x = 0;
				data->raycast->dir_y = -1;
			}
			else if (data->map->map_tab[i][j] == 'S')
			{
				data->raycast->dir_x = 0;
				data->raycast->dir_y = 1;
			}
			else if (data->map->map_tab[i][j] == 'E')
			{
				data->raycast->dir_x = 1;
				data->raycast->dir_y = 0;
			}
			else if (data->map->map_tab[i][j] == 'W')
			{
				data->raycast->dir_x = -1;
				data->raycast->dir_y = 0;
			}
			j++;
		}
		i++;
	}
	return (1);
}

int ft_get_player_pos(t_data *data)
{
	size_t i;
	size_t j;

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

void draw_floor(t_data *data)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (data->map->map_tab[y] && y < data->map->height)
	{
		while (data->map->map_tab[y][x] && x < data->map->width)
		{
			if ((data->map->map_int[y][x] == 0 || data->map->map_int[y][x] == 3) && data->map->map_int[y][x] != 1 && data->map->map_int[y][x] != 2)
				mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
										data->mlx->img[0]->img, x * (PIXEL + 2), y * (PIXEL + 2));
			x++;
		}
		x = 0;
		y++;
	}
}

void draw_wall(t_data *data)
{
	int x;
	int y;

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

void draw_player(t_data *data)
{
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
							data->mlx->img[2]->img, data->player->pos_x * (PIXEL + 2),
							data->player->pos_y * (PIXEL + 2));
}

void draw_ray(t_data *data)
{
	int i;

	i = 0;
	printf("dir_x = %f\n", data->raycast->dir_x);
	printf("dir_y = %f\n", data->raycast->dir_y);
	printf("plane_x = %f\n", data->raycast->plane_x);
	printf("plane_y = %f\n", data->raycast->plane_y);
	printf("ray_x = %f\n", data->raycast->ray_x);
	printf("ray_y = %f\n", data->raycast->ray_y);
	while (i < data->map->width)
	{
		double camera_x = 2 * data->player->pos_x / data->map->width - 1;
		double camera_y = 2 * data->player->pos_y / data->map->height - 1;
		data->raycast->ray_x = data->raycast->dir_x + data->raycast->plane_x * camera_x;
		data->raycast->ray_y = data->raycast->dir_y + data->raycast->plane_y * camera_y;
		data->raycast->delta_x = (data->raycast->ray_x == 0) ? 1e30 : fabs(1 / data->raycast->ray_x);
		data->raycast->delta_y = (data->raycast->ray_y == 0) ? 1e30 : fabs(1 * data->raycast->ray_y);
		data->raycast->map_x = data->player->pos_x;
		data->raycast->map_y = data->player->pos_y;
		if (data->raycast->map_x < 0 || data->raycast->map_x >= data->map->width || data->raycast->map_y < 0 || data->raycast->map_y >= data->map->height)
			break;
		while (data->raycast->map_x > 0 && data->raycast->map_x <= data->map->width && data->raycast->map_y > 0 && data->raycast->map_y <= data->map->height)
		{
			if (data->map->map_int[(int)data->raycast->map_y][(int)data->raycast->map_x] != 1)
			{
				int j = 0;
				int i = 0;
				// int	test_x;
				// int	test_y;

				//i < (data->map->width * PIXEL) c'est la longueur du trait, faut trouver pour qu'il s'arrete au mur
				while ((i < (data->map->width * PIXEL) && data->raycast->ray_y < (j * PIXEL)))
				{
					if (data->map->map_int[(int)data->raycast->map_y][(int)data->raycast->map_x] == 1)
						break;
					mlx_pixel_put(data->mlx->mlx, data->mlx->win,
								(data->player->pos_x * (PIXEL + 2)) + (data->raycast->ray_x * data->raycast->dir_x),
								(data->player->pos_y * (PIXEL + 2)) + (data->raycast->ray_y * data->raycast->dir_y),
								0xFFFF00);
					data->raycast->ray_x += (data->raycast->delta_x > 0) ? 1 : -1;
					i++;
					data->raycast->ray_y += (data->raycast->delta_y > 0) ? 1 : -1;
					printf("ray_x = %f\n", data->raycast->ray_x);
					printf("ray_y = %f\n", data->raycast->ray_y);
					j++;

				}
			}
			if (data->raycast->delta_x < data->raycast->delta_y)
			{
				data->raycast->map_x += (data->raycast->ray_x > 0) ? 1 : -1;
				data->raycast->delta_x += fabs(1 / data->raycast->ray_x);
			}
			else
			{
				data->raycast->map_y += (data->raycast->ray_y > 0) ? 1 : -1;
				data->raycast->delta_y += fabs(1 / data->raycast->ray_y);
			}
			if (data->raycast->map_y >= 0 && data->raycast->map_x >= 0 && data->map->map_int[(int)data->raycast->map_y][(int)data->raycast->map_x] == 1)
				break ;
		}
		if (data->raycast->map_y >= 0 && data->raycast->map_x >= 0 && data->map->map_int[(int)data->raycast->map_y][(int)data->raycast->map_x] == 1)
				break ;
		i++;
	}
}
int	is_valid_move(double new_x, double new_y, t_data *data)
{
	int	map_x;
	int	map_y;

	if (new_x < 0 || new_x >= data->map->width || new_y < 0
		|| new_y >= data->map->height)
		return (0);
	map_x = (int)new_x;
	map_y = (int)new_y;
	if (data->map->map_int[map_y][map_x] == 1)
		return (0);
	return (1);
}

void	direction_key(unsigned int keycode, t_data *data)
{
	if (keycode == UP)
	{
		data->raycast->dir_x = 0;
		data->raycast->dir_y = -1;
	}
	if (keycode == DOWN)
	{
		data->raycast->dir_x = 0;
		data->raycast->dir_y = 1;
	}
	if (keycode == LEFT)
	{
		data->raycast->dir_x = 1;
		data->raycast->dir_y = 0;
	}
	if (keycode == RIGHT)
	{
		data->raycast->dir_x = -1;
		data->raycast->dir_y = 0;
	}
}
int	press_key(unsigned int keycode, t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->pos_x;
	new_y = data->player->pos_y;
	printf("delta_x = %f\n", data->raycast->delta_x);
	printf("delta_y = %f\n", data->raycast->delta_y);
	printf("pos_x = %f\n", data->player->pos_x);
	printf("pos_y = %f\n", data->player->pos_y);
	printf("player[%d][%d] = %d\n", (int)data->player->pos_y,
		(int)data->player->pos_x,
		data->map->map_int[(int)data->player->pos_y][(int)data->player->pos_x]);
	direction_key(keycode, data);
	if (keycode == KEY_ESC)
	{
		ft_free_data(data);
		exit(0);
	}
	if (keycode == KEY_A)
		new_x -= 0.1;
	if (keycode == KEY_D)
		new_x += 0.1;
	if (keycode == KEY_W)
		new_y -= 0.1;
	if (keycode == KEY_S)
		new_y += 0.1;
	if (is_valid_move(new_x, new_y, data))
	{
		printf("new_x = %f\n", new_x);
		printf("new_y = %f\n", new_y);
		data->player->pos_x = new_x;
		data->player->pos_y = new_y;
	}
	mlx_clear_window(data->mlx->mlx, data->mlx->win);
	draw_floor(data);
	draw_wall(data);
	draw_player(data);
	draw_ray(data);
	return (0);
}
