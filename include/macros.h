#ifndef MACROS_H
# define MACROS_H

/*
	- The minimum window size is 128x128 while the maximum is the monitor size.
	- Use a value inferior or equal to 0.1 as the aspect ratio to express 
	"whatever the monitor's aspect ratio is". For example 0 or -1.
*/

# define TITLE "Grim Fetcher"
# define WINDOW_WIDTH  (640 * 1)
# define WINDOW_HEIGHT (360 * 1)
# define ASPECT_RATIO (16.0f / 9)
# define FONT_PAD 4
# define FONT_SIZE_X 7
# define FONT_SIZE_Y 12
# define MAP_DIR "assets/maps"
# define IMG_JSON_DEFAULT "assets/img/index.json"
# define ID_FONT "font"
# define ID_CURSOR "cursor"
# define ID_GUI_COLLEC "soul_gui"
# define ID_BACKGROUND "background"
# define ID_GROUND "ground"
# define ID_RED_GROUND "red_ground"
# define ID_WALL_HOR_ONE "wall_hor_one"
# define ID_WALL_HOR_THREE "wall_hor_three"
# define ID_WALL_HOR_ONE_CLIFF "wall_hor_one_cliff"
# define ID_WALL_VER_TWO "wall_ver_two"
# define NBR_KEYS 16

# define E_NO_MAP "No *.map file was found"
# define E_FAIL_MEM "Memory cannot be allocated"
# define E_FAIL_GLFW "The GLFW lib cannot be initialized"
# define E_FAIL_WINDOW "The window cannot be created"
# define E_FAIL_WINDOW_GL "The window cannot be created. The issue may be " \
	"with the GLFW library, but comes more likely from the OpenGL library. " \
	"Check that your drivers are properly installed"
# define E_FAIL_GL_FUNC "The OpenGL functions cannot be loaded"
# define E_FAIL_SHADER "The vertex and/or fragment shaders cannot be compiled"
# define E_FAIL_SHADER_PROG "The shader program cannot be linked"
# define E_FAIL_UNIFORM_FRAME_TEXTURE "The \"frame_texture\" uniform is " \
	"either not found or unused in the shader program"

/* Parsing ------------------------------------------------------------------ */

# define E_MAP_READ "The map file cannot be read"
# define E_MAP_TYPE "The map file doesn't have the *.map extension"
# define E_MAP_NAME "The map file doesn't have a name"
# define E_FAIL_JSON "The JSON file for images cannot be loaded"
# define E_IMG_NO_PATH "An image object of the JSON file has no \"path\""
# define E_IMG_NO_SEG "An image object of the JSON file has no segment"
# define E_IMG_NO_ID "An image segment has no \"id\""
# define E_IMG_BAD_SIZE "An image segment has no \"size\", or a size of 0"
# define E_IMG_NO_CYCLE "An image segment has no frame in its \"cycle\""
# define E_IMG_BAD_STILL "The \"still_frame\" of an image segment is " \
	"outside of its cycle"
# define E_IMG_OUT_OF_BOUNDS "An image segment reaches outside of its PNG file"
# define E_IMG_SHADOW_SIZE "The shadow PNG doesn't have the size of its image"
# define E_NO_IMG "PNG image not found"
# define E_MAP_SYMBOL "Unknown map symbol - Valid ones are \"01BCEGP\""
# define E_MAP_NO_COLLEC "The map has no collectible ('C')"
# define E_MAP_NO_EXIT "The map has no exit ('E')"
# define E_MAP_EXITS "The map has more than one exit ('E')"
# define E_MAP_NO_PLAYER "The map has no player start ('P')"
# define E_MAP_PLAYERS "The map has more than one player start ('P')"
# define E_MAP_RECT "The map is not rectangular"
# define E_MAP_WALLS "The map is not closed off by walls"
# define E_MAP_UNREACHABLE "The exit or a collectible cannot be reached"
# define E_MAP_ENEMY_START "A slime ('B' or 'G') is next to the player " \
	"start ('P')"

#endif
