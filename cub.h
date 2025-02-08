/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:59:17 by ede-cola          #+#    #+#             */
/*   Updated: 2025/02/07 23:54:45 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "./minilibx-linux/mlx.h"
# include "libft/libft.h"
# include <math.h>

# define HEIGHT	512
# define WIDTH 1024
# define PIXEL 48
# define FOV 0.66
# define ROT_SPEED 0.1
# define MOVE_SPEED 0.1
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_Z 122
# define KEY_Q 113
# define KEY_ESC 65307
// # define LEFT	37
// # define UP	38
// # define RIGHT	39
// # define DOWN	40
# define LEFT	65361
# define UP	65362
# define RIGHT	65363
# define DOWN	65364


typedef struct s_size
{
	int			screen_width;
	int			screen_height;
}				t_size;

typedef struct s_map
{
	int			height;
	int			width;
	char		**map_tab;
	int			**map_int;
}				t_map;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			endian;
	int			bpp;
	int			line_len;
	int			width;
	int			height;
}				t_img;

typedef struct s_player
{
	double		pos_y;
	double		pos_x;
	double		next_y;
	double		next_x;
}				t_player;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	t_img		*img[4];
}				t_mlx;

typedef struct s_raycast
{
	double		dir_x;
	double		dir_y;
	double		delta_x;
	double		delta_y;
	double		plane_x;
	double		plane_y;
	double		camera_x;
	double		ray_x;
	double		ray_y;
	double		side_x;
	double		side_y;
	int			map_x;
	int			map_y;

}				t_raycast;

typedef struct s_data
{
	t_map		*map;
	t_mlx		*mlx;
	t_player	*player;
	t_raycast	*raycast;
	char		*texture_f;
	char		*texture_c;
	char		*texture_n;
	char		*texture_s;
	char		*texture_e;
	char		*texture_w;

}				t_data;

/*		PARSE				*/
char			**ft_read_map(char *map);
int				ft_check_map(char **map);
int				ft_get_data(t_data *data, char **file);
int				ft_check_map_extension(char *file);

/*		PARSE_MAP*/
int				ft_check_map_closed(char **map);
int				ft_check_player(char **map);

/*		INIT		*/
int				ft_clean_init_data(t_data *data);
int				ft_clean_init_player(t_data *data);
int				ft_clean_init_raycast(t_data *data);
int				mlx_start(t_data *data);
int				mlx_window_init(t_data *data);

/*		UTILS		*/
size_t			ft_longest_line(char **map);
char			*ft_get_textures_path(char *path, char *entry);
char			*ft_join_to_comb_empty(char *line, size_t longest_line);

/*		FREE		*/
int				ft_free_img(t_mlx *mlx, int n);
int				ft_free_data(t_data *data);

/*		CHECK_TEXTURES		*/
int				ft_check_textures(t_data *data);
t_img			*ft_init_img(t_mlx *mlx, char *path);
int				ft_check_rgb(t_data *data);

/*		CONVERT_MAP			*/
int				**ft_convert_map(char **map);

/*		RAYCAST_UTILS		*/
int				ft_get_player_pos(t_data *data);
int				ft_get_player_dir(t_data *data);

/*		TEST		*/
void			draw_player(t_data *data);
void			draw_wall(t_data *data);
void			draw_floor(t_data *data);
void			draw_ray(t_data *data);
void			display_game(t_data *data);
int				press_key(unsigned int keycode, t_data *data);
int				direction_key(unsigned int keycode, t_data *data);
#endif
