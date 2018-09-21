#define STB_IMAGE_IMPLEMENTATION
#include "fileutils.h"

using namespace Engine;

std::string FileUtils::read_file(const char* filepath)
{
	// Mode rt, read text
	FILE* file = fopen(filepath, "rt");
	// Mennään filun loppuun
	// TODO error checki polkuun
	fseek(file, 0, SEEK_END);
	// Otetaan ylös pituus
	unsigned long length = ftell(file);
	char* data = new char[length + 1];
	// Asetetaan data nollaksi
	memset(data, 0, length + 1);
	// Mennään takasi filun alkuun ja otetaan datat talteen
	fseek(file, 0, SEEK_SET);
	fread(data, 1, length, file);
	fclose(file);

	// Datat stringiksi ja poistoon, resultit ulos funktiosta
	std::string result(data);
	delete[] data;
	return result;
}

unsigned char* FileUtils::LoadTextureFromFile(const std::string FileName)
{
		int x, y;
		int n = 3;
		std::string FileDir = "../Assets/" + FileName;
		unsigned char *data = stbi_load(FileDir.c_str(), &x, &y, &n, 3);

		if (data == nullptr)
		{
			std::cout << "\nKuvan lataus epäonnistui <NULLPTR>";
			return nullptr;
		}
		else return data;
}