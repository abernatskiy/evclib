#ifndef ANN_HIDDEN_RECURSIVE
#define ANN_HIDDEN_RECURSIVE

#include <string>
#include <array>
#include "../misc.h" // sigmoid() is defined there

#include "GlutDemoApplication.h"

#ifndef ANN_HIDDEN_RECURSIVE_INPUT_NODES
#define ANN_HIDDEN_RECURSIVE_INPUT_NODES 4
#endif // ANN_HIDDEN_RECURSIVE_INPUT_NODES

#ifndef ANN_HIDDEN_RECURSIVE_HIDDEN_NODES
#define ANN_HIDDEN_RECURSIVE_HIDDEN_NODES 2
#endif // ANN_HIDDEN_RECURSIVE_HIDDEN_NODES

#ifndef ANN_HIDDEN_RECURSIVE_OUTPUT_NODES
#define ANN_HIDDEN_RECURSIVE_OUTPUT_NODES 2
#endif // ANN_HIDDEN_RECURSIVE_OUTPUT_NODES

#ifndef ANN_HIDDEN_RECURSIVE_SIGMOID
#define ANN_HIDDEN_RECURSIVE_SIGMOID(X) sigmoid(X) // I'm using the func from misc.h by default
#endif // ANN_SIGMOID

// The type to be used for ANN's nodes, including outputs and inputs
// It must be convertible to from double (i.e., understand assignments like =0.0)
#ifndef ANNNodeStateType
#define ANNNodeStateType btScalar
#endif // ANNNodeStateType

typedef std::array<ANNNodeStateType,ANN_HIDDEN_RECURSIVE_INPUT_NODES> Percept;
typedef std::array<ANNNodeStateType,ANN_HIDDEN_RECURSIVE_OUTPUT_NODES> MotorPattern;

std::string str(const Percept& perc);
std::string str(const MotorPattern& motPat);

class NeuralNetwork
{
	private:

	btScalar hidden[ANN_HIDDEN_RECURSIVE_HIDDEN_NODES];
	btScalar inputToHidden[ANN_HIDDEN_RECURSIVE_INPUT_NODES][ANN_HIDDEN_RECURSIVE_HIDDEN_NODES];
	btScalar hiddenToHidden[ANN_HIDDEN_RECURSIVE_HIDDEN_NODES][ANN_HIDDEN_RECURSIVE_HIDDEN_NODES];
	btScalar hiddenToOutput[ANN_HIDDEN_RECURSIVE_HIDDEN_NODES][ANN_HIDDEN_RECURSIVE_OUTPUT_NODES];

	public:

	int ID;
	double eval;
	NeuralNetwork(std::string);
	NeuralNetwork(const NeuralNetwork&);
	void print() const;
	void printHidden() const;
	std::string getDesc() const;
	void resetHidden();
	MotorPattern output(const Percept& input); // depends on ANN_DIRECT_SIGMOID()
};

#endif // ANN_HIDDEN_RECURSIVE
