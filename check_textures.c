/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:35:32 by ede-cola          #+#    #+#             */
/*   Updated: 2024/12/09 18:19:26 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_img	*ft_init_img(t_mlx *mlx, char *path)
{
	t_img	*img;

	img = ft_calloc(1, sizeof(t_img));
	if (!img)
		return (NULL);
	img->img = mlx_xpm_file_to_image(mlx->mlx, path, &img->width,
			&img->height);
	if (!img->img)
		return (free(img), NULL);
	printf("path = %s\n", path);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
	if (!img->addr)
		return (free(img->img), free(img), NULL);
	return (img);
}

int	ft_check_textures(t_data *map_data)
{
	map_data->mlx->img[0] = ft_init_img(map_data->mlx,
			map_data->texture_n);
	if (!map_data->mlx->img[0])
		return (1);
	map_data->mlx->img[1] = ft_init_img(map_data->mlx,
			map_data->texture_s);
	if (!map_data->mlx->img[1])
		return (ft_free_img(map_data->mlx, 0), 1);
	map_data->mlx->img[2] = ft_init_img(map_data->mlx,
			map_data->texture_e);
	if (!map_data->mlx->img[2])
		return (ft_free_img(map_data->mlx, 1), 1);
	map_data->mlx->img[3] = ft_init_img(map_data->mlx,
			map_data->texture_w);
	if (!map_data->mlx->img[3])
		return (ft_free_img(map_data->mlx, 2), 1);
	return (0);
}
