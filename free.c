/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:44:57 by ede-cola          #+#    #+#             */
/*   Updated: 2024/12/03 23:46:44 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_free_data(t_data *map_data)
{
	ft_free_tab(map_data->map);
	free(map_data->texture_f);
	free(map_data->texture_c);
	free(map_data->texture_n);
	free(map_data->texture_s);
	free(map_data->texture_e);
	free(map_data->texture_w);
	return (0);
}
