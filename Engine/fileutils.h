#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <stb_image.h>
#include "timer.h"

namespace Engine {

	// Filun luku

	class FileUtils
	{
	public:
		static std::string read_file(const char* filepath);
		static unsigned char* LoadTextureFromFile(const std::string Filename);
		int CoutFPS();
	private:
		Timer time;
		float timer = 0.0f;
		unsigned int frames = 0;
	};
}