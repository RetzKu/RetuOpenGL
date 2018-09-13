#pragma once

#include <vector>
#include "../Dependency/Glew/glew.h"
#include "Maths.h"


namespace Engine { namespace Graphics {

		class Renderable2D;

		class Renderer2D
		{
		protected:
			std::vector<Maths::mat4> _transformationStack;
			const Maths::mat4* _transformationBack;
		protected:
			Renderer2D()
			{
				_transformationStack.push_back(Maths::mat4::identity());
				_transformationBack = &_transformationStack.back();
			}
		public:
			// Lisätään kamaa transformation stäkkiin
			// Bool defaulttina false, jos true -> override
			void push(const Maths::mat4& matrix, bool override = false)
			{
				// Ei kerrota matriisia .bäckillä()
				if(override)
				{
					_transformationStack.push_back(matrix);
				}
				// Default: kerrotaan .bäckillä()
				else
				{
					_transformationStack.push_back(_transformationStack.back() * matrix);
				}

				_transformationBack = &_transformationStack.back();

			}
			// Poistetaan viimeinen
			void pop()
			{
				// Jos siellä on muutakin kuin mat4::identity()
				if(_transformationStack.size() > 1)
				{
					_transformationStack.pop_back();
				}

				_transformationBack = &_transformationStack.back();

				// TODO: Tää pitää logata myöhemmin
			}

			virtual void begin(){}
			virtual void end(){}
			virtual void drawString(const std::string& text,const Maths::vec3& position,const Maths::vec4& color) {}
			virtual void submit(const Renderable2D* renderable) = 0;
			virtual void flush() = 0;
		
		};
}}