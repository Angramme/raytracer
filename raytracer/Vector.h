#pragma once
#include <iostream>
#include <cmath>

template <class T>
struct Vec3 {
	union {
		struct {
			T r, g, b;
		};
		struct {
			T x, y, z;
		};
		T data[3];
	};

	Vec3()
		: x(0), y(0), z(0)
	{};

	Vec3(T a, T b, T c)
		: x(a), y(b), z(c)
	{};
  
	
	////USEFUL STATIC INLINES

	constexpr inline static Vec3<T> reflect(const Vec3<T>& V, const Vec3<T>& N) {
		return V - N * 2 * V.dot(N);
	}

	constexpr inline static Vec3<T> normalize(const Vec3<T>& o) {
		return o * (1 / o.length());
	};


	////FUNCTIONS
	
	inline void set(T px, T py, T pz) {
		x = px;
		y = py;
		z = pz;
	}

	inline T dot(const Vec3<T>& o) const {
		return x * o.x + y * o.y + z * o.z;
	};

	inline Vec3<T> cross(const Vec3<T>& o) const {
		return Vec3<T>(
			y*o.z - z*o.y,
			z*o.x - x*o.z,
			x*o.y - y*o.x
		);
	}

	inline T lengthSQ() const {
		return x * x + y * y + z * z;
	};

	inline T length() const {
		return std::sqrtf(lengthSQ());
	};

	inline Vec3<T>& normalize() {
		(*this) /= length();
		return *this;
	}

	
	////OPERATORS

	inline Vec3<T> operator-() const {
		return Vec3<T>(-x, -y, -z);
	}

	inline Vec3<T>& operator+=(const Vec3<T>& o) {
		x += o.x;
		y += o.y;
		z += o.z;
		return *this;
	};

	inline Vec3<T>& operator-=(const Vec3<T>& o) {
		x -= o.x;
		y -= o.y;
		z -= o.z;
		return *this;
	};

	inline Vec3<T>& operator*=(const Vec3<T>& o) {
		x *= o.x;
		y *= o.y;
		z *= o.z;
		return *this;
	};

	inline Vec3<T>& operator/=(const Vec3<T>& o) {
		x /= o.x;
		y /= o.y;
		z /= o.z;
		return *this;
	};



	Vec3<T>& operator+=(const T& o) {
		x += o;
		y += o;
		z += o;
		return *this;
	};

	Vec3<T>& operator-=(const T& o) {
		x -= o;
		y -= o;
		z -= o;
		return *this;
	};

	inline Vec3<T>& operator*=(const T& o) {
		x *= o;
		y *= o;
		z *= o;
		return *this;
	};

	inline Vec3<T>& operator/=(const T& o) {
		x /= o;
		y /= o;
		z /= o;
		return *this;
	};


	inline Vec3<T> operator+(const Vec3<T>& o) const {
		return Vec3<T>(
			x + o.x,
			y + o.y,
			z + o.z
			);
	};

	inline Vec3<T> operator-(const Vec3<T>& o) const {
		return Vec3<T>(
			x - o.x,
			y - o.y,
			z - o.z
			);
	};

	inline Vec3<T> operator*(const Vec3<T>& o) const {
		return Vec3<T>(
			x * o.x,
			y * o.y,
			z * o.z
			);
	};

	inline Vec3<T> operator/(const Vec3<T>& o) const {
		return Vec3<T>(
			x / o.x,
			y / o.y,
			z / o.z
			);
	};



	inline Vec3<T> operator+(const T& o) const {
		return Vec3<T>(
			x + o,
			y + o,
			z + o
			);
	};

	inline Vec3<T> operator-(const T& o) const {
		return Vec3<T>(
			x - o,
			y - o,
			z - o
			);
	};

	inline Vec3<T> operator*(const T& o) const {
		return Vec3<T>(
			x * o,
			y * o,
			z * o
			);
	};

	inline Vec3<T> operator/(const T& o) const {
		return Vec3<T>(
			x / o,
			y / o,
			z / o
			);
	};
};

template <class T>
std::ostream & operator << (std::ostream &in, const Vec3<T>&v)
{
	std::cout << "Vec3<"
		<< typeid(T).name()
		<< "> {" << v.x << ", " << v.y << ", " << v.z << "};";
	return in;
}

using Vec3f = Vec3<float>;
using Vec3i = Vec3<int>;
