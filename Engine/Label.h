#pragma once

#include "renderable2d.h"
#include "BatchRenderer2D.h"

namespace Engine{namespace Graphics
{
	class Label : public Renderable2D
	{
	public:	
		Label(std::string text, float x, float y, Maths::vec4 color);
		//TODO: Korjaa Label
		//void submit(BatchRenderer2D* renderer)const override;

		std::string Text;
		float x, y;
		Maths::vec3& Position;
	};
}}
