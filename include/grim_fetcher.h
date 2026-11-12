#ifndef GRIM_FETCHER_H
#define GRIM_FETCHER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <dirent.h>
#include <math.h>
#include <GL/gl.h>
#include "gl_functions.h"
#include "lib/glfw3.h"
#include "lib/lodepng.h"

#define IMG_JSON_DEFAULT "assets/img/index.json"
#define ID_BACKGROUND "background"
#define ID_CURSOR "cursor"
#define ID_FONT "font_default"
#define ID_GROUND "ground"
#define ID_RED_GROUND "red_ground"
#define ID_WALL_HOR_ONE "wall_hor_one"
#define ID_WALL_HOR_THREE "wall_hor_three"
#define ID_WALL_HOR_ONE_CLIFF "wall_hor_one_cliff"
#define ID_WALL_VER_TWO "wall_ver_two"
#define ID_SOUL_GUI "soul_gui"

#define E_FAIL_MEM "Memory cannot be allocated"
#define E_FAIL_JSON "The JSON file for images cannot be loaded"
#define E_NO_IMG "Image not found"
#define E_IMG_NO_PATH "An image object of the JSON file has no \"path\""
#define E_IMG_NO_SEG "An image object of the JSON file has no segment"
#define E_IMG_NO_ID "An image segment has no \"id\""
#define E_IMG_BAD_SIZE "An image segment has no \"size\", or a size of 0"
#define E_IMG_NO_CYCLE "An image segment has no frame in its \"cycle\""
#define E_IMG_BAD_STILL "The \"still_frame\" of an image segment is outside of " \
	"its cycle"
#define E_IMG_OUT_OF_BOUNDS "An image segment reaches outside of its PNG file"
#define E_IMG_SHADOW_SIZE "The shadow PNG doesn't have the size of its image"

typedef unsigned char t_ubyte;
typedef unsigned int t_uint;

enum state
{
	ONGOING,
	VICTORY,
	FAILURE,
};

typedef struct s_uivec2
{
	t_uint x;
	t_uint y;
} t_uivec2;

typedef struct s_ivec2
{
	int x;
	int y;
} t_ivec2;

typedef struct s_vec2
{
	double x;
	double y;
} t_vec2;

typedef struct s_color
{
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
} t_color;

typedef struct s_vert
{
	t_ivec2 coord;
	t_color color;
} t_vert;

typedef struct s_list
{
	void          *data;
	struct s_list *next;
} t_list;

/* Unlike Olafur, cycles are stored row-major, since nothing is raycasted. */
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

typedef struct s_player
{
	t_ivec2 pos;
	int     steps;
	int     collected;
	int     to_collect;
	int     health;
	int     stamina;
} t_player;

typedef struct s_cell t_cell;

struct s_cell
{
	char    symbol;
	t_img   *spr;
	int     is_obstacle;
	int     is_visited;
	t_ivec2 pos;
	t_cell  *neighbors[4];
	t_cell  *parent;
	double  local_goal;
	double  global_goal;
};

typedef struct s_map
{
	t_ivec2 size;
	t_cell  *cells;
} t_map;

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

typedef struct s_frame
{
	GLuint   id;
	t_ivec2  size;
	t_ivec2  real_size;
	int      thickness;
	GLubyte  *buf;
} t_frame;

typedef struct s_res
{
	t_ivec2 monitor_size;
	double aspect_ratio;
	t_ivec2 window_size_default;
	t_ivec2 window_size;
	t_ivec2 window_pos;
	t_ivec2 viewport_size;
	t_ivec2 viewport_offset;
	int     is_fullscreen;
	t_ivec2 fullscreen;
} t_res;

#define NBR_FRAMES 3
typedef struct s_man
{
	int        map_index;
	char       **map_filenames;
	GLFWwindow *window;
	GLuint     shader_program;
	double     delta_time;
	double     fps_count;
	t_res      res;
	t_frame    *frame[NBR_FRAMES + 1];
	int        curr_frame;
	t_player   player;
	t_ivec2    cursor;
	int        click;
	t_ivec2    click_pos;
	int        zoom;
	enum state state;
	long       dt_ms;
	char       **json_paths;
	t_img      **images;
	t_img      *img_background;
	t_img      *img_cursor;
	t_img      *img_font;
	t_img      *img_ground;
	t_img      *img_red_ground;
	t_img      *img_wall_hor_one;
	t_img      *img_wall_hor_three;
	t_img      *img_wall_hor_one_cliff;
	t_img      *img_wall_ver_two;
	t_img      *img_soul_gui;
	t_map      map;
	t_list     *clicked_path;
} t_man;

extern t_man man;

/* Init --------------------------------------------------------------------- */

int			reload_game(void);
int			init_images(void);
void		deinit_images(void);
void		set_map_filenames(void);
void		free_map_filenames(void);
int			set_map_and_player(char *path);
char		*read_file(char* filepath);
int			get_map_fd(char *path);
char		**copy_map(int *fd, char *path);
char		**get_map_data(char *path);
void		free_map_data(char **map);
int			are_collectibles_and_exit_accessible(void);
int			create_background(void);
int			add_red_version_of_ground(void);
int			is_cell_a_slime_neighbor(t_ivec2 i);
int			create_mesh(void);
void		render_mesh(void);
void		free_mesh(void);
int			create_shader_program(void);
void		free_shader_program(void);
int			create_uniform(void);
void		free_uniform(void);
int			create_frames(void);
void		free_frames(void);
GLFWwindow	*get_window(char* title);
void		toggle_fullscreen(GLFWwindow* window);
void		physical_key_callback(GLFWwindow* window, int key, int scancode,
				int action, int mods);
void		scroll_callback(GLFWwindow* window, double x_offset,
				double y_offset);
void		mouse_callback(GLFWwindow* window, int button, int action,
				int mods);
void		cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);

/* Colors ------------------------------------------------------------------- */

t_color		get_color_rgba(GLubyte r, GLubyte g, GLubyte b, GLubyte a);
t_color		get_color_hex(char* str, GLubyte alpha);
t_color		get_alpha_blended_color(t_color prev, t_color new);
t_color		get_frame_color(t_frame* f, int x, int y);
int			cmp_color(t_color a, t_color b);

/* Draw --------------------------------------------------------------------- */

void		use_frame(t_frame* f);
void		clear_drawing(t_frame *f, GLubyte alpha);
void		save_drawing(t_frame* f);
void		render(void);
long		get_delta_time(void);
long		get_time(void);
int			game_over_screen(void);
t_img		*get_spr_by_symbol(char symbol);
void		render_background(t_frame *frame);
void		draw_walls(t_frame *frame, t_ivec2 pos, t_ivec2 i);
void		copy_frame(t_frame *dst, t_frame *src, int zoom_factor);
void		render_gui(t_frame *frame);
void		draw_point(t_frame *f, t_color c, int x, int y);
void		draw_sprite(t_frame *frame, t_img *sprite, t_ivec2 pos);
void		draw_cursor(t_frame *frame, t_img *sprite, t_ivec2 p, int cyc);
void		draw_font_default(t_frame *frame, t_ivec2 *pos, char *str);

/* Images ----------------------------------------------------------------- */

t_png		*load_png_from_path(const char *path);
void		free_png(t_png *png);
char		**get_json_content(t_man *man, const char *filepath);
void		free_json_content(char **content);
int			is_field(char *line, const char *field);
char		*get_string_value(char *line);
int			get_int_value(char *line);
t_ivec2		get_ivec2_value(char *line);
int			set_png_file_obj(t_png *file, char **lines, size_t *i);
void		free_and_reset_png_file_obj(t_png *file);
void		free_segments(t_png *file);
void		set_string_value(char **dst, char *line);
void		parse_segments(t_png *file, char **lines, size_t *i);
int			update_image_array(t_man *man, const char *path);
int			register_json_path(t_man *man, const char *path);
void		discard_new_images(t_man *man, size_t start, const char *path);
int			check_png_segments(t_png *file);
int			create_images_from_file(t_man *man, t_png *file, size_t *i_img);
void		cut_image(t_png *file, t_img *img, size_t i);
t_img		*create_empty_image(const char *id, t_ivec2 size, t_ubyte alpha);
t_img		*duplicate_image(const char *dst_id, t_img *src);
t_img		*get_image(t_man *man, const char *id);
void		advance_all_image_cycles(t_man *man);
void		add_outline_to_font(t_img *font);
void		free_images(t_man *man);
void		free_image(t_img *img, void (free_fct)(void *));

/* Game --------------------------------------------------------------------- */

t_list		*get_path(t_cell *start, t_cell *end);
void		move_along_clicked_path(long dt);
t_cell		*find_cell_by_symbol(t_cell *map, char symbol);
void		move_player(int x, int y);
void		move_symbol(t_map *map, t_ivec2 start, t_ivec2 end);
void		move_slimes(long dt);

/* Math --------------------------------------------------------------------- */

double		f_clamp(double number, double min, double max);
int			i_clamp(int number, int min, int max);
int			i_min(int a, int b);
double		f_sqrt(double number);
double		f_dist_euclidean(double ax, double ay, double bx, double by);
double		f_dist_manhattan(double ax, double ay, double bx, double by);
int			rng_minmax(int *seed, int min, int max);
void		set_vec2(t_vec2 *vector, double x, double y);
void		set_ivec2(t_ivec2 *vector, int x, int y);

/* Utils -------------------------------------------------------------------- */

char		*gnl(int fd);
int			put_error(const char *msg, const char *arg, int errnum);
void		free_arr(void **arr, void (free_fct)(void *));
size_t		count_arr_elems(void **arr);
char		*get_absolute_path(const char *path);
const char	*get_filename(const char *path);
char		*itoa_dec(int number);
t_list		*list_new(void *content);
void		list_add_front(t_list **list, t_list *new);
int			list_add_sorted(t_list **list, t_list *new,
				int (*f)(void *, void *));
void		list_pop(t_list **list, void (*del)(void *));
void		list_clear(t_list **list, void (*del)(void *));
int			list_size(t_list *list);

#endif
