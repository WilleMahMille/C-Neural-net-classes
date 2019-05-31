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
	//Read the file and convert the file into data packages
	bool ReadDataFromFile(int maxLength = 500);

	//Retrieves a specific data based on number
	DataPackage GetDataNumber(int number);

	//Variables
	std::vector<DataPackage> data;
	std::string dataName, filePath;
	int length;
private:
	//Retrieves a specific
	std::vector<int> GetValues(std::string data);

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

