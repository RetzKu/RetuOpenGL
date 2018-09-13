#pragma once

#include "renderable2d.h"

namespace Engine{namespace Graphics
{
	class Label : public Renderable2D
	{
	public:	
		Label(std::string text, float x, float y, Maths::vec4 color);
		void submit(Renderer2D* renderer)const override;

		std::string Text;
		float x, y;
		Maths::vec3& Position;
	};
}}
