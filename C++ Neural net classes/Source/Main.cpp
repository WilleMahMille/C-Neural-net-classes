#include "Neural net.h"
#include "Data.h"
#include <iostream>
#include <string>

void Examples(Data *data, Network *netw, int amtOfData, int examples = 5);

int main() {

	//I think we need to add biases to make it work with the data, right now it only works halfly
	//rebuilt structure, but still no biases
	
	
	
	/*
	std::vector<int> layers;

	layers.push_back(2);
	layers.push_back(2);
	layers.push_back(2);

	Network* netw = new Network(layers);
	
	std::vector<float> input;
	std::vector<float> output;
	input.push_back(1);
	input.push_back(0);
	output.push_back(0.01);
	output.push_back(0.99);
	
	for (int i = 0; i < 20000; i++) {
		netw->FeedForward(input);
		netw->BackPropagation(output);
	}
	std::cout << "\n";
	netw->FeedForward(input);
	netw->PrintOutput();

	*/

	//still not working (haven't added biases)
	

	int amtOfData = 500;

	Data *data = new Data("../Debug/Data/train.csv", "Training data");
	data->ReadDataFromFile(amtOfData);

	
	std::vector<int> layers;
	layers.push_back(784);
	layers.push_back(16);
	layers.push_back(10);
	Network* netw = new Network(layers);
	

	std::vector<float> input;
	int dataOutput;
	std::vector<float> expectedOutput;
	int trainingTimes = 1000;
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
		netw->BackPropagation(expectedOutput);
		std::cout << "\t\t\tTimes left: " << trainingTimes - i - 1;
	}

	std::cout << "\n\nDone learning\n";
	
	Examples(data, netw, amtOfData, 5);
	
	while (true);
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


		actualOutput = 0;
		actualOutputValue = 0;

		std::cout << "Did the sample data " << dataValue << ", expected value was " << exampleDataOutput << "\n";
		std::cout << "Actual output: \n";
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