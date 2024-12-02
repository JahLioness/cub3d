/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:20:17 by ede-cola          #+#    #+#             */
/*   Updated: 2024/12/02 16:44:19 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main(int ac, char **av, char **env)
{
	if (!env || !*env)
		return (ft_putendl_fd("Env is needed to launch cub3d", 2), 1);
	else if (ac != 2)
		return (ft_putendl_fd("Wrong arguments count", 2), 1);
	else
	{
		char **test = ft_read_map(av[1]);
		int i = 0;
		while (test[i])
		{
			printf("%s", test[i]);
			i++;
		}
		ft_free_tab(test);
	}
	return (0);
}