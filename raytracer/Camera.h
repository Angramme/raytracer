#pragma once

#include "Vector.h"
class Ray;

class Camera {
	int m_width, m_height;
	float m_fov;
	float m_ippu; // inverse of pixels per unit

public:
	Vec3f pos;
	Vec3f rot;

	Camera(int w, int h, float fov)
		: m_width(w), m_height(h), m_ippu(1.0f / 1)
	{
		m_fov = fov < 3.13 ? fov : 3.13;
	}

public:
	Ray get_ray(int x, int y) const;
	inline void set_PPU(int ppu) { m_ippu = 1.0f / ppu; }
};