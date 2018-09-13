#include "simple2drenderer.h"
#include "renderable2d.h"

namespace Engine { namespace Graphics {


		void Simple2DRenderer::submit(const Renderable2D* renderable)
		{
			_renderQueue.push_back((StaticSprite*)renderable);
		}

		void Simple2DRenderer::flush()
		{
			while (!_renderQueue.empty())
			{
				const StaticSprite* sprite = _renderQueue.front();
				sprite->getVAO()->bind();
				sprite->getIBO()->bind();

				sprite->getShader().setUniformMat4("ml_matrix", Maths::mat4::translation(sprite->getPosition()));
				glDrawElements(GL_TRIANGLES, sprite->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

				sprite->getIBO()->unbind();
				sprite->getVAO()->unbind();

				_renderQueue.pop_front();
			}
		}
		
}}