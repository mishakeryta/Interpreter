#include "Operator.hpp"

bool Operator::operator <=(const Operator& oper) const
{
	return priority <= oper.priority;
}

int Operator::calculate(int val1, int val2)
{
	switch (oper)
	{
	case'+':return val1 + val2;
	case'-':return val1 - val2;
	case'*':return val1 * val2;
	case'/':return val1 / val2;
	case'>':return (val1 > val2) ? (1) : 0;
	case'<':return (val1 < val2) ? (1) : 0;
	default:throw std::string{ "Error: something bad whith expression operator" };
	}
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
	case'\0':
		priority = 0; break;
	default: throw "Error: unknown operator";
	}

}


