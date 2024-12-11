/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:52:07 by ede-cola          #+#    #+#             */
/*   Updated: 2024/12/11 15:57:31 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_clean_init_data(t_data *map_data)
{
	map_data->map = NULL;
	map_data->mlx = NULL;
	map_data->texture_c = NULL;
	map_data->texture_f = NULL;
	map_data->texture_n = NULL;
	map_data->texture_s = NULL;
	map_data->texture_w = NULL;
	map_data->texture_e = NULL;
	return (0);
}

int	mlx_start(t_data *map_data)
{
	map_data->mlx = ft_calloc(1, sizeof(t_mlx));
	if (!map_data->mlx)
		return (1);
	map_data->mlx->mlx = mlx_init();
	if (!map_data->mlx->mlx)
		return(free(map_data->mlx), 1);
	map_data->mlx->win = mlx_new_window(map_data->mlx->mlx, 600, 400, "cub3D");
	if (!map_data->mlx->win)
		return (free(map_data->mlx->mlx), free(map_data->mlx), 1);
	return (0);
}
