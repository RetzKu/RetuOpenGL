#pragma once

#include <cstddef>
#include "renderer2d.h"
#include "renderable2d.h"
#include "indexbuffer.h"


namespace ftgl {
	struct texture_atlas_t;
	struct texture_font_t;
}

namespace Engine { namespace Graphics {

#define RENDERER_MAX_SPRITES	60000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6
#define SHADER_VERTEX_INDEX		0
#define SHADER_UV_INDEX			1
#define SHADER_TID_INDEX		2
#define SHADER_COLOR_INDEX		3

	class BatchRenderer2D : public Renderer2D
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
	public:
		BatchRenderer2D();
		~BatchRenderer2D();
		void begin() override;
		void submit(const Renderable2D* renderable);
		void drawString(const std::string& text,const Maths::vec3& position,const Maths::vec4& color) override;
		void end() override;
		void flush();
	private:
		void init();
	};

}}