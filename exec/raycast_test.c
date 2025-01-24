/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:25:19 by ede-cola          #+#    #+#             */
/*   Updated: 2025/01/23 19:00:57 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	ft_get_player_pos(t_data *map_data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < ft_tab_len(map_data->map->map_tab))
	{
		j = 0;
		while (j < ft_strlen(map_data->map->map_tab[i]))
		{
			if (map_data->map->map_int[i][j] == 3)
			{
				map_data->player->pos_y = (double)i;
				map_data->player->pos_x = (double)j;
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	wall_hit(t_data *map_data, double ray_x, double ray_y)
{
	int		x;
	int		y;

	x = (int)map_data->player->pos_x;
	y = (int)map_data->player->pos_y;
	while (map_data->map->map_int[y][x] != 1)
	{
		x += ray_x;
		y += ray_y;
		if (map_data->map->map_int[y][x] == 1)
			return (1);
	}
	return (0);
}

void	raycasting(t_data *map_data)
{
	double	dir_x = -1;
	double	dir_y = 0;
	double	plane_x = 0.0;
	double	plane_y = 0.66;
	int		x = 0;
	
	while(x < map_data->map->width)
	{
		double	camera_x = 2 * x / (double)map_data->map->width - 1;
		double	ray_x = dir_x + plane_x * camera_x;
		double	ray_y = dir_y + plane_y * camera_x;
		double side_dist_x;
		double side_dist_y;
		double delta_dist_x = (ray_x == 0) ? 1e30 : fabs(1 / ray_x);
		double delta_dist_y = (ray_y == 0) ? 1e30 : fabs(1 / ray_y);
		double wall_dist;
		int step_x;
		int step_y;
		int hit = 0;
		int side;
		int map_x = map_data->player->pos_x;
		int map_y = map_data->player->pos_y;
		if (ray_x < 0)
		{
			step_x = -1;
			side_dist_x = (map_data->player->pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - map_data->player->pos_x) * delta_dist_x;
		}
		if (ray_y < 0)
		{
			step_y = -1;
			side_dist_y = (map_data->player->pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - map_data->player->pos_y) * delta_dist_y;
		}
		while (!hit)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (map_data->map->map_int[map_y][map_x] == 1)
				hit = 1;
		}
		if (!side)
			wall_dist = side_dist_x - delta_dist_x;
		else
			wall_dist = side_dist_y - delta_dist_y;
		double	line_height = map_data->map->height / wall_dist;
		int draw_start = -line_height / 2 + map_data->map->height / 2;
		if (draw_start < 0)
			draw_start = 0;
		int draw_end = line_height / 2 + map_data->map->height / 2;
		if (draw_end >= map_data->map->height)
			draw_end = map_data->map->height - 1;
		/*	FAUT QUE JE TROUVE UN MOYEN DE METTRE LA COULEUR AVEC LA MLX*/
		/*ET J'AI JUSTE ESSAYER DE "TRADUIRE" LE TUTO, JE SAIS PAS SI CA FONCTIONNE*/
		x++;
	}
}
