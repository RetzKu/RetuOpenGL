#pragma once

#include <vector>
#include "../Dependency/Glew/glew.h"
#include "buffer.h"

namespace Engine { namespace Graphics {

	class VertexArray
	{
	private:
		GLuint _arrayID;
		std::vector<Buffer*> _buffers;
	public:
		VertexArray();
		~VertexArray();

		void addBuffer(Buffer* buffer, GLuint index);
		void bind() const;
		void unbind() const;
	};


}}