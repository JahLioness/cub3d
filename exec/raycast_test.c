/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:25:19 by ede-cola          #+#    #+#             */
/*   Updated: 2025/01/25 04:27:05 by andjenna         ###   ########.fr       */
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
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (data->map->map_tab[y] && y < data->map->height)
	{
		while (data->map->map_tab[y][x] && x < data->map->width)
		{
			if ((data->map->map_int[y][x] == 0 || data->map->map_int[y][x] != data->map->map_int[(int)data->player->pos_y][(int)data->player->pos_x]) && data->map->map_int[y][x] != 1 && data->map->map_int[y][x] != 2)
				mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->img[0]->img, x * (PIXEL + 2), y * (PIXEL + 2));
			x++;
		}
		x = 0;
		y++;
	}
}

void	draw_wall(t_data *data)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (data->map->map_tab[y] && y < data->map->height)
	{
		while (data->map->map_tab[y][x] && x < data->map->width)
		{
			if (data->map->map_int[y][x] == 1)
				mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->img[1]->img, x * (PIXEL + 2), y * (PIXEL + 2));
			x++;
		}
		x = 0;
		y++;
	}
}
void	draw_player(t_data *data)
{
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->img[2]->img, data->player->pos_x * (PIXEL + 2), data->player->pos_y * (PIXEL + 2));
}


int	press_key(unsigned int keycode, t_data *data)
{
	double new_x;
	double new_y;

	new_x = 0;
	new_y = 0;
	printf("pos_x = %f\n", data->player->pos_x);
	printf("pos_y = %f\n", data->player->pos_y);
	printf("player[%d][%d] = %d\n", (int)data->player->pos_y, (int)data->player->pos_x, data->map->map_int[(int)data->player->pos_y][(int)data->player->pos_x]);
	mlx_clear_window(data->mlx->mlx, data->mlx->win);
	if (keycode == KEY_ESC)
		exit(0);
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
	return (0);
}


// void	mini_map(t_data *data)
// {
// 	int		x;
// 	int		y;

// 	x = 0;
// 	y = 0;
// 	while (data->map->map_tab[y] && y < data->map->height)
// 	{
// 		while (data->map->map_tab[y][x] && x < data->map->width)
// 		{
// 			if (data->map->map_tab[y][x] == '0')
// 				mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->img[0]->img, x * PIXEL, y * PIXEL);
// 			else if (data->map->map_tab[y][x] == '1')
// 				mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->img[1]->img, x * PIXEL, y * PIXEL);
// 			else if (data->map->map_tab[y][x] == 'W' || data->map->map_tab[y][x] == 'E' || data->map->map_tab[y][x] == 'N' || data->map->map_tab[y][x] == 'S')
// 				mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->img[2]->img, x * PIXEL, y * PIXEL);
// 			x++;
// 		}
// 		x = 0;
// 		y++;
// 	}
// }

// void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
//     char    *dst;

//     dst = data->mlx->img[0]->addr + (y * data->mlx->img[0]->line_len + x * (data->mlx->img[0]->bpp / 8));
//     *(unsigned int*)dst = color;
// }

// void draw_vertical_line(t_data *data, int x, int start, int end, int color) {
//     for (int y = start; y <= end; y++) {
//         my_mlx_pixel_put(data, x, y, color);
//     }
// }

// void	ft_init_raycast(t_data *data)
// {
// 	data->raycast = malloc(sizeof(t_raycast));
// 	if (!data->raycast)
// 		return ;
// 	data->raycast->dir_x = -1;
// 	data->raycast->dir_y = 0;
// 	data->raycast->plane_x = 0;
// 	data->raycast->plane_y = 0.66;
// }

// void	raycasting(t_data *data)
// {
// 	int		x;

// 	x = 0;
// 	ft_init_raycast(data);
// 	while (x < data->map->width)
// 	{
// 		data->raycast->camera_x = 2 * x / (double)data->map->width - 1;
// 		data->raycast->ray_x = data->raycast->dir_x + data->raycast->plane_x * data->raycast->camera_x;
// 		data->raycast->ray_y = data->raycast->dir_y + data->raycast->plane_y * data->raycast->camera_x;
		
// 		data->raycast->map_x = (int)data->player->pos_x;
// 		data->raycast->map_y = (int)data->player->pos_y;

// 		double delta_dist_x = fabs(1 / data->raycast->ray_x);
// 		double delta_dist_y = fabs(1 / data->raycast->ray_y);

// 		double side_dist_x;
// 		double side_dist_y;
// 		int step_x;
// 		int step_y;
		
// 		if (data->raycast->ray_x < 0)
// 		{
// 			step_x = -1;
// 			side_dist_x = (data->player->pos_x - data->raycast->map_x) * delta_dist_x;
// 		}
// 		else
// 		{
// 			step_x = 1;
// 			side_dist_x = (data->raycast->map_x + 1.0 - data->player->pos_x) * delta_dist_x;
// 		}
// 		if (data->raycast->ray_y < 0)
// 		{
// 			step_y = -1;
// 			side_dist_y = (data->player->pos_y - data->raycast->map_y) * delta_dist_y;
// 		}
// 		else
// 		{
// 			step_y = 1;
// 			side_dist_y = (data->raycast->map_y + 1.0 - data->player->pos_y) * delta_dist_y;
// 		}
		
// 		int hit = 0;
// 		int side;

// 		while (hit == 0)
// 		{
// 			if (side_dist_x < side_dist_y)
// 			{
// 				side_dist_x += delta_dist_x;
// 				data->raycast->map_x += step_x;
// 				side = 0;
// 			}
// 			else
// 			{
// 				side_dist_y += delta_dist_y;
// 				data->raycast->map_y += step_y;
// 				side = 1;
// 			}
// 			if (data->map->map_int[data->raycast->map_y][data->raycast->map_x] == 1)
// 				hit = 1;
// 		}
		
// 		double wall_dist;
// 		if (side == 0)
// 		{
// 			wall_dist = (data->raycast->map_x - data->player->pos_x + (1 - step_x) / 2) / data->raycast->ray_x;
// 		}
// 		else
// 		{
// 			wall_dist = (data->raycast->map_y - data->player->pos_y + (1 - step_y) / 2) / data->raycast->ray_y;
// 		}
// 		int lineHeight = (int)(data->map->height) / wall_dist;
//         int drawStart = -lineHeight / 2 + data->map->height / 2;
//         if (drawStart < 0) drawStart = 0;
//         int drawEnd = lineHeight / 2 + data->map->height / 2;
//         if (drawEnd >= data->map->height) drawEnd = data->map->height - 1;

//         // Couleur du mur (différente selon la face touchée)
//         int color = (side == 0) ? 0xFF0000 : 0x800000;

//         // Dessiner la colonne
//         draw_vertical_line(data, x, drawStart, drawEnd, color);
// 		x++;
// 	}
// }
