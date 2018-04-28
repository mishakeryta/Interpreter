#ifndef OPERATORS_HPP
#define OPERATORS_HPP
#include <string>
class Operator
{
public:
	Operator(char ch = '\0',unsigned int numOfOpenScope = 0);
	bool operator <=(const Operator& oper)const;
	bool isEmpty() const { return oper == '\0'; }
	int calculate(int val1, int val2);
private:
	char oper;
	unsigned int priority;
	
};
#endif

