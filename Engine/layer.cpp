#include "layer.h"
#include "PhysicsObject.h"
#include <GLFW\include\glfw3.h>

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
			//TODO: atm t‰m‰ on hyvin vammainen. Tee renderable objectin sis‰lle mat4 joka sis‰lt‰‰ objektin sijainti datan.
			//TODO: Puuttuu rotaatio tieto objectin sis‰lt‰;
			std::cout << glfwGetTime() << std::endl;

			renderable->rotation.x = glfwGetTime() * 15;
			renderable->rotation.y = glfwGetTime() * 15;
			renderable->rotation.z = glfwGetTime() * 15;

			shader->setUniformMat4("ml_matrix", Maths::mat4(Maths::mat4::identity() * 
												Maths::mat4::translation(renderable->getPosition()) * 
												Maths::mat4::scale(Maths::vec3(renderable->getSize().x, renderable->getSize().y,0)))*
												Maths::mat4::rotation(renderable->rotation));

		}
		renderer->end();
		renderer->flush();
		shader->disable();
	}
}}