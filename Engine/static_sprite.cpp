#include "static_sprite.h"

namespace Engine { namespace Graphics {

	StaticSprite::StaticSprite(float x, float y, float width, float height, const Maths::vec4& color, Shader& shader, bool collider)
		: Renderable2D(Maths::vec3(x, y, 0), Maths::vec2(width, height), color, collider), _shader(shader)
		{
			_vertexArray = new VertexArray();

			GLfloat vertices[] =
			{
				0,			0,			0,
				0,		 height,		0,
				width,	 height,		0,
				width,		0,			0
			};

			GLfloat colors[] =
			{
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w
			};

			_vertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
			_vertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);

			// oli ennen glushort
			GLuint indices[] = { 0, 1, 2, 2, 3, 0 };
			_indexBuffer = new IndexBuffer(indices, 6);

		}

		StaticSprite::~StaticSprite()
		{
			delete _vertexArray;
			delete _indexBuffer;
		}

}}