#include "Neural net.h"
#include "ImportImage.h"
#include "Data.h"
#include <iostream>
#include <string>

void Examples(Data *data, Network *netw, int amtOfData, int examples = 5);

void PrintData(DataPackage data);

//possible problems
//1. Data is corrupted or invalid (not likely)
//2. Weight initialization (is a problem) [fixed, works now to some extent]
//3. Activation function (possibly a problem) 
//4. Bias wrongly implemented (possibly a problem)


std::vector<float> ImportImage() {
	std::string filePath = "C:/Users/Wilhelm.jansson2/Desktop/ImportImage/Import.bmp";
	std::cout << "------------------Importing Image--------------------------\n";
	std::cout << "The current filepath to import from is: " << filePath << "\n";
	system("PAUSE");
	std::cout << "Importing image\n";
	Image* img = new Image();
	img->ReadImage(filePath);
	img->ConvertToGray();
	img->InvertGray();
	return img->ExportImageGrayFloats();
}

int main() {

	/*
	//this works aswell
	std::vector<int> layers;
	layers.push_back(2);
	layers.push_back(3);
	layers.push_back(1);

	Network *netw = new Network(layers);

	std::vector<float> inputOne;
	std::vector<float> outputOne;
	inputOne.push_back(0);
	inputOne.push_back(0);
	outputOne.push_back(0);

	std::vector<float> inputTwo;
	std::vector<float> outputTwo;
	inputTwo.push_back(0);
	inputTwo.push_back(1);
	outputTwo.push_back(1);

	std::vector<float> inputThree;
	std::vector<float> outputThree;
	inputThree.push_back(1);
	inputThree.push_back(0);
	outputThree.push_back(1);

	std::vector<float> inputFour;
	std::vector<float> outputFour;
	inputFour.push_back(1);
	inputFour.push_back(1);
	outputFour.push_back(0);


	int trainingTimes = 50000;

	for (int i = 0; i < trainingTimes; i++) {
		int inputValue = static_cast<int>(rand() / static_cast<float>(RAND_MAX) * 4) + 1;
		std::vector<float> input = std::vector<float>();
		std::vector<float> output = std::vector<float>();
		switch (inputValue) {
		case 1:
			input = inputOne;
			output = outputOne;
			break;
		case 2:
			input = inputTwo; 
			output = outputTwo;
			break;
		case 3:
			input = inputThree;
			output = outputThree;
			break;
		case 4:
			input = inputFour;
			output = outputFour;
			break;
		default:
			input = inputOne;
			output = outputOne;
			break;
		}
		netw->FeedForward(input);
		netw->BackPropagation(output);
	}

	std::cout << "\n";

	netw->FeedForward(inputOne);
	netw->PrintOutput();

	netw->FeedForward(inputTwo);
	netw->PrintOutput();

	netw->FeedForward(inputThree);
	netw->PrintOutput();

	netw->FeedForward(inputFour);
	netw->PrintOutput();
	*/
	


	
	int amtOfData = 10000;
	//path 1: C:/Users/Wilhelm.jansson2/Source/Repos/WilleMahMille/C-Neural-net-classes/C++ Neural net classes/Source/Data/train.csv
	//path 2: C:/Users/Wille ma Mille/source/repos/C++ Neural net classes/C++ Neural net classes/Source/Data/train.csv
	Data *data = new Data("C:/Users/Wilhelm.jansson2/Source/Repos/WilleMahMille/C-Neural-net-classes/C++ Neural net classes/Source/Data/train.csv", "Training data");
	data->ReadDataFromFile(amtOfData);

	std::vector<int> layers;
	layers.push_back(784);
	layers.push_back(16);
	layers.push_back(10);
	Network* netw = new Network(layers);
	

	std::vector<float> input;
	int dataOutput;
	std::vector<float> expectedOutput;
	int trainingTimes = 30000;
	
	
	for (int i = 0; i < trainingTimes; i++) {

		int dataValue = static_cast<int>(rand() / static_cast<float>(RAND_MAX) * (amtOfData - 1));
		DataPackage temp = data->GetDataNumber(dataValue);
		input = std::vector<float>(temp.floatValues);
		dataOutput = temp.expectedValue;
		netw->FeedForward(input);
		
		expectedOutput = std::vector<float>();
		for (int i = 0; i < dataOutput; i++) {
			expectedOutput.push_back(0);
		}
		expectedOutput.push_back(1);
		for (int i = dataOutput + 1; i <= 9; i++) {
			expectedOutput.push_back(0);
		}

		if ((trainingTimes - i) % 1000 == 0) {
			netw->BackPropagation(expectedOutput, true);
			std::cout << "\t\t\tTimes left: " << trainingTimes - i << "\n";
		}
		else {
			netw->BackPropagation(expectedOutput);
		}
	}
	std::cout << "\n\nDone learning\n";
	
	
	
	
	while (true) {
		std::vector<float> output;
		float actualOutput = 0;
		float actualOutputValue = 0;
		system("PAUSE");
		input = ImportImage();
		netw->FeedForward(input);
		output = netw->GetOutput();

		for (int i = 0; i < output.size(); i++) {
			std::cout << i << ": " << output[i] << "\n";
			if (output[i] > actualOutputValue) {
				actualOutput = i;
				actualOutputValue = output[i];
			}
		}
		std::cout << "The output from the network was: " << actualOutput << " with a value of " << actualOutputValue << "\n-----------------------------------------------\n";

	}
}



void Examples(Data *data, Network *netw, int amtOfData, int examples) {

	std::cout << "Outputing " << examples << " examples: \n";

	std::vector<float> output;
	int exampleDataOutput;
	int actualOutput;
	float actualOutputValue;
	std::vector<float> input;


	for (int i = 0; i < examples; i++) {

		int dataValue = static_cast<int>(rand() / static_cast<float>(RAND_MAX) * amtOfData);
		DataPackage temp = data->GetDataNumber(dataValue);
		input = std::vector<float>(temp.floatValues);
		exampleDataOutput = temp.expectedValue;
		netw->FeedForward(input);
		output = netw->GetOutput();

		std::vector<float> expectedOutput;
		int dataOutput = temp.expectedValue;
		expectedOutput = std::vector<float>();
		for (int i = 0; i < dataOutput; i++) {
			expectedOutput.push_back(0);
		}
		expectedOutput.push_back(1);
		for (int i = dataOutput + 1; i <= 9; i++) {
			expectedOutput.push_back(0);
		}

		actualOutput = 0;
		actualOutputValue = 0;

		std::cout << "Did the sample data " << dataValue << ", expected value was " << exampleDataOutput << "\n";
		PrintData(temp);
		for (int i = 0; i < output.size(); i++) {
			std::cout << i << ": " << output[i] << "\t\t\tExpected: " << expectedOutput[i] << "\n";
			if (output[i] > actualOutputValue) {
				actualOutput = i;
				actualOutputValue = output[i];
			}
		}
		std::cout << "The output from the network was: " << actualOutput << " with a value of " << actualOutputValue << "\n-----------------------------------------------\n";


	}
}

void PrintData(DataPackage data) {
	std::vector<int> dataValues = data.intValues;
	for (int i = 0; i < 28; i++) {
		for (int j = 0; j < 28; j++) {
			int tempDataValue = dataValues[i * 28 + j];
			if (tempDataValue == 0) {
				std::cout << "  ";
			}
			else {
				std::cout << "##";
			}
		}
		std::cout << "\n";
	}

}

