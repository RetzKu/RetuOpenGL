#pragma once

#include "fileutils.h"
#include "../Dependency/Glew/glew.h"
#include <vector>
#include <iostream>
#include "Maths.h"

namespace Engine { namespace Graphics {

	class Shader
	{
		// Variables
	public:
	private:
		GLuint _shaderID;
		const char* _vertPath;
		const char* _fragPath;
		// Functions
	public:
		Shader(const char* vertPath, const char* fragPath);
		~Shader();

		// Uniformit on tapa jutella vertex & fragment shaderilla niiden ulkopuolelta
		// Näillä syötetään kamaa siis shadereille

		// Linkkauksen jälkeen voidaan ettiä uniformin sijainti
		// glGetUniformLocation komennolla ja muokata sitä
		// glUniform komennolla
		void setUniformMat1f(const GLchar* name, float value);
		void setUniformMat1fv(const GLchar* name, float* value, GLsizei count);
		void setUniformMat1iv(const GLchar* name, int* value, GLsizei count);
		void setUniformMat2f(const GLchar* name, const Maths::vec2& vector);
		void setUniformMat3f(const GLchar* name, const Maths::vec3& vector);
		void setUniformMat4f(const GLchar* name, const Maths::vec4& vector);
		void setUniformMat1i(const GLchar* name, int value);
		void setUniformMat4(const GLchar* name, const Maths::mat4& matrix);

		void enable() const;
		void disable() const;
	private:
		GLuint load();
		GLint getUniformLocation(const GLchar* name);
	};	
}}