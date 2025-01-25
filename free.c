/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:44:57 by ede-cola          #+#    #+#             */
/*   Updated: 2025/01/25 04:37:06 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_free_int_tab(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < ft_tab_len(data->map->map_tab))
	{
		free(data->map->map_int[i]);
		i++;
	}
	free(data->map->map_int);
	return (0);
}

int	ft_free_data(t_data *data)
{
	if (data->map && data->map->map_int)
	{
		ft_free_int_tab(map_data);
		ft_free_tab(map_data->map->map_tab);
		free(map_data->map);
	}
	if (map_data->mlx)
	{
		ft_free_img(data->mlx, 3);
		if (data->mlx->win)
			mlx_destroy_window(data->mlx->mlx, data->mlx->win);
		mlx_destroy_display(data->mlx->mlx);
		free(data->mlx->mlx);
		free(data->mlx);
	}
	if (data->player)
		free(data->player);
	free(data->texture_f);
	free(data->texture_c);
	free(data->texture_n);
	free(data->texture_s);
	free(data->texture_e);
	free(data->texture_w);
	return (0);
}

int	ft_free_img(t_mlx *mlx, int index)
{
	int	i;

	i = 0;
	while (i <= index)
	{
		if (mlx->img[i])
		{
			mlx_destroy_image(mlx->mlx, mlx->img[i]->img);
			free(mlx->img[i]);
		}
		i++;
	}
	return (0);
}
