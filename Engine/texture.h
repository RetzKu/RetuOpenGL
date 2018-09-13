#pragma once
#include <FreeImage\include\FreeImage.h>
#include <string>
#include "../Dependency/Glew/glew.h"
#include "imageload.h"

namespace Engine { namespace Graphics {

	class Texture
	{
	private:
		std::string _filename;
		GLuint _TID;
		GLsizei _width;
		GLsizei _height;
	public:
		Texture(const std::string& filename);
		~Texture();
		void bind() const;
		void unbind() const;

		inline const unsigned int getID() const { return _TID; }
		inline const unsigned int getWidth() const { return _width; }
		inline const unsigned int getHeight() const { return _height; }
	private:
		GLuint load();

	};

}}