class NeuralNetwork
{
	private:

	btScalar* hidden;
	btScalar** inputToHidden;
	btScalar** hiddenToOutput;

	void resetHidden();

	public:

	int k; // number of hidden nodes
	int ID;
	btScalar eval;
	NeuralNetwork(const char* netdesc);
	~NeuralNetwork();
	void print();
	int  descLength();
	void getDesc(char* buffer);
	void getOutput(btScalar in0, btScalar in1, btScalar* out0, btScalar* out1);
};
