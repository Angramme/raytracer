#pragma once

template<class T>
class Vec3;
using Vec3f = Vec3<float>;

class Ray;


class Shape {
public:
	virtual float intersect(const Ray& ray) const = 0;
	virtual Vec3f get_normal(const Vec3f& p) const = 0;
};