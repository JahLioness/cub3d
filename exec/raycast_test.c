/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:25:19 by ede-cola          #+#    #+#             */
/*   Updated: 2025/02/07 21:27:14 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	ft_get_player_dir(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < ft_tab_len(data->map->map_tab))
	{
		j = 0;
		while (j < ft_strlen(data->map->map_tab[i]))
		{
			if (data->map->map_tab[i][j] == 'N')
			{
				data->raycast->dir_x = -1;
				data->raycast->dir_y = 0;
			}
			else if (data->map->map_tab[i][j] == 'S')
			{
				data->raycast->dir_x = 1;
				data->raycast->dir_y = 0;
			}
			else if (data->map->map_tab[i][j] == 'E')
			{
				data->raycast->dir_x = 0;
				data->raycast->dir_y = 1;
			}
			else if (data->map->map_tab[i][j] == 'W')
			{
				data->raycast->dir_x = 0;
				data->raycast->dir_y = -1;
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_get_player_pos(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < ft_tab_len(data->map->map_tab))
	{
		j = 0;
		while (j < ft_strlen(data->map->map_tab[i]))
		{
			if (data->map->map_int[i][j] == 3)
			{
				data->player->pos_y = (double)i;
				data->player->pos_x = (double)j;
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	draw_floor(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (data->map->map_tab[y] && y < data->map->height)
	{
		while (data->map->map_tab[y][x] && x < data->map->width)
		{
			if ((data->map->map_int[y][x] == 0 || data->map->map_int[y][x] == 3)
				&& data->map->map_int[y][x] != 1
				&& data->map->map_int[y][x] != 2)
				mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
					data->mlx->img[0]->img, x * (PIXEL + 2), y * (PIXEL + 2));
			x++;
		}
		x = 0;
		y++;
	}
}

void	draw_wall(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (data->map->map_tab[y] && y < data->map->height)
	{
		while (data->map->map_tab[y][x] && x < data->map->width)
		{
			if (data->map->map_int[y][x] == 1)
				mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
					data->mlx->img[1]->img, x * (PIXEL + 2), y * (PIXEL + 2));
			x++;
		}
		x = 0;
		y++;
	}
}

void	draw_player(t_data *data)
{
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
		data->mlx->img[2]->img, data->player->pos_x * (PIXEL + 2),
		data->player->pos_y * (PIXEL + 2));
}

// void	draw_ray(t_data *data)
// {
// 	int		i;
// 	double	camera_x;
// 	double	side_dist_x;
// 	double	side_dist_y;
// 	int		hit;
// 	double	perp_wall_dist;
// 	int		line_height;
// 	int		draw_start;
// 	int		draw_end;

// 	i = 0;
// 	while (i < data->map->width)
// 	{
// 		camera_x = 2 * i / (double)data->map->width - 1;
// 		data->raycast->ray_x = data->raycast->dir_x + data->raycast->plane_x
// 			* camera_x;
// 		data->raycast->ray_y = data->raycast->dir_y + data->raycast->plane_y
// 			* camera_x;
// 		data->raycast->delta_x = (data->raycast->ray_y == 0) ? 1e30 : fabs(1
// 				/ data->raycast->ray_x);
// 		data->raycast->delta_y = (data->raycast->ray_x == 0) ? 1e30 : fabs(1
// 				/ data->raycast->ray_y);
// 		data->raycast->map_x = (int)data->player->pos_x;
// 		data->raycast->map_y = (int)data->player->pos_y;
// 		int step_x, step_y;
// 		if (data->raycast->ray_x < 0)
// 		{
// 			step_x = -1;
// 			side_dist_x = (data->player->pos_x - data->raycast->map_x)
// 				* data->raycast->delta_x;
// 		}
// 		else
// 		{
// 			step_x = 1;
// 			side_dist_x = (data->raycast->map_x + 1.0 - data->player->pos_x)
// 				* data->raycast->delta_x;
// 		}
// 		if (data->raycast->ray_y < 0)
// 		{
// 			step_y = -1;
// 			side_dist_y = (data->player->pos_y - data->raycast->map_y)
// 				* data->raycast->delta_y;
// 		}
// 		else
// 		{
// 			step_y = 1;
// 			side_dist_y = (data->raycast->map_y + 1.0 - data->player->pos_y)
// 				* data->raycast->delta_y;
// 		}
// 		hit = 0;
// 		while (!hit)
// 		{
// 			if (side_dist_x < side_dist_y)
// 			{
// 				side_dist_x += data->raycast->delta_x;
// 				data->raycast->map_x += step_x;
// 				if (data->map->map_int[data->raycast->map_y][data->raycast->map_x] == 1)
// 					hit = 1;
// 			}
// 			else
// 			{
// 				side_dist_y += data->raycast->delta_y;
// 				data->raycast->map_y += step_y;
// 				if (data->map->map_int[data->raycast->map_y][data->raycast->map_x] == 1)
// 					hit = 1;
// 			}
// 			// Assure que les coordonnées sont valides
// 			if (data->raycast->map_x < 0
// 				|| data->raycast->map_x >= data->map->width
// 				|| data->raycast->map_y < 0
// 				|| data->raycast->map_y >= data->map->height)
// 			{
// 				hit = 1;
// 			}
// 		}
// 		if (data->raycast->map_x != data->player->pos_x)
// 			perp_wall_dist = (data->raycast->map_x - data->player->pos_x + (1
// 						- step_x) / 2) / data->raycast->ray_x;
// 		else
// 			perp_wall_dist = (data->raycast->map_y - data->player->pos_y + (1
// 						- step_y) / 2) / data->raycast->ray_y;
// 		// Calcul de la hauteur de la ligne en fonction de la distance au mur
// 		line_height = (int)(data->map->height / perp_wall_dist);
// 		// Calcul des positions de début et fin de la ligne (afin de dessiner le rayon à la bonne position)
// 		draw_start = -line_height / 2 + data->map->height / 2;
// 		if (draw_start < 0)
// 			draw_start = 0;
// 		draw_end = line_height / 2 + data->map->height / 2;
// 		if (draw_end >= data->map->height)
// 			draw_end = data->map->height - 1;
// 		// Dessin du rayon à la bonne position (ajout du facteur de mise à l'échelle pour chaque colonne)
// 		int color = 0xFFFF00; // Choisir la couleur du rayon
// 		for (int y = draw_start; y < draw_end; y++)
// 		{
// 			mlx_pixel_put(data->mlx->mlx, data->mlx->win, i * PIXEL, y, color);
// 		}
// 		i++;
// 	}
// }

void	draw_ray(t_data *data)
{
	int		i;
	double	camera_x;
		double side_dist_x;
		double side_dist_y;
	int		line_height;
	int		draw_start;
	int		draw_end;

	// int map_x, map_y;
	i = 0;
	while (i < data->map->width)
	{
		// Calcul de la direction du rayon pour chaque colonne
		camera_x = (2 * i / (double)data->map->width) - 1;
		data->raycast->ray_x = data->raycast->dir_x + data->raycast->plane_x
			* camera_x;
		data->raycast->ray_y = data->raycast->dir_y + data->raycast->plane_y
			* camera_x;
		// Calcul des différences (delta) pour chaque direction
		data->raycast->delta_x = (data->raycast->ray_y == 0) ? 1e30 : fabs(1
				/ data->raycast->ray_x);
		data->raycast->delta_y = (data->raycast->ray_x == 0) ? 1e30 : fabs(1
				/ data->raycast->ray_y);
		// Position initiale du rayon (en coordonnées flottantes)
		data->raycast->map_x = (int)data->player->pos_x;
		data->raycast->map_y = (int)data->player->pos_y;
		// Variables pour les étapes du rayon
		int step_x, step_y;
		// Calcul des étapes et des distances initiales pour chaque direction
		if (data->raycast->ray_x < 0)
		{
			step_x = -1;
			side_dist_x = (data->player->pos_x - data->raycast->map_x)
				* data->raycast->delta_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (data->raycast->map_x + 1.0 - data->player->pos_x)
				* data->raycast->delta_x;
		}
		if (data->raycast->ray_y < 0)
		{
			step_y = -1;
			side_dist_y = (data->player->pos_y - data->raycast->map_y)
				* data->raycast->delta_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (data->raycast->map_y + 1.0 - data->player->pos_y)
				* data->raycast->delta_y;
		}
		// DDA loop : progression dans la grille
		int hit = 0; // Flag pour savoir si on touche un mur
		while (!hit)
		{
			// On avance dans la direction X ou Y selon la distance minimale
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += data->raycast->delta_x;
				data->raycast->map_x += step_x;
				// Vérifie si le rayon touche un mur (mur = 1 dans la carte)
				if (data->map->map_int[data->raycast->map_y][data->raycast->map_x] == 1)
					hit = 1;
			}
			else
			{
				side_dist_y += data->raycast->delta_y;
				data->raycast->map_y += step_y;
				// Vérifie si le rayon touche un mur (mur = 1 dans la carte)
				if (data->map->map_int[data->raycast->map_y][data->raycast->map_x] == 1)
					hit = 1;
			}
			// Assure que les coordonnées sont valides
			if (data->raycast->map_x < 0
				|| data->raycast->map_x >= data->map->width
				|| data->raycast->map_y < 0
				|| data->raycast->map_y >= data->map->height)
			{
				hit = 1;
			}
		}
		// Calcul de la hauteur de ligne pour l'affichage du rayon
		line_height = (int)(data->map->height / (data->raycast->map_y
					- data->player->pos_y));
		draw_start = -line_height / 2 + data->map->height / 2;
		draw_end = line_height / 2 + data->map->height / 2;
		// Dessin du rayon à la bonne position (ajout du facteur de mise à l'échelle pour chaque colonne)
		mlx_pixel_put(data->mlx->mlx, data->mlx->win, i * PIXEL, draw_start,
			0xFFFF00); // Pour les pixels en haut
		mlx_pixel_put(data->mlx->mlx, data->mlx->win, i * PIXEL, draw_end,
			0xFFFF00);   // Pour les pixels en bas
		i++;
	}
}


int	is_valid_move(double new_x, double new_y, t_data *data)
{
	int	map_x;
	int	map_y;

	if (new_x < 0 || new_x >= data->map->width || new_y < 0
		|| new_y >= data->map->height)
		return (0);
	map_x = (int)new_x;
	map_y = (int)new_y;
	if (data->map->map_int[map_y][map_x] == 1)
		return (0);
	return (1);
}

int	direction_key(unsigned int keycode, t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	// if (keycode == UP)
	// {
	// 	printf("UP\n");
	// 	data->raycast->dir_x = 0;
	// 	data->raycast->dir_y = -1;
	// }
	// if (keycode == DOWN)
	// {
	// 	printf("DOWN\n");
	// 	data->raycast->dir_x = 0;
	// 	data->raycast->dir_y = 1;
	// }
	if (keycode == LEFT)
	{
		printf("LEFT\n");
		old_dir_x = data->raycast->dir_x;
		data->raycast->dir_x = data->raycast->dir_x * cos(-ROT_SPEED)
			- data->raycast->dir_y * sin(-ROT_SPEED);
		data->raycast->dir_y = old_dir_x * sin(-ROT_SPEED)
			+ data->raycast->dir_y * cos(-ROT_SPEED);
		old_plane_x = data->raycast->plane_x;
		data->raycast->plane_x = data->raycast->plane_x * cos(-ROT_SPEED)
			- data->raycast->plane_y * sin(-ROT_SPEED);
		data->raycast->plane_y = old_plane_x * sin(-ROT_SPEED)
			+ data->raycast->plane_y * cos(-ROT_SPEED);
	}
	if (keycode == RIGHT)
	{
		printf("RIGHT\n");
		old_dir_x = data->raycast->dir_x;
		data->raycast->dir_x = data->raycast->dir_x * cos(ROT_SPEED)
			- data->raycast->dir_y * sin(ROT_SPEED);
		data->raycast->dir_y = old_dir_x * sin(ROT_SPEED) + data->raycast->dir_y
			* cos(ROT_SPEED);
		old_plane_x = data->raycast->plane_x;
		data->raycast->plane_x = data->raycast->plane_x * cos(ROT_SPEED)
			- data->raycast->plane_y * sin(ROT_SPEED);
		data->raycast->plane_y = old_plane_x * sin(ROT_SPEED)
			+ data->raycast->plane_y * cos(ROT_SPEED);
	}
	return (0);
}
int	press_key(unsigned int keycode, t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->pos_x;
	new_y = data->player->pos_y;
	printf("delta_x = %f\n", data->raycast->delta_x);
	printf("delta_y = %f\n", data->raycast->delta_y);
	printf("pos_x = %f\n", data->player->pos_x);
	printf("pos_y = %f\n", data->player->pos_y);
	printf("player[%d][%d] = %d\n", (int)data->player->pos_y,
		(int)data->player->pos_x,
		data->map->map_int[(int)data->player->pos_y][(int)data->player->pos_x]);
	direction_key(keycode, data);
	if (keycode == KEY_ESC)
	{
		ft_free_data(data);
		exit(0);
	}
	if (keycode == KEY_A || keycode == KEY_Q)
		new_x -= 0.1;
	if (keycode == KEY_D)
		new_x += 0.1;
	if (keycode == KEY_W || keycode == KEY_Z)
		new_y -= 0.1;
	if (keycode == KEY_S)
		new_y += 0.1;
	if (is_valid_move(new_x, new_y, data))
	{
		printf("new_x = %f\n", new_x);
		printf("new_y = %f\n", new_y);
		data->player->pos_x = new_x;
		data->player->pos_y = new_y;
	}
	mlx_clear_window(data->mlx->mlx, data->mlx->win);
	draw_floor(data);
	draw_wall(data);
	draw_player(data);
	draw_ray(data);
	return (0);
}
