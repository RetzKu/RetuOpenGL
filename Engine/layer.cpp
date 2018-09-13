#include "layer.h"
#include "PhysicsObject.h"

namespace Engine { namespace Graphics {

	Layer::Layer(Renderer2D* renderer, Shader* shader, Maths::mat4 projectionMatrix)
	{
		_renderer = renderer;
		_shader = shader;
		_projectionMatrix = projectionMatrix;

		_shader->enable();
		_shader->setUniformMat4("pr_matrix", _projectionMatrix);
		_shader->disable();
	}

	Layer::~Layer()
	{
		delete _shader;
		delete _renderer;

		for(int i = 0; i < _renderables.size(); i++)
		{
			delete _renderables[i];
		}
	}

	void Layer::add(Renderable2D* renderable)
	{
		_renderables.push_back(renderable);
	}

	void Layer::render()
	{
		_shader->enable();
		_renderer->begin();
		for(Renderable2D* renderable : _renderables)
		{
			auto as = dynamic_cast<PhysicsObject*>(renderable);
			if (as != nullptr)
			{
				as->Update();
			}
			renderable->submit(_renderer);
		}

		_renderer->end();
		_renderer->flush();
	}
}}