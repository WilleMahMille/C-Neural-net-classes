#include "Neural net.h"

Network::Network(std::vector<int> structure) {

	for (unsigned i = 0; i < structure.size(); i++) {
		srand(static_cast<unsigned> (time(0)));
		Layer* temp = new Layer(structure[i]);
		if (i != structure.size() - 1) {
			temp->GenerateWeights(structure[i + 1]);
		}
		layers.push_back(*temp);
	}
}
Network::~Network() {
}

void Network::FeedForward(std::vector<float> inputs) {
	//error handling
	if (inputs.size() != layers[0].neurons.size()) {
		throw std::invalid_argument("The inputs does not correspong to the networks inputs");
	}
	//"squish" first layer
	//change to compress
	for (int i = 0; i < layers[0].neurons.size(); i++) {
		layers[0].neurons[i].squishedValue = inputs[i];
	}
	//feed forward and squish
	for (int i = 0; i < layers.size() - 1; i++) {
		layers[i].FeedForward(&layers[i + 1]);
		layers[i + 1].Squish();
	}
}

std::vector<float> Network::GetOutput(bool unSqished) {
	std::vector<float> temp;
	for (unsigned i = 0; i < layers[layers.size() - 1].neurons.size(); i++) {
		if (!unSqished) {
			temp.push_back(layers[layers.size() - 1].neurons[i].squishedValue);
		}
		else {
			temp.push_back(layers[layers.size() - 1].neurons[i].unSquishedValue);
		}
	}
	return temp;
}
void Network::PrintNetwork() {
	for (unsigned i = 0; i < layers.size(); i++) {
		layers[i].PrintLayer();
	}
}
void Network::PrintOutput() {
	for (unsigned i = 0; i < layers[layers.size() - 1].neurons.size(); i++) {
		std::cout << "{" << layers[layers.size() - 1].neurons[i].squishedValue << "}\n";
	}
}


void Network::BackPropagation(std::vector<float> expectedOutput) {
	//error checking
	if (expectedOutput.size() > layers[layers.size() - 1].neurons.size()) {
		throw std::invalid_argument("The expected output is larger than the output in the network");
	}

	float errorGradient = CalcErrorGradient(expectedOutput);

	//set errorGradient for outputs
	layers[layers.size() - 1].SetErrorGradient(expectedOutput);

	//back propagating
	for (int i = layers.size() - 2; i >= 0; i--) {
		//update weights
		layers[i].BackPropagation(&layers[i + 1]);
		//update bias
		layers[i].UpdateBias(&layers[i + 1]);
		//set the error gradient for the layer
		layers[i].SetErrorGradient(&layers[i + 1]);
	}



}
float Network::CalcErrorGradient(std::vector<float> expectedOutput) {
	float errorGradient = 0;
	for (unsigned i = 0; i < expectedOutput.size(); i++) {
		errorGradient += pow(expectedOutput[i] - layers[layers.size() - 1].neurons[i].squishedValue, 2) / 2;
	}
	std::cout << "\nError gradient: " << errorGradient;
	return errorGradient;
}

Layer::Layer(int _size) {
	for (int i = 0; i < _size; i++) {
		Neuron* tempNeuron = new Neuron();
		neurons.push_back(*tempNeuron);
	}
	bias = rand() / static_cast<float>(RAND_MAX) * 10 - 5; //generate a bias between -5 and 5
	size = _size;
}
Layer::~Layer() {
}
void Layer::GenerateWeights(int nextLayerSize) {
	for (unsigned j = 0; j < neurons.size(); j++) {
		for (int i = 0; i < nextLayerSize; i++) {
			//random initialization
			float tempWeight = rand() / static_cast<float>(RAND_MAX);
			tempWeight /= neurons.size();
			neurons[j].weights.push_back(tempWeight);
		}
	}


}
void Layer::FeedForward(Layer *nextLayer) {
	//resetting next layers unsquished values
	for (int i = 0; i < nextLayer->neurons.size(); i++) {
		nextLayer->neurons[i].unSquishedValue = 0;
	}
	//adding the squished values
	for (unsigned i = 0; i < neurons.size(); i++) {
		neurons[i].FeedForward(nextLayer);
	}
	//adding the bias
	for (int i = 0; i < nextLayer->neurons.size(); i++) {
		nextLayer->neurons[i].unSquishedValue += bias;
	}
}
void Layer::Squish() {
	//squishing the unsquished to squished
	for (unsigned i = 0; i < neurons.size(); i++) {
		neurons[i].Squish();
	}
}
void Layer::SetErrorGradient(std::vector<float> expectedOutput) {
	//updating the error gradient for the outer layer
	for (int i = 0; i < neurons.size(); i++) {
		neurons[i].errorGradient = neurons[i].squishedValue - expectedOutput[i];
	}
}
void Layer::BackPropagation(Layer *nextLayer) {
	for (int i = 0; i < neurons.size(); i++) {
		neurons[i].UpdateWeights(nextLayer);
	}
}

void Layer::SetErrorGradient(Layer* nextLayer) {
	//updating the error gradient for the current layer
	if (nextLayer == nullptr) {	
		std::invalid_argument("nextLayer is nullptr");
	}
	for (int i = 0; i < neurons.size(); i++) {
		neurons[i].UpdateErrorGradient(nextLayer);
	}
}
void Layer::UpdateBias(Layer* nextLayer, float learningRate) {
	//update biases
	for (int i = 0; i < nextLayer->neurons.size(); i++) {
		float nextLayerOutput = nextLayer->neurons[i].squishedValue;
		float biasChange = nextLayer->neurons[i].errorGradient * nextLayerOutput * (1 - nextLayerOutput);
		bias -= biasChange * learningRate;
	}
}
void Layer::PrintLayer() {
	for (unsigned i = 0; i < neurons.size(); i++) {
		neurons[i].PrintNeuron();
	}
	std::cout << "\n";
}

Neuron::Neuron() {
	squishedValue = 0;
}
Neuron::~Neuron() {
}
void Neuron::PrintNeuron() {
	std::cout << "{" + std::to_string(squishedValue) + ",";

	for (unsigned i = 0; i < weights.size(); i++) {
		std::cout << " " + std::to_string(weights[i]);
	}
	std::cout << "} ";
}
void Neuron::FeedForward(Layer* nextLayer) {
	for (int i = 0; i < weights.size(); i++) {
		nextLayer->neurons[i].unSquishedValue += squishedValue * weights[i];
	}
}
void Neuron::Squish() {
	squishedValue = 1 / (1 + pow(M_E, (-unSquishedValue)));
}
void Neuron::UpdateWeights(Layer* nextLayer, float learningRate) {
	//update the weights
	this;
	for (int i = 0; i < weights.size(); i++) {

		float nextLayerOutput = nextLayer->neurons[i].squishedValue;

		float weightChange = nextLayer->neurons[i].errorGradient * nextLayerOutput * (1 - nextLayerOutput) * squishedValue;

		if (weightChange != 0 && nextLayer->size == 16) {
			std::cout << "";
		}

		weights[i] -= weightChange * learningRate;

	}

}

void Neuron::UpdateErrorGradient(Layer* nextLayer) {
	errorGradient = 0;
	for (unsigned i = 0; i < weights.size(); i++) {
		float nextLayerOutput = nextLayer->neurons[i].squishedValue;
		float errorGradientChange = nextLayer->neurons[i].errorGradient * nextLayerOutput * (1 - nextLayerOutput) * weights[i];
		errorGradient += errorGradientChange;
		std::cout << "";
	}
}
