#include "sprite.h"



namespace Engine { namespace Graphics {

		Sprite::Sprite(float x, float y, float width, float height, const Maths::vec4& color, bool collider)
			: Renderable2D(Maths::vec3(x, y, 0), Maths::vec2(width, height), color, collider)
		{		
			
		}

		Sprite::Sprite(float x, float y, float width, float height, Texture* texture, bool collider)
			: Renderable2D(Maths::vec3(x, y, 0), Maths::vec2(width, height), Maths::vec4(1, 1, 1, 1), collider)
		{
			this->texture = texture;
		}

}}