#include <cassert>
#include "BatchRenderer2D.h"
#include "../Dependency/FreeType/freetype-gl/freetype-gl.h"

// T‰ss‰ filussa oleviin kommentteihin ‰lk‰‰ kajotko voi k‰ytt‰‰ myˆhemmin hyv‰ks et kattoo jos on PC nii k‰ytt‰‰ sit VAO:ta

namespace Engine { namespace Graphics {

	BatchRenderer2D::BatchRenderer2D()
	{
		init();
	}

	BatchRenderer2D::~BatchRenderer2D()
	{
		delete _IBO;
		glDeleteBuffers(1, &_VBO);

		delete _buffer;
		_buffer = _bufferStart = nullptr;
	}

	void BatchRenderer2D::init()
	{
		//glGenVertexArrays(1, &_VAO);
		glGenBuffers(1, &_VBO);
		//glBindVertexArray(_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, _VBO);
		glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
		//glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
		//glEnableVertexAttribArray(SHADER_COLOR_INDEX);
		//glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*) 0);
		//glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// oli GLushort, mutta ku pit‰‰ saada paljo neliˆit‰ ruutuun nii v‰liaikasesti int

		GLuint* indices = new GLuint[RENDERER_INDICES_SIZE];

		int offset = 0;
		for(int i = 0; i < RENDERER_INDICES_SIZE;  i+= 6)
		{
			indices[  i  ] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);
		//glBindVertexArray(0);

		_bufferStart = _buffer = new VertexData[RENDERER_MAX_SPRITES * 4];

		m_FTAtlas = ftgl::texture_atlas_new(512, 512, 2);
		m_FTFont = ftgl::texture_font_new_from_file(m_FTAtlas, 32, "arial.ttf");

		this->transformationStack.push_back(Maths::mat4::identity());
		this->transformationBack = &transformationStack.back();
	}

	void BatchRenderer2D::begin()
	{
		glBindBuffer(GL_ARRAY_BUFFER, _VBO);
		//_buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		_buffer = _bufferStart;
	}

	void BatchRenderer2D::submit(Renderable2D* renderable)
	{
		Maths::vec3 position = renderable->getPosition();
		Maths::vec2 size = renderable->getSize();
		Maths::vec4 color = renderable->getColor();
		std::vector<Maths::vec2> uv = renderable->getUV();
		GLuint tid = renderable->getTID();

		unsigned int c = 0;

		// ts = Texture slot
		float ts = 0.0f;
		// tid = Texture ID
		if(tid > 0)
		{
			// Defaulttina ei lˆytynyt
			bool found = false;
			// K‰yd‰‰n _textureSlotsit l‰pi jos lˆytyisi oikea tekstuuri
			for (int i = 0; i < _textureSlots.size(); i++)
			{
				// Jos tekstuuri lˆytyy
				if(_textureSlots[i] == tid)
				{
					// Texture slot talteen
					ts = (float)(i + 1);
					// Lˆydetty
					found = true;
					break;
				}
			}

			// Jos ei lˆytynyt, pit‰‰ ladata tekstuuri tekstuurislotteihin
			if(!found)
			{
				// Jos meill‰ loppuu tekstuurislotit kesken
				if(_textureSlots.size() >= 32)
				{
					// Piirret‰‰n kaikki mit‰ pystyttiin, nyt ei en‰‰ pystyt‰ koska
					// puuttuu tekstuuri, joten piirret‰‰n kaikki mit‰ oli bufferissa
					end();
					// Flush updatee texture slotit
					flush();
					begin();
				}

				// Laitetaan puuttuva tekstuuri viimesimp‰‰n slottiin
				_textureSlots.push_back(tid);
				// Ja p‰ivitet‰‰n ts uuteen slotti m‰‰r‰‰n
				ts = (float)_textureSlots.size();
			}
		}

		int r = color.x * 255.0f;
		int g = color.y * 255.0f;
		int b = color.z * 255.0f;
		int a = color.w * 255.0f;			

		c = a << 24 | b << 16 | g << 8 | r;

		_buffer->vertex = *transformationBack * position;
		_buffer->uv = uv[0];
		_buffer->tid = ts;
		_buffer->color = c;
		_buffer++;	

		_buffer->vertex = *transformationBack * Maths::vec3(position.x, position.y + size.y, position.z);
		_buffer->uv = uv[1];
		_buffer->tid = ts;
		_buffer->color = c;
		_buffer++;

		_buffer->vertex = *transformationBack * Maths::vec3(position.x + size.x, position.y + size.y, position.z);
		_buffer->uv = uv[2];
		_buffer->tid = ts;
		_buffer->color = c;
		_buffer++;

		_buffer->vertex = *transformationBack * Maths::vec3(position.x + size.x, position.y, position.z);
		_buffer->uv = uv[3];
		_buffer->tid = ts;
		_buffer->color = c;
		_buffer++;

		_indexCount += 6;
	}

	//void BatchRenderer2D::drawString(std::string& text,Maths::vec3& position,Maths::vec4& color)
	void BatchRenderer2D::drawString(Label* renderable)
	{
		using namespace ftgl;
		Maths::vec4 color = renderable->getColor();
		Maths::vec3 position = renderable->getPosition();
		std::string text = renderable->Text;

		int r = color.x * 255.0f;
		int g = color.y * 255.0f;
		int b = color.z * 255.0f;
		int a = color.w * 255.0f;

		unsigned int unsintcolor = a << 24 | b << 16 | g << 8 | r;

		float ts = 0.0f;
		bool found = false;
		for (int i = 0; i < _textureSlots.size(); i++)
		{
			if (_textureSlots[i] == m_FTAtlas->id)
			{
				ts = (float)(i + 1);
				found = true;
				break;
			}
		}
		if (!found)
		{
			if (_textureSlots.size() >= 32)
			{
				end();
				flush();
				begin();
			}
			_textureSlots.push_back(m_FTAtlas->id);
			ts = (float)(_textureSlots.size());
		}

		float x = position.x;
		float scaley = 540.0f / 18.0f;
		float scalex = 960.0f / 32.0f;

		for (int i = 0; i < text.length(); i++)
		{
			char c = text.at(i);
			texture_glyph_t* glyph = texture_font_get_glyph(m_FTFont, c);
			if (glyph != NULL)
			{

				if (i < 0)
				{
					float kerning = ftgl::texture_glyph_get_kerning(glyph, text[i - 1]);
					x += kerning / scalex;
				}

				float x0 = x + glyph->offset_x / scalex;
				float y0 = position.y + glyph->offset_y / scaley;
				float x1 = x0 + glyph->width / scalex;
				float y1 = y0 - glyph->height / scaley;

				float u0 = glyph->s0;
				float v0 = glyph->t0;
				float u1 = glyph->s1;
				float v1 = glyph->t1;

				_buffer->vertex = *transformationBack* Maths::vec3(x0, y0, 0);
				_buffer->uv = Maths::vec2(u0, v0);
				_buffer->tid = ts;
				_buffer->color = unsintcolor;
				_buffer++;
				
				_buffer->vertex = *transformationBack* Maths::vec3(x0, y1, 0);
				_buffer->uv = Maths::vec2(u0, v1);
				_buffer->tid = ts;
				_buffer->color = unsintcolor;;
				_buffer++;

				_buffer->vertex = *transformationBack* Maths::vec3(x1, y1, 0);
				_buffer->uv = Maths::vec2(u1, v1);
				_buffer->tid = ts;
				_buffer->color = unsintcolor;
				_buffer++;

				_buffer->vertex = *transformationBack* Maths::vec3(x1, y0, 0);
				_buffer->uv = Maths::vec2(u1, v0);
				_buffer->tid = ts;
				_buffer->color = unsintcolor;
				_buffer++;
				_indexCount += 6;

				x += glyph->advance_x / scalex;

			}
		}

	}
	
	void BatchRenderer2D::end()
	{
		int currentSize = (_buffer - _bufferStart) * RENDERER_SPRITE_SIZE;

		assert(currentSize < RENDERER_MAX_SPRITES * RENDERER_SPRITE_SIZE); // Note(Eetu): ei voida rendata noin montaa nosta Renderer max sizea
		glBufferSubData(GL_ARRAY_BUFFER, 0, currentSize, _bufferStart);
		// std::cout << _buffer - _bufferStart << std::endl;

		//glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void BatchRenderer2D::flush()
	{
		// Bindataan tekstuurit
		for(int i = 0; i < _textureSlots.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, _textureSlots[i]);
		}

		//glBindVertexArray(_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, _VBO);

		glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
		glEnableVertexAttribArray(SHADER_UV_INDEX);
		glEnableVertexAttribArray(SHADER_TID_INDEX);
		glEnableVertexAttribArray(SHADER_COLOR_INDEX);

		glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
		glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::uv)));
		glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::tid)));
		glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		_IBO->bind();
		// oli GL_UNSIGNED_SHORT, mutta ku pit‰‰ saada paljo neliˆit‰ ruutuun nii v‰liaikasesti int
		glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_INT, NULL);

		_IBO->unbind();

		//glBindVertexArray(0);

		_indexCount = 0;
	}
	
	void BatchRenderer2D::PushTransform(Maths::mat4& matrix, bool overwrite)
	{
		if (overwrite) { transformationStack.push_back(matrix); }
		else { transformationStack.push_back(transformationStack.back() * matrix); }
		transformationBack = &transformationStack.back();
	}
	
	void BatchRenderer2D::PopTransform()
	{
		if (transformationStack.size() > 1)
		{
			transformationStack.pop_back();
		}
		transformationBack = &transformationStack.back();
	}
}}