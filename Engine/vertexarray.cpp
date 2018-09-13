#include "vertexarray.h"


namespace Engine { namespace Graphics {
	
	VertexArray::VertexArray()
	{
		// TODO vaihda funktio 3.0 -> 2.0 tukevaksi
		glGenVertexArrays(1, &_arrayID);
	}
	
	VertexArray::~VertexArray()
	{
		for (int x = 0; x < _buffers.size(); x++)
		{
			delete _buffers[x];
		}
		// TODO vaihda funktio 3.0 -> 2.0 tukevaksi
		glDeleteVertexArrays(1, &_arrayID);
	}
	
	void VertexArray::addBuffer(Buffer* buffer, GLuint index)
	{
		bind();
		buffer->bind();

		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);

		buffer->unbind();
		unbind();
	}

	void VertexArray::bind() const
	{
		// TODO vaihda funktio 3.0 -> 2.0 tukevaksi
		glBindVertexArray(_arrayID);
	}

	void VertexArray::unbind() const
	{
		// TODO vaihda funktio 3.0 -> 2.0 tukevaksi
		glBindVertexArray(0);
	}

}}