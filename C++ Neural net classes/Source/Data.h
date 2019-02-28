#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class DataPackage;

class Data {
public:
	Data(std::string _filePath, std::string _dataName);	
	~Data();
	//read the file and convert into data packages
	bool ReadDataFromFile(int maxLength = 500);
	std::vector<int> GetValues(std::string data);

	//to receive data
	DataPackage GetDataNumber(int number);

	//Variables
	std::vector<DataPackage> data;
	std::string dataName, filePath;
	int length;

};


class DataPackage {
public:
	DataPackage(std::vector<int> _values);
	~DataPackage();
	int expectedValue;
	std::vector<int> intValues;
	//float values are just values divided by 255
	std::vector<float> floatValues;
};

