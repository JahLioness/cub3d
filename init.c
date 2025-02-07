/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:52:07 by ede-cola          #+#    #+#             */
/*   Updated: 2025/02/07 21:09:34 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_clean_init_data(t_data *data)
{
	data->map = NULL;
	data->mlx = NULL;
	data->player = NULL;
	data->texture_c = NULL;
	data->texture_f = NULL;
	data->texture_n = NULL;
	data->texture_s = NULL;
	data->texture_w = NULL;
	data->texture_e = NULL;
	return (0);
}

int	ft_clean_init_player(t_data *data)
{
	data->player = ft_calloc(1, sizeof(t_player));
	if (!data->player)
		return (1);
	data->player->pos_x = 0;
	data->player->pos_y = 0;
	data->player->next_x = 0;
	data->player->next_y = 0;
	return (0);
}
int	ft_clean_init_raycast(t_data *data)
{
	data->raycast = ft_calloc(1, sizeof(t_raycast));
	if (!data->raycast)
		return (1);
	if (!ft_get_player_dir(data))
		return (1);
	data->raycast->delta_x = 0;
	data->raycast->delta_y = 0;
	ft_get_player_dir(data);
	// data->raycast->plane_x = 0.66;
	// data->raycast->plane_y = 0;
	data->raycast->plane_x = -data->raycast->dir_y * FOV;
	data->raycast->plane_y = data->raycast->dir_x * FOV;
	data->raycast->camera_x = 0;
	data->raycast->ray_x = 0;
	data->raycast->ray_y = 0;
	data->raycast->side_x = 0;
	data->raycast->side_y = 0;
	data->raycast->map_x = 0;
	data->raycast->map_y = 0;
	return (0);
}
t_size	*ft_screen_size(void *mlx)
{
	t_size	*size;

	size = ft_calloc(1, sizeof(t_size));
	if (!size)
		return (NULL);
	mlx_get_screen_size(mlx, &size->screen_width, &size->screen_height);
	return (size);
}

int	mlx_start(t_data *data)
{
	data->mlx = ft_calloc(1, sizeof(t_mlx));
	if (!data->mlx)
		return (1);
	data->mlx->mlx = mlx_init();
	if (!data->mlx->mlx)
		return (free(data->mlx), 1);
	data->mlx->win = NULL;
	return (0);
}

int	mlx_window_init(t_data *data)
{
	t_size	*screen_size;

	screen_size = ft_screen_size(data->mlx->mlx);
	if (data->map->width && data->map->height && data->map->width
		* PIXEL < screen_size->screen_width && data->map->height
		* PIXEL < screen_size->screen_height)
		data->mlx->win = mlx_new_window(data->mlx->mlx, data->map->width
				* PIXEL, data->map->height * PIXEL, "cub3D");
	else
		data->mlx->win = mlx_new_window(data->mlx->mlx, WIDTH, HEIGHT, "cub3D");
	if (!data->mlx->win)
		return (free(data->mlx->mlx), free(data->mlx), free(screen_size), 1);
	return (free(screen_size), 0);
}
