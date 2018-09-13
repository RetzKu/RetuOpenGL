#pragma once


#include <string>
#include <FreeImage\include\FreeImage.h>

namespace Engine {

	static BYTE* load_image(const char* filename, GLsizei* width, GLsizei* height)
	{
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP *dib = nullptr;
		fif = FreeImage_GetFileType(filename, 0);
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(filename);
		if (fif == FIF_UNKNOWN)
			return nullptr;

		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, filename);
			if (FreeImage_GetBPP(dib) != 32)
			{
				FIBITMAP* tempImage = dib;
				dib = FreeImage_ConvertTo32Bits(tempImage);
			}

		if (!dib)
			return nullptr;

		BYTE* pixels = (BYTE*)FreeImage_GetBits(dib);

		BYTE *bits = new BYTE[FreeImage_GetWidth(dib) * FreeImage_GetHeight(dib) * 4];

		for (int pix = 0; pix<FreeImage_GetWidth(dib) * FreeImage_GetHeight(dib); pix++)
		{
			bits[pix * 4 + 0] = pixels[pix * 4 + 2];
			bits[pix * 4 + 1] = pixels[pix * 4 + 1];
			bits[pix * 4 + 2] = pixels[pix * 4 + 0];
			bits[pix * 4 + 3] = pixels[pix * 4 + 3];
		}

		*width = FreeImage_GetWidth(dib);
		*height = FreeImage_GetHeight(dib);

		return bits;
	}
}