/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:31:56 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/04 16:50:19 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "mini_rt.h"

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

/* Structure for 2x2 matrices.
** @param t_matrix2x2: double[2][2] The 2x2 matrix.
*/
typedef double	t_matrix2x2[2][2];

/* Structure for 3x3 matrices.
** @param t_matrix3x3: double[3][3] The 3x3 matrix.
*/
typedef double	t_matrix3x3[3][3];


/* Structure for 4x4 matrices.
** @param t_matrix4x4: double[4][4] The 4x4 matrix.
*/
typedef double	t_matrix4x4[4][4];

/* Structure for rays.
** @param origin: t_tuple (Point)The origin of the ray.
** @param direction: t_tuple (Vector)The direction of the ray.
*/
typedef struct	s_ray
{
	t_tuple	origin;		//point
	t_tuple	direction;	//vector
}			t_ray;

/* Structure for materials.
** @param color: t_tuple The color of the material.
** @param ambient: double The ambient light of the material.
** @param diffuse: double The diffuse light of the material.
** @param specular: double The specular light of the material.
** @param shininess: double The shininess of the material.
*/
typedef struct	s_material
{
	t_tuple	color;
	double	ambient;
	double	diffuse;
	double	specular;
	double	shininess;
}			t_material;

/* Structure for spheres.
** @param center: t_tuple The center of the sphere.
** @param radius: double The radius of the sphere.
** @param transform: t_matrix The transformation matrix of the sphere.
** @param material: t_material The material of the sphere.
*/
typedef struct	s_sphere
{
	t_tuple		center;
	double		radius;
	t_matrix4x4	*transform;
	t_material	material;
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
** @param *object: t_sphere The object of the intersection.
** @param point: t_tuple The point of the intersection.
** @param eyev: t_tuple The eye vector.
** @param normalv: t_tuple The normal vector.
** @param inside: int The inside value.
*/
typedef struct s_intersection
{
	double		t;
	t_sphere	*object;
	t_tuple		point;
	t_tuple		eyev; // vector
	t_tuple		normalv; // vector
	int			inside;
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
	t_sphere	**sphere;
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
	t_matrix4x4	transform;
	double		pixel_size;
	double		half_width;
	double		half_height;
}				t_camera;

#endif
