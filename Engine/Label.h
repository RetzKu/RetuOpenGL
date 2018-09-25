#pragma once

#include "renderable2d.h"

namespace Engine{namespace Graphics
{
	class Label : public Renderable2D
	{
	public:	
		Label(std::string text, float x, float y, Maths::vec4 color);
		std::string Text;
	};
}}
