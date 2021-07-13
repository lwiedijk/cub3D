/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/19 14:03:21 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/07/13 13:04:42 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define TILE_SIZE 64
# define SCALE 0.15
# define W_KEY 13
# define S_KEY 1
# define A_KEY 0
# define D_KEY 2
# define LEFT_ARROW 123
# define RIGHT_ARROW 124


typedef enum	e_error_code
{
	OK,
	INCORRECT_CUB_FILE,
	MALLOC_FAIL,
	INVALID_FD,
	READ_FAIL,
	WRONG_ARGC,
	INVALID_MAP,
}				t_error_code;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	void		*img_1;
	void		*img_2;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			next_frame;
	int			on_off;
}				t_mlx;

typedef struct	s_tex_array
{
	void		*tex_pnt;
	char		*tex_addr;
	int			tex_bpp;
	int			tex_ls;
	int			tex_endian;
	int			tex_hight;
	int			tex_width;

}				t_tex_array;

typedef	struct	s_tex
{
	t_tex_array	*tex_array;
	int			tex_ofset_x;
	int			tex_ofset_y;
}				t_tex;

typedef struct	s_maze
{
	int			filepos;
	int			screenres_y;
	int			screenres_x;
	char		*north_texture;
	char		*south_texture;
	char		*east_texture;
	char		*west_texture;
	char		*sprite;
	int			floor_color;
	int			ceiling_color;
	int			r;
	int			g;
	int			b;
	int			map_y;
	int			*map_x;
	int			**map;
	int			tile_size;
	float		step_size;
	char		player_or;
}				t_maze;

typedef struct	s_player
{
	float		pos_x;
	float		pos_y;
	int			walkdirection;
	int			turndirection;
	int			strafe;
	float		rotation;
	float		move_speed;
	float		rotation_speed;
}				t_player;

typedef struct	s_rays
{
	float		fov_angle;
	int			strip_width;
	float		ray_angle;
	int			ray_num;
	int			ray_up;
	int			ray_down;
	int			ray_right;
	int			ray_left;
	float		hx_intercept;
	float		hy_intercept;
	float		vx_intercept;
	float		vy_intercept;
	float		horz_xstep;
	float		horz_ystep;
	float		vert_xstep;
	float		vert_ystep;
	float		hor_hit_x;
	float		hor_hit_y;
	float		vert_hit_x;
	float		vert_hit_y;
	int			found_hor_wallhit;
	int			fount_vert_wallhit;
	float		horz_distance;
	float		vert_distance;
	float		wall_striphight;
	float		draw_start;
	float		draw_end;
}				t_rays;

typedef	struct	s_wall
{
	float		raydistance;
	char		wall_or;
	float		wall_hit_x;
	float		wall_hit_y;
	int			vertical_hit;
}				t_wall;

typedef	struct	s_port
{
	t_mlx		*mlx;
	t_maze		*blueprint;
	t_player	*player;
	t_rays		*rays;
	t_wall		*wall_array;
	t_tex		*tex;
}				t_port;

void	init_maze(t_maze *blueprint);
void	init_mlx(t_mlx *mlx);
void	init_player(t_player *player);
void	init_rays(t_rays *rays, t_maze *blueprint);
void	init_tex(t_tex *tex);
void	init_tex_2(t_tex *tex);
//void	read_textures(t_port *port, t_maze *blueprint, t_tex *tex);
void	parse(char *av, t_maze *blueprint);
void	parse_mapfile(t_maze *blueprint, char *mapfile);
void	parse_screenres(t_maze *blueprint, char *mapfile);
void	parse_textures(t_maze *blueprint, char *mapfile, char texture_type);
void	parse_color(t_maze *blueprint, char *mapfile, char type);
void	parse_map(t_maze *blueprint, char *mapfile);
void	check_max_screensize(t_maze *blueprint, t_mlx mlx);

/* animate/key_button_hook */
int		x_button_hook(t_mlx *mlx);
int		key_press_hook(int keycode, t_port *port);
int		key_release_hook(int keycode, t_port *port);

/* animate/player_movement */
void	set_player(t_port *port);
void	walk_player(t_port *port);
int		wall_hit(float x, float y, t_port *port);

/* animate/render_frame */
int		render_frame(t_port *port);
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
int		put_color(int t, int r, int g, int b);

/* animate/ray_casting */
void	new_ray(t_port *port, t_rays *rays, t_player *player, int colum_id);
void	cast_all_rays(t_port *port, t_rays *rays);

/* animate/draw_walls */
void	draw_walls(t_port *port, t_rays *rays, t_wall *wall_array, int colum_id);
void	put_all_textures(t_port *port, t_wall *wall_array, int colum_id);
void	put_cur_texture(t_port *port, t_tex_array tex_array, t_rays *rays, int colum_id);

/* animate/ray_casting_utils */
float	distance_between_points(float x1, float y1, float x2, float y2);
void	normalize_ray_angle(float *ray_angle);
void	ray_direction(t_rays *rays);

/* frame_build/dda.c */
void	horizontal_intercept(t_rays *rays, t_player *player);
void	check_horizontal_wallhit(t_port *port, t_rays *rays, t_maze *maze);
void	vertical_intercept(t_rays *rays, t_player *player);
void	check_vertical_wallhit(t_port *port, t_rays *rays, t_maze *maze);

/* animate/minimap */
void	draw_mini_player(t_port *port, float x, float y, int color);
void	draw_mini_map(t_port *port);
void	put_square(t_port *port, float x, float y, int color);
void	draw_line(t_mlx *mlx, t_player *player, float end_x, float end_y);

/* read_textures */
void	read_textures(t_port *port, t_maze *blueprint, t_tex *tex);
void	calculate_textures(t_port *port, t_tex *tex, char map);

#endif