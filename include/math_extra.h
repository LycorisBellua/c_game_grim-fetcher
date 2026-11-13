#ifndef MATH_EXTRA_H
# define MATH_EXTRA_H

typedef struct s_vec2
{
	float	x;
	float	y;
}	t_vec2;

typedef struct s_ivec2
{
	int	x;
	int	y;
}	t_ivec2;

typedef struct s_uivec2
{
	unsigned int	x;
	unsigned int	y;
}	t_uivec2;

/* Clamp -------------------------------------------------------------------- */

int		clamp(int n, int min, int max);

/* Distance ----------------------------------------------------------------- */

float	dist(t_vec2 a, t_vec2 b);
float	dist_manhattan(t_vec2 a, t_vec2 b);

/* Random Number Generation ------------------------------------------------- */

int		rng_minmax(unsigned int *seed, int min, int max);

/* Square Root Approximation ------------------------------------------------ */

float	sqrt_approx(float n);
double	sqrt_approx_f64(double n);

/* Vectors ------------------------------------------------------------------ */

void	set_vec2(t_vec2 *v, float x, float y);
void	set_ivec2(t_ivec2 *v, int x, int y);

#endif
