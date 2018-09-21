#pragma once

#include "BatchRenderer2D.h"


namespace Engine {
	namespace Graphics {

		class Layer
		{
		public:
			Layer(Shader* shader);
			~Layer();
			virtual void add(Renderable2D* renderable);
			virtual void render();

		private:
			BatchRenderer2D* renderer;
			std::vector<Renderable2D*> renderables;
			Shader* shader;
			Maths::mat4 projectionMatrix;
			Layer(BatchRenderer2D* renderer, Shader* shader, Maths::mat4 projectionMatrix);
		};
}} 