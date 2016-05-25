#ifndef ANN_DIRECT_H
#define ANN_DIRECT_H

#include <string>
#include <array>
#include "../misc.h" // sigmoid() is defined there

#include "GlutDemoApplication.h"

#ifndef ANN_DIRECT_INPUT_NODES
#define ANN_DIRECT_INPUT_NODES 4
#endif // ANN_DIRECT_INPUT_NODES

#ifndef ANN_DIRECT_OUTPUT_NODES
#define ANN_DIRECT_OUTPUT_NODES 2
#endif // ANN_DIRECT_OUTPUT_NODES

#ifndef ANN_DIRECT_SIGMOID
#define ANN_DIRECT_SIGMOID(X) sigmoid(X) // I'm using the func from misc.h by default
#endif // ANN_SIGMOID

// The type to be used for ANN's nodes, including outputs and inputs
// It must be convertible to from double (i.e., understand assignments like =0.0)
#ifndef ANNNodeStateType
#define ANNNodeStateType btScalar
#endif // ANNNodeStateType

typedef std::array<ANNNodeStateType,ANN_DIRECT_INPUT_NODES> Percept;
typedef std::array<ANNNodeStateType,ANN_DIRECT_OUTPUT_NODES> MotorPattern;

std::string str(const Percept& perc);
std::string str(const MotorPattern& motPat);

class NeuralNetwork
{
	private:

	btScalar inputToOutput[ANN_DIRECT_INPUT_NODES][ANN_DIRECT_OUTPUT_NODES];

	public:

	int ID;
	double eval;
	NeuralNetwork(std::string);
	void print() const;
	std::string getDesc() const;
	MotorPattern output(const Percept& input) const; // depends on ANN_DIRECT_SIGMOID()
};

#endif // ANN_DIRECT_H
