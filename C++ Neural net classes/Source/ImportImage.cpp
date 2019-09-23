#include "ImportImage.h"


using namespace cv;

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
Pixel CreatePixel(Vec3b bgr) {
	return Pixel(bgr.val[2], bgr.val[1], bgr.val[0]);
}

std::vector<Pixel> ReadImageToPixels(cv::String filePath) {
	//this import doesn't work
	std::vector<Pixel> pixels;
	Mat img;
	img = imread(filePath, 1);
	if (!img.data) {
		std::cout << "no data found in image\n";
	}
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			pixels.push_back(CreatePixel(img.at<Vec3b>(i, j)));
		}
	}
	return pixels;
}

Image::Image() {
}
Image::~Image() {
}
void Image::ReadImage(cv::String _filePath) {
	filePath = _filePath;
	pixels = ReadImageToPixels(filePath);
	
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
	for (int i = 0; i < pixels.size(); i++) {
		exportedPixels.push_back(pixels[i].fBlack);
	}
	return exportedPixels;
}




