/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:44:57 by ede-cola          #+#    #+#             */
/*   Updated: 2024/12/11 17:18:36 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_free_data(t_data *map_data)
{
	if (map_data->map && map_data->map->map_tab)
		ft_free_tab(map_data->map->map_tab);
	free(map_data->map);
	if (map_data->mlx)
	{
		ft_free_img(map_data->mlx, 3);
		mlx_destroy_window(map_data->mlx->mlx, map_data->mlx->win);
		mlx_destroy_display(map_data->mlx->mlx);
		free(map_data->mlx->mlx);
		free(map_data->mlx);
	}
	free(map_data->texture_f);
	free(map_data->texture_c);
	free(map_data->texture_n);
	free(map_data->texture_s);
	free(map_data->texture_e);
	free(map_data->texture_w);
	return (0);
}

int	ft_free_img(t_mlx *mlx, int index)
{
	int i;

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