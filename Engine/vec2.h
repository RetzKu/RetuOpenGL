#pragma once
#include <iostream>
namespace Engine {
	namespace Maths {

		struct vec2 
		{
			float x, y;

			vec2();
			vec2(const float& x, const float& y);

			//metodit
			vec2& add     (const vec2& other);
			vec2& subtract(const vec2& other);
			vec2& multiply(const vec2& other);
			vec2& divide  (const vec2& other);
			//operaattorien ylilataus
			friend vec2& operator+(vec2 left, const vec2& right);
			friend vec2& operator-(vec2 left, const vec2& right);
			friend vec2& operator*(vec2 left, const vec2& right);
			friend vec2& operator/(vec2 left, const vec2& right);
			// vertaa operaattoreita, compare.
			bool operator==(const vec2& other);
			bool operator!=(const vec2& other);

			//uudet operaattorit ex. a += b, 
			vec2& operator+=(const vec2& other);
			vec2& operator-=(const vec2& other);
			vec2& operator*=(const vec2& other);
			vec2& operator/=(const vec2& other);

			friend std::ostream& operator<<(std::ostream& stream, const vec2& vector);
		};
	}
}