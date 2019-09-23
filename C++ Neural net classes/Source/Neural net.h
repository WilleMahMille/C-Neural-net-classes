#pragma once
#define _USE_MATH_DEFINES
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>
#include <random>


class Neuron;
class Layer;

class Network {
public:
	Network(std::vector<int> structure);
	~Network();

	void FeedForward(std::vector<float> inputs);
	void BackPropagation(std::vector<float> expectedOutputs, float learningRate = 0.5f, bool printErrorGradient = false);
	
	std::vector<float> GetOutput(bool unSquished = false);
	void PrintNetwork();
	void PrintOutput();

	std::vector<Layer> layers;
	

private:
	float CalcErrorGradient(std::vector<float> expectedOutput);

};

class Layer {
public:
	Layer(int _size);
	~Layer();

	void GenerateWeights(int layerSize, int nextLayerSize);

	void FeedForward(Layer *nextLayer);
	void BackPropagation(Layer *nextLayer, float learningRate = 0.5f);
	void SetErrorGradient(std::vector<float> expectedOutput);
	void SetErrorGradient(Layer* nextLayer);
	void UpdateBias(Layer* nextLayer, float learningRate = 0.5);

	void Squish();
	void PrintLayer();

	std::vector<Neuron> neurons;
	float bias;
	int size;
};

class Neuron {
public:
	Neuron();
	~Neuron();
	std::vector<float> weights;
	float squishedValue;
	float unSquishedValue;
	float errorGradient;

	void PrintNeuron();
	void Squish();
	void FeedForward(Layer* nextLayer);
	void UpdateWeights(Layer* nextLayer, float learningRate = 0.5);
	void UpdateErrorGradient(Layer* nextLayer);

};

