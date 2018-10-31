#include "Label.h"

namespace Engine {namespace Graphics
{
	Label::Label(std::string text, float x, float y, Maths::vec4 color) : Renderable2D(), Text(text)
	{
		this->position = Maths::vec3(x, y, 0);
		this->color = color;
		_collider = false;
		isText = true;
	}
}}