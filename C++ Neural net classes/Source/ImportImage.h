#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Data.h"
#include <opencv2\core\core.hpp>
#include <opencv2/highgui/highgui.hpp>


class Pixel;

class Image {
public:
	Image();
	~Image();
	
	void ReadImage(cv::String _filePath);
	void InvertGray();
	void ConvertToGray();
	std::vector<float> ExportImageGrayFloats();

	cv::String filePath;

	std::vector<Pixel> pixels;

};

class Pixel {
public:
	Pixel(int r, int g, int b);
	Pixel(float r, float g, float b);
	Pixel(int gray);
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

