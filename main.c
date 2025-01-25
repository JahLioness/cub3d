/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:20:17 by ede-cola          #+#    #+#             */
/*   Updated: 2025/01/25 05:19:04 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	display_game(t_data *data)
{
	draw_floor(data);
	draw_wall(data);
	draw_player(data);
	mlx_hook(data->mlx->win, 2, 1L << 0, press_key, data);
	mlx_loop(data->mlx->mlx);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	**test;
	size_t		i;
	size_t		j;

	if (!env || !*env)
		return (ft_putendl_fd("Error env is needed to launch cub3d", 2), 1);
	else if (ac != 2)
		return (ft_putendl_fd("Error wrong arguments count", 2), 1);
	else
	{
		test = ft_read_map(av[1]);
		if (!test)
			return (ft_putendl_fd("Error can't read map", 2), 1);
		i = 0;
		ft_clean_init_data(&data);
		if (ft_get_data(&data, test))
		{
			printf("texture N = %s\n", data.texture_n);
			printf("texture S = %s\n", data.texture_s);
			printf("texture W = %s\n", data.texture_w);
			printf("texture E = %s\n", data.texture_e);
			printf("texture F = %s\n", data.texture_f);
			printf("texture C = %s\n", data.texture_c);
			while (data.map->map_tab[i])
			{
				printf("%s", data.map->map_tab[i]);
				i++;
			}
			if (mlx_start(&data))
				return (ft_free_data(&data), ft_free_tab(test),
					ft_putendl_fd("Error initalizing mlx failed", 2), 1);
			if(ft_check_textures(&data) || ft_check_rgb(&data))
				return (ft_free_data(&data), ft_free_tab(test),
				ft_putendl_fd("Error invalid image files", 2), 1);
			else if (ft_check_map_closed(data.map->map_tab) || ft_check_player(data.map->map_tab))
				return (ft_free_data(&data), ft_free_tab(test),
				ft_putendl_fd("Error invalid map file", 2), 1);
		}
		else
			return (ft_free_data(&data), ft_free_tab(test),
				ft_putendl_fd("Error invalid map file", 2), 1);
		if (mlx_window_init(&data))
			return (ft_free_data(&data), ft_free_tab(test),
				ft_putendl_fd("Error initalizing window failed", 2), 1);
		data.map->width = ft_strlen(data.map->map_tab[0]);
		data.map->height = ft_tab_len(data.map->map_tab);
		data.map->map_int = ft_convert_map(data.map->map_tab);
		i = 0;
		printf("\n");
		while (i < ft_tab_len(data.map->map_tab))
		{
			printf("{");
			j = 0;
			while (j < ft_strlen(data.map->map_tab[i]) - 1)
			{
				printf("%d", data.map->map_int[i][j]);
				if (j != ft_strlen(data.map->map_tab[i]) - 2)
					printf(",");
				j++;
			}
			printf("}\n");
			i++;
		}
		ft_clean_init_player(&data);
		if (!ft_get_player_pos(&data))
			printf("player pos x = %f, player pos y = %f\n", data.player->pos_x, data.player->pos_y);
		display_game(&data);
		ft_free_tab(test);
		ft_free_data(&data);
	}
	return (0);
}
