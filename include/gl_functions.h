#ifndef GL_FUNCTIONS_H
#define GL_FUNCTIONS_H

#include <GL/gl.h>
#include <GL/glext.h>
#include "lib/glfw3.h"

int init_gl_functions(void);

typedef void	(APIENTRY *GL_AS)(GLuint program, GLuint shader);
typedef void	(APIENTRY *GL_BB)(GLenum target, GLuint buffer);
typedef void	(APIENTRY *GL_BVA)(GLuint array);
typedef void	(APIENTRY *GL_BD)(GLenum target, GLsizeiptr size,
					const void* data, GLenum usage);
typedef void	(APIENTRY *GL_COS)(GLuint shader);
typedef GLuint	(APIENTRY *GL_CP)(void);
typedef GLuint	(APIENTRY *GL_CS)(GLenum shaderType);
typedef void	(APIENTRY *GL_DB)(GLsizei n, const GLuint* buffers);
typedef void	(APIENTRY *GL_DP)(GLuint program);
typedef void	(APIENTRY *GL_DS)(GLuint shader);
typedef void	(APIENTRY *GL_DVA)(GLsizei n, const GLuint* arrays);
typedef void	(APIENTRY *GL_EVAA)(GLuint index);
typedef void	(APIENTRY *GL_GB)(GLsizei n, GLuint* buffers);
typedef void	(APIENTRY *GL_GVA)(GLsizei n, GLuint* arrays);
typedef GLint	(APIENTRY *GL_GUL)(GLuint program, const GLchar* name);
typedef void	(APIENTRY *GL_GVAI)(GLuint index, GLenum pname, GLuint* params);
typedef void	(APIENTRY *GL_LP)(GLuint program);
typedef void	(APIENTRY *GL_SS)(GLuint shader, GLsizei count,
					const GLchar** string, const GLint* length);
typedef void	(APIENTRY *GL_U1I)(GLint location, GLint v0);
typedef void	(APIENTRY *GL_UP)(GLuint program);
typedef void	(APIENTRY *GL_VAP)(GLuint index, GLint size, GLenum type,
					GLboolean normalized, GLsizei stride, const void* pointer);

/*
	System GL libraries only guarantee exports up to OpenGL 1.1. Newer functions 
   live in the graphics driver, so their addresses are queried at runtime 
   (after a context is made current). Each name is aliased to a prefixed 
   variable to avoid clashing with symbols the system library may export under 
   the same names.
*/
#define glAttachShader gf_glAttachShader
#define glBindBuffer gf_glBindBuffer
#define glBindVertexArray gf_glBindVertexArray
#define glBufferData gf_glBufferData
#define glCompileShader gf_glCompileShader
#define glCreateProgram gf_glCreateProgram
#define glCreateShader gf_glCreateShader
#define glDeleteBuffers gf_glDeleteBuffers
#define glDeleteProgram gf_glDeleteProgram
#define glDeleteShader gf_glDeleteShader
#define glDeleteVertexArrays gf_glDeleteVertexArrays
#define glEnableVertexAttribArray gf_glEnableVertexAttribArray
#define glGenBuffers gf_glGenBuffers
#define glGenVertexArrays gf_glGenVertexArrays
#define glGetUniformLocation gf_glGetUniformLocation
#define glGetVertexAttribIuiv gf_glGetVertexAttribIuiv
#define glLinkProgram gf_glLinkProgram
#define glShaderSource gf_glShaderSource
#define glUniform1i gf_glUniform1i
#define glUseProgram gf_glUseProgram
#define glVertexAttribPointer gf_glVertexAttribPointer

extern GL_AS   glAttachShader;
extern GL_BB   glBindBuffer;
extern GL_BVA  glBindVertexArray;
extern GL_BD   glBufferData;
extern GL_COS  glCompileShader;
extern GL_CP   glCreateProgram;
extern GL_CS   glCreateShader;
extern GL_DB   glDeleteBuffers;
extern GL_DP   glDeleteProgram;
extern GL_DS   glDeleteShader;
extern GL_DVA  glDeleteVertexArrays;
extern GL_EVAA	glEnableVertexAttribArray;
extern GL_GB   glGenBuffers;
extern GL_GVA  glGenVertexArrays;
extern GL_GUL  glGetUniformLocation;
extern GL_GVAI glGetVertexAttribIuiv;
extern GL_LP   glLinkProgram;
extern GL_SS   glShaderSource;
extern GL_U1I  glUniform1i;
extern GL_UP   glUseProgram;
extern GL_VAP  glVertexAttribPointer;

#endif
