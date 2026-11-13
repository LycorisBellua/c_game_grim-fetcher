#ifndef STRUCTS_H
# define STRUCTS_H

typedef unsigned char	t_ubyte;
typedef unsigned int	t_uint;
typedef struct s_man	t_man;
typedef void			(*t_action)(t_man *man, int set);

typedef enum e_game_state
{
	GAME_STATE_NONE,
	GAME_STATE_PLAY,
	GAME_STATE_SUCCESS,
	GAME_STATE_FAILURE
}	t_game_state;

typedef enum e_key_state
{
	KEY_STATE_NONE,
	KEY_STATE_PRESSED,
	KEY_STATE_HELD,
	KEY_STATE_RELEASED
}	t_key_state;

/* Each key has 3 potential game states for 3 potential key states. */
typedef struct s_key
{
	int				keycode;
	t_key_state		state;
	t_action		actions[3][3];
}	t_key;

typedef struct s_list
{
	struct s_list	*prev;
	void			*data;
	struct s_list	*next;
}	t_list;

typedef struct s_color
{
	t_ubyte	r;
	t_ubyte	g;
	t_ubyte	b;
	t_ubyte	a;
}	t_color;

typedef struct s_vert
{
	t_ivec2	coord;
	t_color	color;
}	t_vert;

typedef struct s_img
{
	char	*id;
	t_ivec2	size;
	t_ivec2	shadow_offset;
	int		still_frame;
	size_t	cycle_len;
	size_t	cycle_index;
	long	elapsed_time_in_ms;
	long	cycle_time_in_ms;
	t_color	**cycle;
	t_color	**cycle_shadow;
}	t_img;

typedef struct s_png_seg
{
	char	*id;
	t_ivec2	size;
	t_ivec2	shadow_offset;
	int		still_frame;
	long	cycle_time_in_ms;
	size_t	cycle_len;
	t_ivec2	*cycle;
}	t_png_seg;

typedef struct s_png
{
	char		*path;
	char		*path_shadow;
	t_ivec2		size;
	t_color		*buf;
	t_color		*buf_shadow;
	size_t		segment_len;
	t_png_seg	*seg;
}	t_png;

typedef struct s_cell	t_cell;

struct s_cell
{
	char	symbol;
	t_img	*spr;
	int		is_obstacle;
	int		has_moved;
	int		is_visited;
	t_ivec2	pos;
	t_cell	*neighbors[4];
	t_cell	*parent;
	float	local_goal;
	float	global_goal;
};

typedef struct s_map
{
	t_ivec2	size;
	t_cell	*cells;
}	t_map;

typedef struct s_astar
{
	t_cell	*end;
	int		avoid_red;
}	t_astar;

typedef struct s_player
{
	t_ivec2	pos;
	int		steps;
	int		collected;
	int		to_collect;
}	t_player;

typedef struct s_frame
{
	GLuint	id;
	t_color	*buf;
	t_ivec2	size;
}	t_frame;

typedef struct s_res
{
	t_ivec2	monitor_size;
	t_ivec2	window_size_default;
	t_ivec2	window_size;
	t_ivec2	window_pos;
	float	ratio;
	t_ivec2	res;
	t_ivec2	viewport_size;
	t_ivec2	viewport_offset;
	int		is_fullscreen;
}	t_res;

struct s_man
{
	GLFWwindow		*window;
	GLuint			shader_program;
	GLint			uniform_loc;
	GLuint			pbo[2];
	int				pbo_index;
	char			*title;
	int				gl_loaded;
	t_frame			frame;
	float			dt;
	long			dt_ms;
	int				fps;
	int				reset_dt;
	t_res			res;
	t_game_state	game_state;
	t_player		player;
	t_key			keys[NBR_KEYS + 1];
	t_ivec2			cursor;
	int				show_debug;
	int				vsync;
	char			**json_paths;
	t_img			**images;
	int				gui_scale;
	t_img			*img_font;
	t_img			*img_cursor;
	t_img			*img_collec;
	int				map_index;
	char			**map_filenames;
	t_frame			frame_tmp;
	int				click;
	int				click_pending;
	t_ivec2			click_pos;
	int				zoom;
	t_img			*img_background;
	t_img			*img_ground;
	t_img			*img_red_ground;
	t_img			*img_wall_hor_one;
	t_img			*img_wall_hor_three;
	t_img			*img_wall_hor_one_cliff;
	t_img			*img_wall_ver_two;
	t_map			map;
	t_list			*clicked_path;
};

extern t_man	g_man;

#endif
