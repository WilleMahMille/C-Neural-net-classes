#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Data.h"


class Pixel;

class Image {
public:
	Image();
	~Image();
	
	void ReadImage(std::string _filePath);
	void InvertGray();
	void ConvertToGray();
	std::vector<float> ExportImageGrayFloats();

	std::string filePath;

	std::vector<Pixel> pixels;

};

class Pixel {
public:
	Pixel(int r, int g, int b);
	Pixel(float r, float g, float b);
	~Pixel();

	//adds red, green and blue together and divides by 3 (not accurate conversion)
	void ConvertToGray();
	//inverts gray values
	void InvertGray();
	int iRed, iBlue, iGreen, iBlack;
	float fRed, fBlue, fGreen, fBlack;
private:
	void ConvertToFloat();
	void ConvertToInt();
};

