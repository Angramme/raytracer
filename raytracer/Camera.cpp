#include <cmath>
#include "Camera.h"
#include "Ray.h"

Ray Camera::get_ray(int x, int y) const {
	float x_angle = (float)x / (float)m_width * m_fov - m_fov * 0.5;
	float y_angle = (float)y / (float)m_width * m_fov - m_fov * 0.5;
	x_angle *= std::cosf(y_angle);

	return Ray(
		Vec3f(x * m_ippu, y * m_ippu, 0), 
		Vec3f(
			std::sinf(x_angle),
			std::sinf(y_angle) * std::cosf(x_angle),
			std::cosf(x_angle) * std::cosf(y_angle)
		)
	);
}