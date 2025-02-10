/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:31:56 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/10 19:23:59 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "mini_rt.h"

# define PATTERN_NONE 0
# define PATTERN_STRIPE 1
# define PATTERN_GRADIENT 2
# define PATTERN_RING 3
# define PATTERN_CHECKER 4

# define DEFAULT_REMAINING 4

/* Structure for tuples. We use tuples to represent points and vectors, colors.
** @param x: double The x value of the tuple.
** @param y: double The y value of the tuple.
** @param z: double The z value of the tuple.
** @param w: double The w value of the tuple. (1 for points, 0 for vectors)
*/
typedef struct	s_tuple
{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_tuple;

/* Structure for matrices.
** @param size: int The size of the matrix.
** @param matrix: double** The matrix.
*/
typedef struct	s_matrix
{
	int		size;
	double	matrix[4][4];
}			t_matrix;

/* Structure for rays.
** @param origin: t_tuple (Point)The origin of the ray.
** @param direction: t_tuple (Vector)The direction of the ray.
*/
typedef struct	s_ray
{
	t_tuple	origin;		//point
	t_tuple	direction;	//vector
}			t_ray;

typedef struct	s_pattern
{
	t_tuple		color_a;
	t_tuple		color_b;
	t_matrix	transform;
}				t_pattern;

/* Structure for materials.
** @param color: t_tuple The color of the material.
** @param ambient: double The ambient light of the material.
** @param diffuse: double The diffuse light of the material.
** @param specular: double The specular light of the material.
** @param shininess: double The shininess of the material.
*/
typedef struct	s_material
{
	t_tuple		color;
	double		ambient;
	double		diffuse;
	double		specular;
	double		shininess;
	t_pattern	pattern;
	int			has_pattern;
	double		reflective;
	double		transparency;
	double		refractive_index;
}			t_material;

/* Structure for spheres.
** @param center: t_tuple The center of the sphere.
** @param radius: double The radius of the sphere.
** @param transform: t_matrix The transformation matrix of the sphere.
** @param material: t_material The material of the sphere.
*/
/* typedef struct	s_sphere
{
	t_tuple		center;
	double		radius;
	t_matrix	transform;
	t_material	material;
}				t_sphere; */

/* typedef struct s_object {
	t_matrix	transform;
	t_material	material;
}				t_object;

typedef struct s_sphere {
	t_object	base;
	t_tuple		center;
	double		radius;
	t_matrix	transform;
	t_material	material;
}				t_sphere; */

typedef enum { SHAPE_SPHERE, SHAPE_PLANE } t_shape_type;

typedef struct s_shape {
	t_matrix		transform;
	t_material		material;
	t_shape_type	type;
	t_ray			saved_ray;// test
	t_tuple			center;
	double			radius;
}					t_shape;


typedef struct s_sphere {
	t_shape		base;
	t_tuple		center;
	double		radius;
}				t_sphere;

/* Structure for intersections.
** @param t: double The t value of the intersection.
** @param object: t_sphere The object of the intersection.
*/
/* typedef struct	s_intersection // t value and object
{
	double		t;
	t_sphere	*object;
}				t_intersection; */

/* Structure for intersections.
** @param t: double The t value of the intersection.
** @param *object: t_shape The object of the intersection.
** @param point: t_tuple The point of the intersection.
** @param eyev: t_tuple The eye vector.
** @param normalv: t_tuple The normal vector.
** @param inside: int The inside value.
*/
typedef struct s_intersection
{
	double		t;
	t_shape		*object;
	t_tuple		point;
	t_tuple 	over_point; // for reflection
	t_tuple 	under_point; // for refraction
	t_tuple		eyev; // vector
	t_tuple		normalv; // vector
	int			inside;
	t_tuple		reflectv; // vector
	double		n1;
	double		n2;
}				t_intersection;

/* Structure for intersections.
** @param count: int The number of intersections.
** @param array: t_intersection* The array of intersections.
*/
typedef struct	s_intersects // array of intersections
{
	int				count;
	t_intersection	*array;
}					t_intersects;

/* Structure for lights.
** @param position: t_tuple The position of the light.
** @param intensity: t_tuple The intensity of the light.
*/
typedef struct	s_light
{
	t_tuple	position; // point
	t_tuple	intensity; // color
}			t_light;

/* Structure for world.
** @param light: t_light The light of the world.
** @param sphere: t_sphere** The array of spheres in the world.
*/
typedef struct s_world
{
	t_light		light;
	t_shape		**shapes;
}				t_world;

/* Structure for camera.
** @param hsize: int The horizontal size of the camera.
** @param vsize: int The vertical size of the camera.
** @param field_of_view: double The field of view of the camera.
** @param transform: t_matrix The transformation matrix of the camera.
** @param pixel_size: double The pixel size of the camera.
** @param half_width: double The half width of the camera.
** @param half_height: double The half height of the camera.
*/
typedef struct s_camera
{
	int			hsize;
	int			vsize;
	double		field_of_view;
	t_matrix	transform;
	double		pixel_size;
	double		half_width;
	double		half_height;
}				t_camera;

#endif
