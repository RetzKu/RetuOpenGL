#pragma once

#include "Maths.h"
#include <vector>
#include "texture.h"

namespace Engine { namespace Graphics
	{

		class Renderable2D
		{
		protected:
			Maths::vec3 _position;
			Maths::vec2 _size;
			Maths::vec4 _color;
			std::vector<Maths::vec2> _UV;
			Texture* _texture;
			bool _collider;
			float _distancemoved = 0;
			Maths::vec2 startsize;
			Maths::vec3 startposition;

		protected:
			Renderable2D() : _texture(nullptr) { setUVDefaults(); }
		public:
			Renderable2D(Maths::vec3 position, Maths::vec2 size, Maths::vec4 color, bool collider)
				: _position(position), _size(size), _color(color),_texture(nullptr), _collider(collider)
			{
				startsize = size; startposition = position; setUVDefaults();
			}

			virtual ~Renderable2D(){ }

			const float AddDistance(float AddedDistance) { _distancemoved += AddedDistance; return _distancemoved; }
			Maths::vec3 getPosition() { return _position; }
			void AddMovement(Maths::vec3 Towards);
			void UpdateSize();
			Maths::vec2 getSize() { return _size; }
			Maths::vec4 getColor() { return _color; }
			std::vector<Maths::vec2> getUV() { return _UV; }
			bool IsCollider() { return _collider; }

			GLuint getTID() { return _texture ? _texture->getID() : 0; }

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