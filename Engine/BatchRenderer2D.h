#pragma once
#include <cstddef>
#include "indexbuffer.h"
#include "../Dependency/Glew/glew.h"
#include "Maths.h"
#include <vector>
#include "renderable2d.h"
#include "Shader.h"


namespace ftgl {
	struct texture_atlas_t;
	struct texture_font_t;
}

namespace Engine { namespace Graphics {

		// Kama mitä nakataan shadereille
		struct VertexData
		{
			// Tekstuurin positio
			Maths::vec3 vertex;
			// Tekstuuri koordinaatit
			Maths::vec2 uv;
			// Tekstuuri ID
			float tid;
			// Tekstuurin väri
			unsigned int color;
		};

#define RENDERER_MAX_SPRITES	60000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6
#define SHADER_VERTEX_INDEX		0
#define SHADER_UV_INDEX			1
#define SHADER_TID_INDEX		2
#define SHADER_COLOR_INDEX		3

	class BatchRenderer2D
	{
	private:
		GLuint _VAO;
		GLuint _VBO;
		IndexBuffer* _IBO;
		GLsizei _indexCount;
		VertexData* _buffer;
		VertexData* _bufferStart;

		std::vector<GLuint> _textureSlots;
		ftgl::texture_atlas_t* m_FTAtlas;
		ftgl::texture_font_t* m_FTFont;

		std::vector<Maths::mat4> transformationStack;
		const Maths::mat4* transformationBack;
		

	public:
		BatchRenderer2D();
		~BatchRenderer2D();
		void begin();
		void submit(Renderable2D* renderable);
		void drawString(std::string& text,Maths::vec3& position,Maths::vec4& color);
		void end();
		void flush();

		void PushTransform(Maths::mat4& matrix, bool overwrite = false);
		void PopTransform();
	private:
		void init();
	};

}}