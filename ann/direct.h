#ifndef EVCLIB_ANN_DIRECT_H
#define EVCLIB_ANN_DIRECT_H

#include <string>
#include <vector>
#include <function>

// The type to be used for ANN's nodes, including outputs and inputs
// It must be convertible to from double (i.e., understand assignments like =0.0)
#ifndef ANNNodeState
#define ANNNodeState double
#endif // ANNNodeStateType

typedef struct ANNDirectHyperparameters
{
	int inputNodes;
	int outputNodes;
	std::function<ANNNodeState(ANNNodeState)> transferFunction;
} ANNDirectHyperparameters;

typedef std::vector<ANNNodeStateType> Percept;
typedef std::vector<ANNNodeStateType> MotorPattern;

std::string str(const Percept& perc);
std::string str(const MotorPattern& motPat);

class ANNDirect
{
	private:

	ANNNodeState inputToOutput[ANN_DIRECT_INPUT_NODES][ANN_DIRECT_OUTPUT_NODES]; // same type is used for node state and weights

	public:

	int ID;
	double eval;

	ANNDirect(const ANNDirectHyperparameters&);
	void getParameters(std::string);
	MotorPattern output(const Percept& input) const;

	void print() const;
	std::string getDesc() const;
};

#endif // EVCLIB_ANN_DIRECT_H
