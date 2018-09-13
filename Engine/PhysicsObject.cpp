#include "PhysicsObject.h"



namespace Engine {
	namespace Graphics {

		PhysicsObject::PhysicsObject(float x, float y, float width, float height, const Maths::vec4& color, float density)
			: Renderable2D(Maths::vec3(x, y, 0), Maths::vec2(width, height), color, true)
		{
			pointA = std::chrono::high_resolution_clock::now();
			this->mass = density * width*height;
			this->defaultDrag = 10;
		}

		PhysicsObject::PhysicsObject(float x, float y, float width, float height, Texture* texture, float density)
			: Renderable2D(Maths::vec3(x, y, 0), Maths::vec2(width, height), Maths::vec4(1, 1, 1, 1), true)
		{
			pointA = std::chrono::high_resolution_clock::now();
			this->mass = density * width*height;
			_texture = texture;
			this->defaultDrag = 10;
		}

		void PhysicsObject::AddForce(Maths::vec2 direction, float force)
		{
			velocity.add(Maths::vec2{direction.x* (force), direction.y * (force)});
		}

		void PhysicsObject::AddTorque(Maths::vec2 point, float force, rotationdirection direction)
		{

		}

		void PhysicsObject::Update()
		{
			auto s = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - pointA);
			pointA = std::chrono::high_resolution_clock::now();	
			float partialsecond = s.count();
			partialsecond = partialsecond / 1000000;
			AddGravity(partialsecond);
			this->_position.x += velocity.x*partialsecond;
			this->_position.y += velocity.y*partialsecond;
			std::cout << "X: " << this->_position.x << " Y: " << this->_position.y << std::endl;
			//std::cout << "X: " << this->velocity.x << " Y: " << this->velocity.y << std::endl;
		}

		void PhysicsObject::AddVelocity(Maths::vec2 direction)
		{

		}

		void PhysicsObject::AddGravity(float dt)
		{
			velocity.y += (-9.81 *dt);
		}
	}
}