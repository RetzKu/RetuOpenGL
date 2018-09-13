#pragma once
#include "renderable2d.h"
#include <chrono>

namespace Engine {
	namespace Graphics {
		enum rotationdirection
		{
			CLOCKWISE,
			COUNTER_CLOCKWISE,
		};

		class PhysicsObject : public Renderable2D
		{
		public:
			PhysicsObject(float x, float y, float width, float height, const Maths::vec4& color, float density);
			PhysicsObject(float x, float y, float width, float height, Texture* texture, float density);

			void AddForce(Maths::vec2 direction, float force);
			void AddTorque(Maths::vec2 point, float force, rotationdirection direction);
			void AddVelocity(Maths::vec2 direction);

			void Update();
			void AddGravity(float dt);
		private:
			Maths::vec2 gravity = Maths::vec2{ 0,9.81f };

			float defaultDrag;
			Maths::vec2 velocity;
			float density;
			float mass;

			std::chrono::high_resolution_clock::time_point pointA;
		};
	}
}
