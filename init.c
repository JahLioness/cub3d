/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:52:07 by ede-cola          #+#    #+#             */
/*   Updated: 2025/01/27 18:21:54 by ede-cola         ###   ########.fr       */
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
	data->player->pos_x = 0;
	data->player->pos_y = 0;
	data->player->dir_x = 0;
	data->player->dir_y = 0;
	data->player->delta_x = 0;
	data->player->delta_y = 0;
	data->player->player_angle = 0;
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
