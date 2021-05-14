/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/19 14:03:21 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/05/14 16:13:50 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# define KOPINK "\033[38;5;200m"
# define RES "\033[0m"

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
	int			jump_size;
}				t_maze;

typedef struct s_player
{
	int	pos_x;
	int	pos_y;
	int	walkdirection;
	int turndirection;
	double rotation;
	double	move_speed;
	double rotation_speed;
}				t_player;

typedef struct	s_rays
{
	double 		fov_angle;
	double		ray_angle;
//	float		wall_hit_x;
//	float		wall_hit_y;
//	float		distance;
	int			ray_up;
	int			ray_down;
	int			ray_right;
	int			ray_left;
//	int			verical_hit;
//	int			wall_hit_content;
	int			ray_num;
	int			strip_width;
	long		hx_intercept;
	long		hy_intercept;
	long		vx_intercept;
	long		vy_intercept;
	double		horz_xstep;
	int			horz_ystep;
	int			vert_xstep;
	double		vert_ystep;
	int			columnid;
}				t_rays;

typedef	struct	s_port
{
	t_mlx		*mlx;
	t_maze		*blueprint;
	t_player	*player;
	t_rays		*rays;
}				t_port;

void	init_maze(t_maze *blueprint);
void	init_mlx(t_mlx *mlx);
void	init_player(t_player *player);
void	init_rays(t_rays *rays, t_maze *blueprint);
void	parse(char *av, t_maze *blueprint);
void	parse_mapfile(t_maze *blueprint, char *mapfile);
void	parse_screenres(t_maze *blueprint, char *mapfile);
void	parse_textures(t_maze *blueprint, char *mapfile, char texture_type);
void	parse_color(t_maze *blueprint, char *mapfile, char type);
void	parse_map(t_maze *blueprint, char *mapfile);

/* animate/key_button_hook */
int		x_button_hook(t_mlx *mlx);
int		key_press_hook(int keycode, t_port *port);
int		key_release_hook(int keycode, t_port *port);

/* animate/player_movement */
void	set_player(t_port *port);
void	draw_player(t_port *port, int x, int y, int color);
void	walk_player(t_port *port);
int		wall_hit(int x, int y, t_port *port, int *wall_content);

/* animate/render_frame */
int		render_frame(t_port *port);
void	put_square(t_port *port, int x, int y, int color);
void	draw_line(t_mlx *mlx, double begin_x, double begin_y, double end_x, double end_y, int color);
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
int		put_color(int r, int g, int b);

/* animate/ray_casting */
void	new_ray(t_port *port, t_rays *rays, double ray_angle, int playerx, int playery);
void	cast_all_rays(t_port *port, int playerx, int playery);
