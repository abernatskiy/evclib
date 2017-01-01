/* Base class for individuals/phenotypes,
   designed for compatibility with evalQueue
   template.

   For full compartibility, ensure additionally
   that a Hyperparameters type is defined and
   that the chuld class can be constructed out
   of it.
 */

#include <string>

class BaseIndividual
{
public:
	virtual void getParameters(std::string) = 0;
	virtual double getEvaluation() = 0;
	virtual void setEvaluation(double) = 0;
	virtual int getID() = 0;
	virtual std::string getDesc() = 0;
};
