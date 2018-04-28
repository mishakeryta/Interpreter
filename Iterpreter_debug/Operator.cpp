#include "Operator.hpp"

bool Operator::operator <(const Operator& oper) const
{
	return priority < oper.priority;
}


Operator::Operator(char chr, unsigned int numOfOpenScope):oper{chr}
{
	switch (chr)
	{
	case'+':
	case'-':
		priority = 5 + 100 * numOfOpenScope; break;
	case'*':
	case'/':
		priority = 10 + 100 * numOfOpenScope; break;
	case'<':
	case'>':
		priority = 4 + 100 * numOfOpenScope; break;
	default: throw "Error: unknown operator";
	}

}


