#pragma once
#include <iostream>
namespace Engine {
	namespace Maths {

		struct vec3 
		{
			float x, y, z;

			vec3();
			vec3(const float& x, const float& y, const float& z);

			//metodit
			vec3& add     (const vec3& other);
			vec3& subtract(const vec3& other);
			vec3& divide  (const vec3& other);
			vec3& multiply(const vec3& other);
			//operaattorien ylilataus
			friend vec3 operator+(vec3 left, const vec3& right);
			friend vec3 operator-(vec3 left, const vec3& right);
			friend vec3 operator*(vec3 left, const vec3& right);
			friend vec3 operator/(vec3 left, const vec3& right);
			// vertaa operaattoreita, compare.
			bool operator==(const vec3& other);
			bool operator!=(const vec3& other);

			//uudet operaattorit ex. a += b, 
			vec3& operator+=(const vec3& other);
			vec3& operator-=(const vec3& other);
			vec3& operator*=(const vec3& other);
			vec3& operator/=(const vec3& other);

			friend std::ostream& operator<<(std::ostream& stream, const vec3& vector);
		};
	}
}