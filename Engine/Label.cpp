#include "Label.h"

namespace Engine {namespace Graphics
{
	Label::Label(std::string text, float x, float y, Maths::vec4 color) : Renderable2D(), Position(_position), Text(text)
	{
		_position = Maths::vec3(x, y, 0);
		_color = color;
		_collider = false;
	}
	
	//void Label::submit(BatchRenderer2D* renderer) const
	//{
	//	renderer->drawString(Text, _position, _color);
	//}
}}