#pragma once

#include "Vector.h"

class Scene;
class Camera;
class Ray;

class Renderer {
	Scene* m_current_scene;
	Camera* m_current_cam;
	//bitmap_image* m_current_image;

	mutable unsigned int m_depth = 0;
	unsigned int m_depth_limit = 1;

public:
	Renderer()
		: m_current_cam(nullptr), m_current_scene(nullptr)
	{}

	Vec3f cast_ray(const Ray& ray) const;
	inline void reset_depth_cap() { m_depth = 0; }

	////GETTERS AND SETTERS

	inline Scene* get_scene() const { return m_current_scene; }
	inline Camera* get_camera() const { return m_current_cam; }

	inline void set_scene(Scene* scene) { m_current_scene = scene; }
	inline void set_camera(Camera* camera) { m_current_cam = camera; }

	inline int get_depth_limit() const { return m_depth_limit; }
	inline void set_depth_limit(const int& n) { m_depth_limit = n; }
	//inline bitmap_image* get_image() const { return m_current_image; }
};