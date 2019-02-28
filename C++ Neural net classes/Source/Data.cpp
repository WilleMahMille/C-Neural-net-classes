#include "Data.h"

Data::Data(std::string _filePath, std::string _dataName) {
	filePath = _filePath;
	dataName = _dataName;
	length = 0;
}

Data::~Data() {
}

bool Data::ReadDataFromFile(int maxLength) {
	std::ifstream file;
	file.open(filePath);
	std::string value;
	std::getline(file, value);

	while (file.good() && maxLength > length) {
		std::getline(file, value);
		std::vector<int> dataValues = GetValues(value);
		DataPackage *dataPackage = new DataPackage(dataValues);
		data.push_back(*dataPackage);
		length++;
	}
	file.close();
	return true;
}

std::vector<int> Data::GetValues(std::string data) {
	std::vector<int> values;
	int current = 0;
	std::string temp = "";
	while (current < data.length()) {
		if (data[current] != ',') {
			temp += data[current];
		}
		else {
			values.push_back(std::stoi(temp));
			temp = "";
		}
		current++;
	}
	values.push_back(std::stoi(temp));
	return values;
}

DataPackage Data::GetDataNumber(int number) {
	return data[number];
}


DataPackage::DataPackage(std::vector<int> _values) {
 	expectedValue = _values[0];
	for (int i = 1; i < _values.size(); i++) {
		intValues.push_back(_values[i]);
		floatValues.push_back(_values[i] / static_cast<float>(255));
	}
}

DataPackage::~DataPackage() {
}
