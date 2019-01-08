#pragma once
#ifndef __IMAGE_SAVE_H__
#define __IMAGE_SAVE_H__

#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

template<class T>
inline void saveGreyPNGfile(T* arr, int width, int height, const std::string& fileName)
 {
	// pmm(p6) -> png convert
	std::ofstream ofs;
	ofs.open("imageTemp/temp.ppm", std::ios::out | std::ios::binary);
	ofs << "P6\n" << width << ' ' << height << "\n255\n";
	for (unsigned i = 0; i < width * height; ++i)
	{
		unsigned char n = static_cast<unsigned char>(arr[i] * 255);
		ofs << n << n << n;
	}
	ofs.close();
	
	int x, y, n;
	unsigned char* data = stbi_load("imageTemp/temp.ppm", &x, &y, &n, 0);

	std::string destination = "imageResult/" + fileName;
	stbi_write_png(destination.c_str(), x, y, n, data, x * n);
	
	stbi_image_free(data);
}

template <class T>
inline void savePNGfile(T* arr, int width, int height, const std::string& fileName)
{
	// pmm(p6) -> png convert
	std::ofstream ofs;
	ofs.open("imageTemp/raytemp.ppm", std::ios::out | std::ios::binary);
	ofs << "P6\n" << width << ' ' << height << "\n255\n";
	for (unsigned i = 0; i < width * height * 3; ++i)
	{
		unsigned char n = static_cast<unsigned char>(arr[i] * 255);
		ofs << n;
	}
	ofs.close();

	int x, y, n;
	unsigned char* data = stbi_load("imageTemp/raytemp.ppm", &x, &y, &n, 0);

	std::string destination = "imageResult/" + fileName;
	stbi_write_png(destination.c_str(), x, y, n, data, x * n);
	
	stbi_image_free(data);
}

#endif