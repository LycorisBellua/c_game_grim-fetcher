#ifndef GRIM_FETCHER_H
# define GRIM_FETCHER_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdarg.h>
# include <dirent.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <math.h>
# include "math_extra.h"
# include "lib/lodepng.h"
# include <GL/gl.h>
# include "lib/glfw3.h"
# include "gl_functions.h"
# include "macros.h"
# include "structs.h"

/* Window ------------------------------------------------------------------- */

int			create_window(t_man *man, const char *title, t_ivec2 size,
				float aspect_ratio);
void		set_monitor_size(t_man *man);
int			set_resolution(t_man *man, t_ivec2 window_size,
				float aspect_ratio);
void		set_viewport(t_man *man, t_ivec2 window_size);
void		set_vsync(t_man *man);
void		toggle_fullscreen(t_man *man);
void		framebuffer_size_callback(GLFWwindow *window, int x, int y);
void		close_window_callback(t_man *man);
int			window_pos_to_view(t_man *man, double xpos, double ypos,
				t_ivec2 *pos);

/* Frame -------------------------------------------------------------------- */

int			init_frame(t_man *man);
void		display_frame(t_man *man);
void		free_frame(t_man *man);
int			create_shader_program(void);
void		free_shader_program(t_man *man);
int			create_uniform(t_man *man);
void		free_uniform(t_man *man);
int			create_mesh(void);
void		render_mesh(void);
void		free_mesh(void);

/* Input -------------------------------------------------------------------- */

void		physical_key_callback(GLFWwindow *window, int key, int scancode,
				int action, int mods);
void		scroll_callback(GLFWwindow *window, double x_offset,
				double y_offset);
void		mouse_callback(GLFWwindow *window, int button, int action,
				int mods);
void		cursor_pos_callback(GLFWwindow *window, double xpos, double ypos);
void		init_input_handling(t_man *man);
void		init_input_keys(t_man *man);
void		execute_input_action(t_man *man, int keycode, t_key_state state);
void		cancel_keys_in_game_state(t_man *man);
void		change_game_state(t_man *man, t_game_state new_state);
void		action_move_left(t_man *man, int set);
void		action_move_right(t_man *man, int set);
void		action_move_to_start(t_man *man, int set);
void		action_toggle_vsync(t_man *man, int set);
void		action_toggle_fullscreen(t_man *man, int set);
void		action_toggle_debug(t_man *man, int set);
void		action_close_window(t_man *man, int set);
void		action_move_up(t_man *man, int set);
void		action_move_down(t_man *man, int set);
void		action_continue(t_man *man, int set);

/* Time --------------------------------------------------------------------- */

void		set_dt_and_fps(t_man *man);
void		display_fps(t_man *man);
long		get_time(void);

/* Colors ------------------------------------------------------------------- */

t_color		get_color_rgba(t_ubyte r, t_ubyte g, t_ubyte b, t_ubyte a);
t_color		alpha_blending(t_color prev, t_color new);
t_color		get_frame_color(t_frame *f, int x, int y);

/* Draw --------------------------------------------------------------------- */

void		draw_point(t_frame *f, t_color c, int x, int y);
void		draw_scaled_point(t_frame *f, t_color c, t_ivec2 at, int scale);
void		fill_frame(t_frame *frame, t_color c);
void		draw_image(t_man *man, t_img *img, t_ivec2 pos);
void		draw_image_scaled(t_man *man, t_img *img, t_ivec2 pos, int scale);
void		draw_cursor(t_man *man, t_img *img, t_ivec2 p, int cyc);
void		draw_font(t_man *man, t_ivec2 *pos, const char *str);
void		draw_image_on_frame(t_frame *frame, t_img *img, t_ivec2 pos,
				int scale);
void		render(t_man *man);
void		copy_frame(t_frame *dst, t_frame *src, int zoom_factor);
void		render_map(t_man *man, t_frame *frame);
void		render_background(t_man *man);
void		render_gui(t_man *man);
int			game_over_screen(t_man *man);
void		draw_walls(t_man *man, t_frame *frame, t_ivec2 pos, t_ivec2 i);
t_img		*get_spr_by_symbol(t_man *man, char symbol);
void		get_map_view(t_man *man, t_ivec2 *cell_size, t_ivec2 *offset);
int			get_map_zoom(t_man *man);

/* Images ------------------------------------------------------------------- */

t_png		*load_png_from_path(const char *path);
void		free_png(t_png *png);
t_img		*create_empty_image(const char *id, t_ivec2 size, t_ubyte alpha);
t_img		*duplicate_image(const char *dst_id, t_img *src);
int			update_image_array(t_man *man, const char *path);
int			register_json_path(t_man *man, const char *path);
void		discard_new_images(t_man *man, size_t start, const char *path);
int			check_png_segments(t_png *file);
int			create_images_from_file(t_man *man, t_png *file, size_t *i_img);
void		cut_image(t_png *file, t_img *img, size_t i);
t_img		*get_image(t_man *man, const char *id);
void		advance_all_image_cycles(t_man *man);
void		add_outline_to_font(t_img *font);
void		free_images(t_man *man);
void		free_image(t_img *img, void (free_fct)(void *));
int			create_background(t_man *man);
int			add_red_version_of_ground(t_man *man);

/* JSON --------------------------------------------------------------------- */

char		**get_json_content(const char *filepath);
void		free_json_content(char **content);
int			is_field(char *line, const char *field);
char		*get_string_value(char *line);
int			get_int_value(char *line);
t_ivec2		get_ivec2_value(char *line);
void		set_string_value(char **dst, char *line);
int			set_png_file_obj(t_png *file, char **lines, size_t *i);
void		free_and_reset_png_file_obj(t_png *file);
void		parse_segments(t_png *file, char **lines, size_t *i);
void		free_segments(t_png *file);

/* Files -------------------------------------------------------------------- */

char		*get_absolute_path(const char *path);
const char	*get_filename(const char *path);
int			has_extension(const char *name, const char *ext);

/* Utils -------------------------------------------------------------------- */

int			put_error(const char *msg, const char *arg, int errnum);
char		*gnl(int fd);
char		*strjoin(char const *s1, char const *s2);
char		*itoa_dec(int number);
void		free_arr(void **arr, void (free_fct)(void *));
size_t		count_arr_elems(void **arr);
t_list		*list_new(void *data);
void		list_del_one(t_list **list, void (*del)(void *));
void		list_add_front(t_list **list, t_list *new);
int			list_add_sorted(t_list **list, t_list *new,
				int (*f)(void *, void *));
void		list_clear(t_list **list, void (*del)(void *));

/* Init --------------------------------------------------------------------- */

void		deinit(t_man *man);
int			reload_game(t_man *man, int next_map);
void		game_deinit(t_man *man);
int			init_images(t_man *man);
void		deinit_images(t_man *man);
void		set_map_filenames(t_man *man);
void		free_map_filenames(t_man *man);

/* Map ---------------------------------------------------------------------- */

int			set_map_and_player(t_man *man, char *path);
char		**get_map_data(char *path);
int			are_symbols_valid(char **map);
int			is_map_rectangular_and_closed_off(char **map);
char		**copy_map(int *fd, char *path);
void		free_map_data(char **map);
int			are_collectibles_and_exit_accessible(t_man *man);
int			is_wall(t_map *map, int x, int y);
t_cell		*find_cell_by_symbol(t_cell *map, char symbol);
t_cell		*find_neighbor(t_cell *cell, const char *symbols);
int			is_cell_an_enemy_neighbor(t_man *man, t_ivec2 i);
void		move_symbol(t_map *map, t_ivec2 start, t_ivec2 end);

/* Game --------------------------------------------------------------------- */

void		move_player(t_man *man, int x, int y);
void		move_enemies(t_man *man, long dt);
t_list		*get_path(t_man *man, t_cell *start, t_cell *end, int avoid_red);
void		move_along_clicked_path(t_man *man, long dt);

#endif
