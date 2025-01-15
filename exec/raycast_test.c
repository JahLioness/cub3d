/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:25:19 by ede-cola          #+#    #+#             */
/*   Updated: 2025/01/15 16:26:47 by ede-cola         ###   ########.fr       */
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
