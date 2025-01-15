/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:52:07 by ede-cola          #+#    #+#             */
/*   Updated: 2025/01/15 16:26:27 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_clean_init_data(t_data *map_data)
{
	map_data->map = NULL;
	map_data->mlx = NULL;
	map_data->player = NULL;
	map_data->texture_c = NULL;
	map_data->texture_f = NULL;
	map_data->texture_n = NULL;
	map_data->texture_s = NULL;
	map_data->texture_w = NULL;
	map_data->texture_e = NULL;
	return (0);
}

int	ft_clean_init_player(t_data *map_data)
{
	map_data->player = ft_calloc(1, sizeof(t_player));
	map_data->player->pos_x = 0;
	map_data->player->pos_y = 0;
	map_data->player->dir_x = 0;
	map_data->player->dir_y = 0;
	return (0);
}

int	mlx_start(t_data *map_data)
{
	map_data->mlx = ft_calloc(1, sizeof(t_mlx));
	if (!map_data->mlx)
		return (1);
	map_data->mlx->mlx = mlx_init();
	if (!map_data->mlx->mlx)
		return (free(map_data->mlx), 1);
	map_data->mlx->win = NULL;
	return (0);
}

int	mlx_window_init(t_data *map_data)
{
	map_data->mlx->win = mlx_new_window(map_data->mlx->mlx, 600, 400, "cub3D");
	if (!map_data->mlx->win)
		return (free(map_data->mlx->mlx), free(map_data->mlx), 1);
	return (0);
}
