# pragma once
# include <vecmath.h>

float dot(Vector4f a, Vector4f b, Matrix4f g);
float dot(Vector3f a, Vector3f b, Matrix4f g);
Vector4f get_negative_null_vector(Vector3f v, Matrix4f g);