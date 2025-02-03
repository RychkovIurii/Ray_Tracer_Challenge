/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:31:56 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/03 15:58:31 by irychkov         ###   ########.fr       */
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

/* Structure for matrices.
** @param size: int The size of the matrix.
** @param matrix: double** The matrix.
*/
typedef struct	s_matrix
{
	int		size;
	double	**matrix;
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
	t_matrix	transform;
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

#endif
