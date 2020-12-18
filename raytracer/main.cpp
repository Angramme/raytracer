#include <iostream>
#include <fstream>

#include "bitmap.hpp"

#include "Vector.h"
#include "Ray.h"

#include "Renderer.h"
#include "Scene.h"

#include "Sphere.h"
#include "Disc.h"
#include "Square.h"

#include "PhongMat.h"
#include "MirrorMat.h"

#include "Camera.h"
#include "Light.h"

#include "GradientBackground.h"



int main() {
	Renderer renderer;

	//part of Renderer.config dictionary
		const int PPU = 1; // pixels per unit
		const int WIDTH = 500 * PPU;
		const int HEIGHT = 500 * PPU;

		const bool ADVANCED_PERCIEVED_LUMINANCE = false;
		const float GAMMA = 1;  // 1 =no correction
		

	
	Scene scene;
	scene.push<Light>(Vec3f(0, 0, 0), Vec3f(0.2, 0.2, 1), 200000);
	scene.push<Light>(Vec3f(500, 250, 0), Vec3f(1, 0.2, 0.2), 200000);
	
	scene.push(new Sphere(Vec3f(250, 250, 250), 150), new PhongMat({1,1,1}, 128, 0.2));
	scene.push(new Sphere(Vec3f(250, 480, 250), 70), new PhongMat({1,1,0.6}, 4, 0.2));
	scene.push(new Sphere(Vec3f(300, 300, 50), 50), new PhongMat({ 0.7, 0.7, 1 }, 2, 0.5));
	scene.push(new Disc(Vec3f(250, 0, 300), Vec3f::normalize({ 0,1,-1 }), 150), new MirrorMat());
	
	scene.set_background(new GradientBackground({ 0.5,0.5,0.8 }, { 0.8,0.8,0.8 }));

	renderer.set_scene(&scene);
	renderer.set_depth_limit(10);


	Camera cam(WIDTH, HEIGHT, 3.14155 / 3); // PPU in constructor to reconsider: meaby pass it with get_ray
	cam.set_PPU(PPU);

	std::vector<Vec3f> framebuffer;
	framebuffer.resize(WIDTH*HEIGHT);
	
	//INSIDE Renderer.render_scene(const Scene& scene, const Camera& cam, bitmap_image& image)

	float HDR_logL_sum = 0;
	float max_luminance = 0;

	
	int x, y;
	for (int i = 0; i < HEIGHT*WIDTH; i++) {
		x = i % WIDTH;
		y = i / WIDTH;

		const Ray ray = cam.get_ray(x, y);

		renderer.reset_depth_cap();
		Vec3f color = renderer.cast_ray(ray);

		framebuffer[i] = color;


		{//HDR LUMINANCE METERING
			//luminance calculation
			//const float L = color.r + color.g + color.b; WRONG!
			//according to https://stackoverflow.com/questions/596216/formula-to-determine-brightness-of-rgb-color
			/*
			const float L = ( ADVANCED_PERCIEVED_LUMINANCE ?
				std::sqrt(0.299f* color.r*color.r + 0.587f* color.g*color.g + 0.114f*color.b*color.b) //advanced but slow
				: (color.r * 0.299) + (color.g * 0.587) + (color.b * 0.114) //simple
			) *1; 
			*/

			const float delta = 1;
			//const float lum = color.dot(Vec3f(0.2126f, 0.7152f, 0.0722f));
			const float lum = ADVANCED_PERCIEVED_LUMINANCE ?
				std::sqrt(0.299f* color.r*color.r + 0.587f* color.g*color.g + 0.114f*color.b*color.b) //advanced but slow
				: (color.r * 0.299) + (color.g * 0.587) + (color.b * 0.114); //simple
			const float log_lum = std::logf(delta + lum);

			const float weight = 1; // meaby use an image for weights
			//HDR_logL_sum += std::logf(L) * weight;

			HDR_logL_sum += log_lum * weight;
			max_luminance = std::max(max_luminance, lum);
		}
	}


	max_luminance *= 0.7; //let it clip a bit
	const float HDR_logL_avg = HDR_logL_sum / (WIDTH * HEIGHT);
	//const float HDR_L_avg = std::powf(2, HDR_logL_avg);
	//const float K = 21.5f; // K is a light meter calibration constant //default: 12.5
	//const float HDR_exposure = std::log2f(HDR_L_avg * 100.0f / K);

	//std::cout << HDR_L_avg << std::endl;
	//std::cout << HDR_exposure << std::endl;


	bitmap_image image(WIDTH, HEIGHT);

	for (int i = 0; i < HEIGHT*WIDTH; i++) {
		x = i % WIDTH;
		y = i / WIDTH;

		Vec3f color = framebuffer[i];

		//HDR   look at stackexchange game developement article
		/*
		color.x = 1 - std::expf(-color.x * HDR_exposure);
		color.y = 1 - std::expf(-color.y * HDR_exposure);
		color.z = 1 - std::expf(-color.z * HDR_exposure);
		*/

		{ //HDR
			const float scale = 0.75f; // 0.25f default
			const float lumwhite2 = max_luminance * max_luminance;

			const float lum = color.dot(Vec3f(0.2126f, 0.7152f, 0.0722f));
			const float L = (scale / HDR_logL_avg) * lum;
			float Ld = (L * (1.0 + L / lumwhite2)) / (1.0 + L);

			color = (color / lum) * Ld;
		}

		//GAMMA CORRECTION
		if (GAMMA != 1) {
			const float inv_gamma = 1 / GAMMA;
			color.x = std::powf(color.x, inv_gamma);
			color.y = std::powf(color.y, inv_gamma);
			color.z = std::powf(color.z, inv_gamma);
		}

		//CLAMP from 0 to 1
		{
			color.x = color.x > 1 ? 1 : color.x;
			color.y = color.y > 1 ? 1 : color.y;
			color.z = color.z > 1 ? 1 : color.z;
		}

		{ //OUTPUT
			rgb_t pixel;

			pixel.red = color.x * 255;
			pixel.green = color.y * 255;
			pixel.blue = color.z * 255;

			image.set_pixel(x, y, pixel);
		}
	}

	image.save_image("output.bmp");

	return 0;
}