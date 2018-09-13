#include "vec2.h"
namespace Engine {
	namespace Maths {
		//2 ulotteinen vektori xy
		//default konstruktori
		vec2::vec2()
		{
			x = 0.0f;
			y = 0.0f;
		}
		//konstruktori
		vec2::vec2(const float& x, const float& y)
		{
			this->x = x;
			this->y = y;
		}
		//matikka hommia vektoriin + - * /
		vec2& vec2::add(const vec2& other)
		{
			x += other.x;
			y += other.y;

			return *this;
		}

		vec2& vec2::subtract(const vec2& other)
		{
			x -= other.x;
			y -= other.y;

			return *this;
		}

		vec2& vec2::multiply(const vec2& other)
		{
			x *= other.x;
			y *= other.y;

			return *this;
		}

		vec2& vec2::divide(const vec2& other)
		{
			x /= other.x;
			y /= other.y;

			return *this;
		}
		//operaattorien overloadia
		vec2& operator+(vec2 left, const vec2& right)
		{
			return left.add(right);
		}
		vec2& operator-(vec2 left, const vec2& right)
		{
			return left.subtract(right);
		}
		vec2& operator*(vec2 left, const vec2& right)
		{
			return left.multiply(right);
		}
		vec2& operator/(vec2 left, const vec2& right)
		{
			return left.divide(right);
		}
		// tupla operaattorien overloadia
		vec2& vec2::operator+=(const vec2& other)
		{
			return add(other);
		}
		vec2& vec2::operator-=(const vec2& other)
		{
			return subtract(other);
		}
		vec2& vec2::operator*=(const vec2& other)
		{
			return multiply(other);
		}
		vec2& vec2::operator/=(const vec2& other)
		{
			return divide(other);
		}
		//compare operaattorit -> onko kaksi vektoria samanlaisia tulostaa 1 / 0
		bool vec2::operator==(const vec2& other)
		{
			return x == other.x && y == other.y;
		}
		//compare operaattorit -> onko kaksi vektoria erilaisia tulostaa 0 / 1
		bool vec2::operator!=(const vec2& other)
		{
			return !(*this == other);
		}
		// << operaattorin overload iostreamilta
		std::ostream& operator<<(std::ostream& stream, const vec2& vector)
		{
			stream << "vec2: (" << vector.x << ", " << vector.y << ")";
			return stream;
		}

	}
}