#pragma once
#include <iostream>
namespace Engine {
	namespace Maths {

		struct vec4
		{
			float x, y, z, w;

			vec4() = default;
			vec4(const float& x, const float& y, const float& z, const float& w);

			//metodit
			vec4& add     (const vec4& other);
			vec4& subtract(const vec4& other);
			vec4& divide  (const vec4& other);
			vec4& multiply(const vec4& other);
			//operaattorien ylilataus
			friend vec4 operator+(vec4 left, const vec4& right);
			friend vec4 operator-(vec4 left, const vec4& right);
			friend vec4 operator*(vec4 left, const vec4& right);
			friend vec4 operator/(vec4 left, const vec4& right);
			// vertaa operaattoreita, compare.
			bool operator==(const vec4& other);
			bool operator!=(const vec4& other);

			//uudet operaattorit ex. a += b, 
			vec4& operator+=(const vec4& other);
			vec4& operator-=(const vec4& other);
			vec4& operator*=(const vec4& other);
			vec4& operator/=(const vec4& other);

			friend std::ostream& operator<<(std::ostream& stream, const vec4& vector);
		};
	}
}