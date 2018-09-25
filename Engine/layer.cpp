#include "layer.h"
#include "PhysicsObject.h"

namespace Engine { namespace Graphics {

	Layer::Layer(BatchRenderer2D* renderer, Shader* shader, Maths::mat4 projectionMatrix)
	{
		renderer = renderer;
		shader = shader;
		projectionMatrix = projectionMatrix;

		shader->enable();
		shader->setUniformMat4("pr_matrix", projectionMatrix);
		shader->disable();
	}

	Layer::Layer(Shader* shader)
	{
		renderer = new BatchRenderer2D();
		this->shader = shader;
		projectionMatrix = Maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f);

		shader->enable();
		shader->setUniformMat4("pr_matrix", projectionMatrix);
		shader->disable();
	}

	Layer::~Layer()
	{
		//delete shader;
		delete renderer;

		for(int i = 0; i < renderables.size(); i++)
		{
			delete renderables[i];
		}
	}

	void Layer::add(Renderable2D* renderable)
	{
		renderables.push_back(renderable);
	}

	void Layer::render()
	{
		shader->enable();
		renderer->begin();
		for(Renderable2D* renderable : renderables)
		{
			if (renderable->isText) 
			{ 
				Label* test = static_cast<Label*>(renderable);
				renderer->drawString(test); 
			}
			else 
			{
				renderer->submit(renderable);
			}
		}
		renderer->end();
		renderer->flush();
	}
}}