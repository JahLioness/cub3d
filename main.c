/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:20:17 by ede-cola          #+#    #+#             */
/*   Updated: 2024/12/03 13:32:24 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main(int ac, char **av, char **env)
{
	t_data	map_data;

	if (!env || !*env)
		return (ft_putendl_fd("Env is needed to launch cub3d", 2), 1);
	else if (ac != 2)
		return (ft_putendl_fd("Wrong arguments count", 2), 1);
	else
	{
		char **test = ft_read_map(av[1]);
		ft_clean_init_data(&map_data);
		if (ft_get_data(&map_data, test))
		{
			printf("texture N = %s\n", map_data.texture_n);
			printf("texture S = %s\n", map_data.texture_s);
			printf("texture W = %s\n", map_data.texture_w);
			printf("texture E = %s\n", map_data.texture_e);
			printf("texture F = %s\n", map_data.texture_f);
			printf("texture C = %s\n", map_data.texture_c);
			ft_free_tab(test);
		}
	}
	return (0);
}
