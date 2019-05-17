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
	output.push_back(0.5);
	output.push_back(0.99);
	
	for (int i = 0; i < 20000; i++) {
		netw->FeedForward(input);
		netw->BackPropagation(output);
	}
	std::cout << "\n";
	netw->FeedForward(input);
	netw->PrintOutput();

	*/


	/*
	std::vector<int> layers;
	layers.push_back(2);
	layers.push_back(2);
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


	int trainingTimes = 10000;

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
	


	//still not working (have added biases)
	/*
	Data *data = new Data("C:/Users/Wilhelm.jansson2/Source/Repos/WilleMahMille/C-Neural-net-classes/C++ Neural net classes/Source/Data/train.csv", "Training data");
	data->ReadDataFromFile(10);

	for (int i = 0; i < 10; i++) {
		DataPackage temp = data->GetDataNumber(i);
		std::vector<int> values = temp.intValues;
		for (int j = 0; j < 28; j++) {
			for (int k = 0; k < 28; k++) {
				if (values[j * 28 + k] > 0) {
					std::cout << "M";
				}
				else {
					std::cout << " ";
				}
			}
			std::cout << "\n";
		}
		std::cout << "\n\n\n\n\n";
	}


	*/

	
	//I think the problem is that the output from all 728 neurons in the first layer sets the squished value in the second layer to one,
	//which in turn makes the weight change in backpropagation become 0, due to 1 - squished = 0, if squished = 1
	
	int amtOfData = 500;

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
		std::cout << "Actual output: \n";
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