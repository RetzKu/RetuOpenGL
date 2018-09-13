#include "Shader.h"

namespace Engine { namespace Graphics {

	Shader::Shader(const char* vertPath, const char* fragPath)
	{
		_vertPath = vertPath;
		_fragPath = fragPath;
		_shaderID = load();
	}

	Shader::~Shader()
	{
		glDeleteProgram(_shaderID);
	}

	GLuint Shader::load()
	{
		GLuint program = glCreateProgram();
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

		std::string vertSourceString = FileUtils::read_file(_vertPath);
		std::string fragSourceString = FileUtils::read_file(_fragPath);

		const char* vertSource = vertSourceString.c_str();
		const char* fragSource = fragSourceString.c_str();

		glShaderSource(vertex, 1, &vertSource, NULL);
		glCompileShader(vertex);

		GLint result;
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
		if(result == GL_FALSE)
		{
			GLint lenght;
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &lenght);
			std::vector<char> error(lenght);
			glGetShaderInfoLog(vertex, lenght, &lenght, &error[0]);
			std::cout << "Failed to compile vertex shader!" << std::endl << &error[0] << std::endl;
			glDeleteShader(vertex);
			return 0;
		}

		glShaderSource(fragment, 1, &fragSource, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint lenght;
			glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &lenght);
			std::vector<char> error(lenght);
			glGetShaderInfoLog(fragment, lenght, &lenght, &error[0]);
			std::cout << "Failed to compile fragment shader!" << std::endl << &error[0] << std::endl;
			glDeleteShader(fragment);
			return 0;
		}

		glAttachShader(program, vertex);
		glAttachShader(program, fragment);

		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		return program;
	}

	GLint Shader::getUniformLocation(const GLchar* name)
	{
		return glGetUniformLocation(_shaderID, name);
	}

	void Shader::setUniformMat1f(const GLchar* name, float value)
	{
		glUniform1f(getUniformLocation(name), value);
	}

	void Shader::setUniformMat1fv(const GLchar* name, float* value, GLsizei count)
	{
		glUniform1fv(getUniformLocation(name), count, value);
	}

	void Shader::setUniformMat1iv(const GLchar* name, int* value, GLsizei count)
	{
		glUniform1iv(getUniformLocation(name), count, value);
	}

	void Shader::setUniformMat2f(const GLchar* name, const Maths::vec2& vector)
	{
		glUniform2f(getUniformLocation(name), vector.x, vector.y);
	}

	void Shader::setUniformMat3f(const GLchar* name, const Maths::vec3& vector)
	{
		glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);

	}

	void Shader::setUniformMat4f(const GLchar* name, const Maths::vec4& vector)
	{
		glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
	}
	
	void Shader::setUniformMat1i(const GLchar* name, int value)
	{
		glUniform1i(getUniformLocation(name), value);
	}

	void Shader::setUniformMat4(const GLchar* name, const Maths::mat4& matrix)
	{
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
	}

	void Shader::enable() const 
	{
		glUseProgram(_shaderID);
	}

	void Shader::disable() const 
	{
		glUseProgram(0);
	}

}}