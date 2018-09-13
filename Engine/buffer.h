#pragma once

#include "../Dependency/Glew/glew.h"

namespace Engine { namespace Graphics {

		class Buffer
		{
		private:
			GLuint _bufferID;
			GLuint _componentCount;

		public:
			Buffer(GLfloat* data, GLsizei count, GLuint componentCount);
			~Buffer();
			void bind() const;
			void unbind() const;

			inline GLuint getComponentCount() const { return _componentCount; }
		};
} }