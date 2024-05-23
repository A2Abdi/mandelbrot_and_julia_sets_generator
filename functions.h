#pragma once

#include <SFML/Graphics.hpp>

#include <cmath>

using namespace sf;

typedef Vector2<float> vec2;


vec2 computeNext( vec2 &z, vec2 &constant) {

	const float zr = (z.x * z.x - z.y * z.y);
	
	const float zi = 2.0f * z.x * z.y;
	
	return vec2{ zr, zi } + constant;
}
  
float compute(vec2 &z) {

	return (z.x * z.x) + (z.y * z.y);
}

float calculate (vec2 z, vec2& constant, int iter, int flag ) {

	int r = 0;

	vec2 z0 = z;

	if (flag) {
		constant = z; z0 = { 0,0 };
	}

	while( r < iter && compute(z0) < 4.0f){

		z0 = computeNext(z0, constant);

		r++;
	}
	return float(r) - log(std::max(1.0f, sqrt(compute(z0))));
}

Color getColor(const int &gradient, float &iter) {

	int r = (float(gradient)/ iter) * 255; 

	if (gradient == iter) return Color::Black;

	else {
		const float t = static_cast<float>(gradient) / iter;

		return Color(static_cast<sf::Uint8>(9 * (1 - t) * t * t * t * 255),
			static_cast<sf::Uint8>(15 * (1 - t) * (1 - t) * t * t * 255),
			static_cast<sf::Uint8>(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255));
	}

	return Color(r,r,r);
}

void drawNext(vec2 render_size, vec2 constant, sf::Image &image, int flag = 0) {

	float iter = 200.f;

	const float scale = 1.0f / float(render_size.y / 2);

	for (int c = 0; c < render_size.y; ++c) {

		for (int r = 0; r < render_size.x; ++r) {

			const float px = float(r - render_size.x/2) * scale;

			const float py = float(c - render_size.y/2) * scale;

			const float gradient = calculate({px, py }, constant, int(iter), flag);

			image.setPixel(r, c, getColor(gradient, iter));
		}
	}
}
