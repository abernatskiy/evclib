#include <string.h>
#include "misc.h" // sigmoid() is there

#include "ANNHidden.h"

NeuralNetwork::NeuralNetwork(const char* netdesc)
{
	// determining the number of hidden nodes
	int dim = 1 + countSpaces(netdesc);
	if(dim < 5)
	{
		printf("Bad neural network string - number of fields must be 5 or more (it is %d)\n", dim);
		exit(1);
	}

	float kEst = ((float) (dim - 1))/4.f;

	if(floorf(kEst) != kEst)
	{
		printf("Bad neural network string - cannot determine number of hidden nodes (estimate based on number of weights is %2.2f)\n", kEst);
		exit(1);
	}

	k = (int) kEst;

	// allocating memory and initializing values of the hidden layer
	hidden = new btScalar[k];
	resetHidden();

	// allocating memory for inter-layer matrices
	inputToHidden = new btScalar*[2];
	for(int i=0; i<2; i++)
		inputToHidden[i] = new btScalar[k];
	hiddenToOutput = new btScalar*[k];
	for(int i=0; i<k; i++)
		hiddenToOutput[i] = new btScalar[2];

	// parsing the description string
	int len = strlen(netdesc);
	char buf[len+2];
	strncpy(buf, netdesc, len+2);

	char* pch = strtok(buf, " ");
	sscanf(pch, "%d", &ID);
	for(int i=0; i<2; i++)
		for(int j=0; j<k; j++)
		{
			pch = strtok(NULL, " ");
			sscanf(pch, "%f", &inputToHidden[i][j]);
		}
	for(int i=0; i<k; i++)
		for(int j=0; j<2; j++)
		{
			pch = strtok(NULL, " ");
			sscanf(pch, "%f", &hiddenToOutput[i][j]);
		}

	eval = -1.f;
}

NeuralNetwork::~NeuralNetwork()
{
	delete [] hidden;
	for(int i=0; i<2; i++)
		delete [] inputToHidden[i];
	delete [] inputToHidden;
	for(int i=0; i<k; i++)
		delete [] hiddenToOutput[i];
	delete [] hiddenToOutput;
}

void NeuralNetwork::print()
{
	printf("ID=%d k=%d\n\n", ID, k);

	for(int i=0; i<2; i++)
	{
		for(int j=0; j<k; j++)
			printf("%2.4f ", inputToHidden[i][j]);
		printf("\n");
	}
	printf("\n");

	for(int i=0; i<k; i++)
	{
		for(int j=0; j<2; j++)
			printf("%2.4f ", hiddenToOutput[i][j]);
		printf("\n");
	}
	printf("\n");

	printf("Current values of the hidden layer:\n");
	for(int j=0; j<k; j++)
		printf(" %2.4f", hidden[j]);
	printf("\n");
}

int NeuralNetwork::descLength()
{
	return WIDTH_OF_DESCRIPTION(k);
}

void NeuralNetwork::getDesc(char* buffer)
{
	const int buflen = WIDTH_OF_FLOAT_STRING_REPRESENTATION;
	char tmpstr[buflen];
	sprintf(tmpstr, "%d ", ID);
	strncpy(buffer, tmpstr, buflen);

	for(int i=0; i<2; i++)
		for(int j=0; j<k; j++)
		{
			sprintf(tmpstr, "%2.4f ", inputToHidden[i][j]);
			strncat(buffer, tmpstr, buflen);
		}
	for(int i=0; i<k; i++)
		for(int j=0; j<2; j++)
		{
			if(i==k-1 && j==1)
				sprintf(tmpstr, "%2.4f\n", hiddenToOutput[i][j]);
			else
				sprintf(tmpstr, "%2.4f ", hiddenToOutput[i][j]);
			strncat(buffer, tmpstr, buflen);
		}
}

void NeuralNetwork::getOutput(btScalar in0, btScalar in1, btScalar* out0, btScalar* out1)
{
//	printf("%2.4f %2.4f -> ", in0, in1);

	btScalar hiddenProcessed[k]; // optimization (buffer preallocation) should be used here

	for(int j=0; j<k; j++)
	{
		hiddenProcessed[j] = 0.f;
		hiddenProcessed[j] += inputToHidden[0][j]*in0;
		hiddenProcessed[j] += inputToHidden[1][j]*in1;
		hiddenProcessed[j] = sigmoid(hiddenProcessed[j]);
	}

	for(int i=0; i<k; i++)
		hidden[i] = hiddenProcessed[i];

	*out0 = 0.f; *out1 = 0.f;
	for(int j=0; j<k; j++)
	{
		*out0 += hiddenToOutput[j][0]*hiddenProcessed[j];
		*out1 += hiddenToOutput[j][1]*hiddenProcessed[j];
	}
	*out0 = sigmoid(*out0); *out1 = sigmoid(*out1);

//	printf("-> %2.4f %2.4f\n", *out0, *out1);
}

void NeuralNetwork::resetHidden()
{
	for(int i=0; i<k; i++)
		hidden[i] = 0.0f;
}
