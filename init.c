/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:52:07 by ede-cola          #+#    #+#             */
/*   Updated: 2024/12/03 12:22:33 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_clean_init_data(t_data *map_data)
{
	map_data->map = NULL;
	map_data->texture_c = NULL;
	map_data->texture_f = NULL;
	map_data->texture_n = NULL;
	map_data->texture_s = NULL;
	map_data->texture_w = NULL;
	map_data->texture_e = NULL;
	return (0);
}
