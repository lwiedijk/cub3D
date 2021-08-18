/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/19 14:03:21 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/08/18 11:03:03 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define TILE_SIZE 64
# define TEX_ARRAY_SIZE 4
# define SCALE 0.15
# define ESC_KEY 53
# define W_KEY 13
# define S_KEY 1
# define A_KEY 0
# define D_KEY 2
# define LEFT_ARROW 123
# define RIGHT_ARROW 124

typedef enum e_error_code
{
	OK,
	INCORRECT_CUB_FILE,
	MALLOC_FAIL,
	INVALID_FD,
	READ_FAIL,
	WRONG_ARGC,
	INVALID_MAP,
	MISSING_MAP,
	NOT_ALL_ELEMENTS,
	TOO_MANY_ELEMENTS,
	MISSING_PLAYER,
	TOO_MANY_PLAYERS,
	NO_NUMBER,
	INVALID_SIZE,
	ILLEGAL_CHAR,
	BAD_NUM_RANGE,
	NO_COMMA,
	INVALID_PATH,
	NO_SPRITE,
}				t_error_code;

typedef struct s_mlx
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
}				t_mlx;

typedef struct s_tex_array
{
	void		*tex_pnt;
	char		*tex_addr;
	int			tex_bpp;
	int			tex_ls;
	int			tex_endian;
	int			tex_hight;
	int			tex_width;

}				t_tex_array;

typedef struct s_tex
{
	t_tex_array	*tex_array;
	int			tex_ofset_x;
	int			tex_ofset_y;
}				t_tex;

typedef struct s_maze
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
	float		jump;
	float		step_size;
	char		player_or;
}				t_maze;

typedef struct s_player
{
	float		pos_x;
	float		pos_y;
	int			forward;
	int			backward;
	int			turndirection_r;
	int			turndirection_l;
	int			strafe_r;
	int			strafe_l;
	float		rotation;
	float		move_speed;
	float		rotation_speed;
}				t_player;

typedef struct s_rays
{
	float		fov_angle;
	int			strip_width;
	float		dist_to_plane;
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

typedef struct s_wall
{
	float		raydistance;
	char		wall_or;
	float		wall_hit_x;
	float		wall_hit_y;
	int			vertical_hit;
}				t_wall;

typedef struct s_port
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

/* parser */
void	parse(char *av, t_maze *blueprint);
void	parse_mapfile(t_maze *blueprint, char *mapfile);
void	parse_screenres(t_maze *blueprint, char *mapfile);
void	parse_textures(t_maze *blueprint, char *mapfile, char texture_type);
void	parse_color(t_maze *blueprint, char *mapfile, char type);
void	parse_map(t_maze *blueprint, char *mapfile);

/* parser/parser_utils */
int		cubfile_read_is_complete(t_maze *blueprint, char *mapfile);

/* parser/check_screenres */
void	check_screenres(t_maze *blueprint);
void	check_max_screensize(t_maze *blueprint, t_mlx mlx);
void	check_min_screensize(t_maze *blueprint);

/* parser/check_map */
int		check_opening_in_map(t_maze blueprint, int **map, int y, int x);
void	check_map(int **map, t_maze blueprint);
void	check_map_existence(char *mapfile, int count_y, int len);
int		loop_through_map(t_maze *blueprint, char mapfile, int x, int y);
void	write_map(t_maze *blueprint, char *mapfile);


void	ft_error(int error_code);
char	*ft_read(char *filename);

/* animate/key_button_hook */
int		x_button_hook(t_port *port);
int		key_press_hook(int keycode, t_port *port);
int		key_release_hook(int keycode, t_port *port);

/* animate/player_movement */
void	set_player(t_port *port);
void	move_player(t_port *port);

/* animate/render_frame */
int		render_frame(t_port *port);
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
int		put_color(int t, int r, int g, int b);

/* animate/ray_casting */
void	new_ray(t_port *port, t_rays *rays, t_player *player, int colum_id);
void	cast_all_rays(t_port *port, t_rays *rays);

/* animate/draw_walls */
void	draw_walls(t_port *port, t_rays *rays, t_wall *wall_array,
			int colum_id);
void	put_all_textures(t_port *port, t_wall *wall_array, int colum_id);
void	put_cur_texture(t_port *port, t_tex_array tex_array, t_rays *rays,
			int colum_id);

/* animate/ray_casting_utils */
float	distance_between_points(float x1, float y1, float x2, float y2);
void	normalize_ray_angle(float *ray_angle);
void	ray_direction(t_rays *rays);
int		wall_hit(float x, float y, t_port *port);

/* frame_build/dda.c */
void	horizontal_intercept(t_rays *rays, t_player *player);
void	check_horizontal_wallhit(t_port *port, t_rays *rays, t_maze *maze);
void	vertical_intercept(t_rays *rays, t_player *player);
void	check_vertical_wallhit(t_port *port, t_rays *rays, t_maze *maze);

/* animate/minimap */
void	draw_mini_player(t_port *port, float x, float y, int color);
void	draw_mini_map(t_port *port, t_maze *blueprint, float jump);
void	put_square(t_port *port, float x, float y, int color);
void	draw_line(t_mlx *mlx, t_player *player, float end_x, float end_y);

/* read_textures */
void	read_textures(t_port *port, t_maze *blueprint, t_tex *tex);
void	calculate_textures(t_port *port, t_tex *tex, char map);

/* free */
void	free_map(t_maze *blueprint);
void	free_texture_array(t_port *port, t_tex *textures);
void	free_texture_path(t_maze *blueprint);
//void	free_at_error(t_port *port);

#endif
