#pragma once

#include "renderable2d.h"
#include "renderer2d.h"


namespace Engine {
	namespace Graphics {

		class Layer
		{
		protected:
			Renderer2D* _renderer;
			std::vector<Renderable2D*> _renderables;
			Shader* _shader;
			Maths::mat4 _projectionMatrix;
		protected:
			Layer(Renderer2D* renderer, Shader* shader, Maths::mat4 projectionMatrix);
		public:
			virtual ~Layer();
			virtual void add(Renderable2D* renderable);
			virtual void render();

		};
}} 