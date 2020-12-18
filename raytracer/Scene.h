#pragma once

#include <vector>
#include <memory>

#include "Shape.h"
#include "Light.h"
#include "Material.h"
#include "Background.h"

class Ray;

template <class T>
class Vec3;
using Vec3f = Vec3<float>;


class Scene {
protected:
	std::vector<std::unique_ptr<Shape>> m_shape_ptrs;
	std::vector<std::unique_ptr<Material>> m_material_ptrs;
	std::vector<std::unique_ptr<Light>> m_light_ptrs;

	std::unique_ptr<Background> m_background_ptr = nullptr;

public:

	struct intersection_data {
		Shape* shape;
		Material* material;
		float t;
	};
	virtual intersection_data intersect(const Ray& ray) const;
	
	/*
	push(new Sphere(//sphere arguments//), new PhongMat(//agruments//));
	*/
	inline void push(Shape* shape, Material* material) {
		m_shape_ptrs.push_back(std::unique_ptr<Shape>(shape));
		m_material_ptrs.push_back(std::unique_ptr<Material>(material));
	}
	/*
	push(new Light(//light arguments//));
	*/
	inline void push(Light* light) {
		m_light_ptrs.push_back(std::unique_ptr<Light>(light));
	}
	/*
	NOTE: not recommended! (slow)
	push(std::make_unique<Sphere>(//sphere arguments go here//));
	*/
	void push(const std::unique_ptr<Shape>& shape, const std::unique_ptr<Material>& material);
	/*
	NOTE: not recommended! (slow)
	push(std::make_unique<Light>(//light arguments go here//));
	*/
	void push(const std::unique_ptr<Light>& light);

	/*
	enables cool syntax like push<Sphere>( //sphere arguments go here// );
	alternatively you can do: push(std::make_unique<Sphere>(//sphere arguments go here//));
	or: push(new Sphere(//sphere arguments//))
	*/
	template<typename T, typename... Args>
	inline void push(Args&&... args) {
		push(new T(std::forward<Args>(args)...));
	}

	inline const std::vector<std::unique_ptr<Shape>>& get_shapes() const { return m_shape_ptrs; };
	inline const std::vector<std::unique_ptr<Light>>& get_lights() const { return m_light_ptrs; };
	//inline const std::vector<std::unique_ptr<Material>>& get_materials() const { return m_material_ptrs; };


	//SETTTERS

	/*
	set_background(new Background(//agruemnts//));
	*/
	inline void set_background(Background* back) { m_background_ptr.reset(back); }
	inline Background* get_background() const { return m_background_ptr.get(); }
	inline Vec3f get_background_color(const Vec3f& dir) const { return m_background_ptr.get() ? m_background_ptr->get_color(dir) : Vec3f(0, 0, 0); }
};

//class Octree{
//	Octree(const Scene& scene, ...)