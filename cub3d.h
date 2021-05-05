/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/19 14:03:21 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/05/05 11:48:35 by lwiedijk      ########   odam.nl         */
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
	int			ray_num;
	int			strip_width;
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
int		x_button_hook(t_mlx *mlx);
int		key_press_hook(int keycode, t_port *port);
int		key_release_hook(int keycode, t_port *port);
int		render_frame(t_port *port);

