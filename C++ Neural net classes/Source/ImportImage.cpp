#include "ImportImage.h"


Pixel::Pixel(int r, int g, int b) : iRed(r), iGreen(g), iBlue(b) {
	ConvertToFloat();
}
Pixel::Pixel(float r, float g, float b) : fRed(r), fGreen(g), fBlue(b) {
	ConvertToInt();
}
Pixel::~Pixel() {
}
void Pixel::ConvertToFloat() {
	fRed = iRed / static_cast<float>(255);
	fGreen = iGreen / static_cast<float>(255);
	fBlue = iBlue / static_cast<float>(255);
}
void Pixel::ConvertToInt() {
	iRed = fRed * 255;
	iGreen = fGreen * 255;
	iBlue = fBlue * 255;
}
void Pixel::ConvertToGray() {
	iBlack = (iRed + iGreen + iBlue) / 3;
	fBlack = static_cast<float>(iBlack) / 255;
}
void Pixel::InvertGray() {
	fBlack = 1 - fBlack;
	iBlack = 255 - iBlack;
}

std::vector<Pixel> ReadImageToPixels(char* filePath) {
	//this import doesn't work
	std::fstream file;
	file.open(filePath);
	int i;
	FILE* f = fopen(filePath, "rb");
	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

	// extract image height and width from header
	int width = *(int*)&info[18];
	int height = *(int*)&info[22];

	int size = 3 * width * height;
	unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
	fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
	fclose(f);


	for (i = 0; i < size; i += 3)
	{
		unsigned char tmp = data[i];
		data[i] = data[i + 2];
		data[i + 2] = tmp;
	}

	std::vector<Pixel> pixels;
	for (int i = 0; i < size; i += 3) {
		Pixel* temp = new Pixel(data[i], data[i + 1], data[i + 2]);
		pixels.push_back(*temp);
	}

	return pixels;
}
Image::Image() {
}
Image::~Image() {
}
void Image::ReadImage(std::string _filePath) {
	filePath = filePath;
	char* charFilePath = new char[filePath.length()];
	pixels = ReadImageToPixels(charFilePath);
}
void Image::ConvertToGray() {
	for (int i = 0; i < pixels.size(); i++) {
		pixels[i].ConvertToGray();
	}
}
void Image::InvertGray() {
	for (int i = 0; i < pixels.size(); i++) {
		pixels[i].InvertGray();
	}
}
std::vector<float> Image::ExportImageGrayFloats() {
	std::vector<float> exportedPixels;
	for (int i = 0; i < exportedPixels.size(); i++) {
		exportedPixels.push_back(pixels[i].fBlack);
	}
	return exportedPixels;
}




