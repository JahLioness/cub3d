/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:20:17 by ede-cola          #+#    #+#             */
/*   Updated: 2024/12/20 15:40:28 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main(int ac, char **av, char **env)
{
	t_data	map_data;
	char	**test;
	int		i;

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
		ft_clean_init_data(&map_data);
		if (ft_get_data(&map_data, test))
		{
			printf("texture N = %s\n", map_data.texture_n);
			printf("texture S = %s\n", map_data.texture_s);
			printf("texture W = %s\n", map_data.texture_w);
			printf("texture E = %s\n", map_data.texture_e);
			printf("texture F = %s\n", map_data.texture_f);
			printf("texture C = %s\n", map_data.texture_c);
			while (map_data.map->map_tab[i])
			{
				printf("%s", map_data.map->map_tab[i]);
				i++;
			}
			mlx_start(&map_data);
			if(ft_check_textures(&map_data) || ft_check_rgb(&map_data))
				return (ft_free_data(&map_data), ft_free_tab(test),
				ft_putendl_fd("Error invalid image files", 2), 1);
			else if (ft_check_map_closed(map_data.map->map_tab))
				return (ft_free_data(&map_data), ft_free_tab(test),
				ft_putendl_fd("Error invalid map file", 2), 1);
			else if (ft_check_player_start(map_data.map->map_tab))
				return (ft_free_data(&map_data), ft_free_tab(test),
					ft_putendl_fd("Error invalid player start", 2), 1);
		}
		else
			return (ft_free_data(&map_data), ft_free_tab(test),
				ft_putendl_fd("Error invalid map file", 2), 1);
		ft_free_tab(test);
		ft_free_data(&map_data);
	}
	return (0);
}
