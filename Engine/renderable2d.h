#pragma once

#include "Maths.h"
#include <vector>
#include "texture.h"

namespace Engine { namespace Graphics
	{

		class Renderable2D
		{
		public:
			Maths::vec3 position;
			Maths::vec2 size;
			Maths::vec4 color;
			Maths::vec3 rotation;
			std::vector<Maths::vec2> _UV;
			Texture* texture;
			bool _collider;
			float _distancemoved = 0;
			Maths::vec2 startsize;
			Maths::vec3 startposition;

		protected:
			Renderable2D() : texture(nullptr) { setUVDefaults(); }
		public:
			Renderable2D(Maths::vec3 position, Maths::vec2 size, Maths::vec4 color, bool collider)
				: position(position), size(size), color(color), texture(nullptr), _collider(collider)
			{
				startsize = size; startposition = position; setUVDefaults();
				rotation = Maths::vec3(0, 0, 0);
			}

			virtual ~Renderable2D(){ }

			const float AddDistance(float AddedDistance) { _distancemoved += AddedDistance; return _distancemoved; }
			Maths::vec3 getPosition() { return position; }
			void AddMovement(Maths::vec3 Towards);
			void UpdateSize();
			Maths::vec2 getSize() { return size; }
			Maths::vec4 getColor() { return color; }
			std::vector<Maths::vec2> getUV() { return _UV; }
			bool IsCollider() { return _collider; }

			GLuint getTID() { return texture ? texture->getID() : 0; }

			bool isText = false;
		private:
			void setUVDefaults()
			{
				_UV.push_back(Maths::vec2(0, 0));
				_UV.push_back(Maths::vec2(0, 1));
				_UV.push_back(Maths::vec2(1, 1));
				_UV.push_back(Maths::vec2(1, 0));
			}
		};
}}